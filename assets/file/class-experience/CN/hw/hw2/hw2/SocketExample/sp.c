#ifdef READ_SERVER
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define ERR_EXIT(a) { perror(a); exit(1); }
typedef struct account{
    int id;
    int balance;
}Account;

typedef struct {
    char hostname[512];  // server's hostname
    unsigned short port;  // port to listen
    int listen_fd;  // fd to wait for a new connection
} server;

typedef struct {
    char host[512];  // client's host
    int conn_fd;  // fd to talk with client
    char buf[512];  // data sent by/to client
    size_t buf_len;  // bytes used by buf
    // you don't need to change this.
	int item;
    int wait_for_write;  // used by handle_read to know if the header is read or not.
} request;

server svr;  // server
request* requestP = NULL;  // point to a list of requests
int maxfd;  // size of open file descriptor table, size of request list

const char* accept_read_header = "ACCEPT_FROM_READ";
const char* accept_write_header = "ACCEPT_FROM_WRITE";

// Forwards

static void init_server(unsigned short port);
// initailize a server, exit for error

static void init_request(request* reqP);
// initailize a request instance

static void free_request(request* reqP);
// free resources used by a request instance

static int handle_read(request* reqP);
// return 0: socket ended, request done.
// return 1: success, message (without header) got this time is in reqP->buf with reqP->buf_len bytes. read more until got <= 0.
// It's guaranteed that the header would be correctly set after the first read.
// error code:
// -1: client connection error
int Read_Account(int file_fd, int idx){
    if(lseek(file_fd, sizeof(Account)*(idx-1), SEEK_SET)== -1){
        fprintf(stderr, "read account wrong\n");
        exit(1);
    }
    Account temp;
    read(file_fd, &temp, sizeof(temp));
    return temp.balance;
}


int main(int argc, char** argv) {
    
    int i, ret;

    struct sockaddr_in cliaddr;  // used by accept()
    int clilen;

    int conn_fd;  // fd for a new connection with client
    int file_fd;  // fd for file that we open for reading
    char buf[512];
    int buf_len;

    // Parse args.
    if (argc != 2) {
        fprintf(stderr, "usage: %s [port]\n", argv[0]);
        exit(1);
    }

    // Initialize server
    init_server((unsigned short) atoi(argv[1]));

    fd_set master;
    fd_set read_fds;
    FD_ZERO(&master);
    FD_ZERO(&read_fds);

    // Get file descripter table size and initize request table
    maxfd = getdtablesize();
    requestP = (request*) malloc(sizeof(request) * maxfd);
    if (requestP == NULL) {
        ERR_EXIT("out of memory allocating all requests");
    }
    for (i = 0; i < maxfd; i++) {
        init_request(&requestP[i]);
    }
    requestP[svr.listen_fd].conn_fd = svr.listen_fd;
    strcpy(requestP[svr.listen_fd].host, svr.hostname);

    int listener = svr.listen_fd;
    FD_SET(listener, &master);

    // Loop for handling connections
    fprintf(stderr, "\nstarting on %.80s, port %d, fd %d, maxconn %d...\n", svr.hostname, svr.port, svr.listen_fd, maxfd);
    // add
    file_fd = open("account_list", O_RDWR);
    while (1){
        read_fds = master; // 複製 master
        // TODO: Add IO multiplexing
        if(select(maxfd, &read_fds, NULL, NULL, NULL) == -1) {
            perror("select");
            exit(4);
        }
        for(int i = 0; i < maxfd; i++){
            if(FD_ISSET(i, &read_fds)){
                if(i == listener){
                    // Check new connection
                    clilen = sizeof(cliaddr);
                    conn_fd = accept(svr.listen_fd, (struct sockaddr*)&cliaddr, (socklen_t*)&clilen);
                    if (conn_fd < 0) {
                        //if (errno == EINTR || errno == EAGAIN) continue;  // try again
                        if (errno == ENFILE) {
                            (void) fprintf(stderr, "out of file descriptor table ... (maxconn %d)\n", maxfd);
                            continue;
                        }
                        ERR_EXIT("accept")
                    }
                    FD_SET(conn_fd, &master);
                    requestP[conn_fd].conn_fd = conn_fd;
                    strcpy(requestP[conn_fd].host, inet_ntoa(cliaddr.sin_addr));
                    fprintf(stderr, "getting a new request... fd %d from %s\n", conn_fd, requestP[conn_fd].host);
                }
                else{
                    ret = handle_read(&requestP[i]); // parse data from client to requestP[conn_fd].buf
                    if (ret < 0) {
                        fprintf(stderr, "bad request from %s\n", requestP[i].host);
                        continue;
                    }
                    int num = atoi(requestP[i].buf);
                    
                    struct flock fl;
                    fl.l_type   = F_RDLCK;  /* F_RDLCK，F_WRLCK，F_UNLCK    */
                    fl.l_whence = SEEK_SET; /* SEEK_SET，SEEK_CUR，SEEK_END */
                    fl.l_start  = sizeof(Account)*(num - 1);        /* Offset from l_whence         */
                    fl.l_len    = sizeof(Account);        /* length，0 = to EOF           */
                    fl.l_pid    = getpid(); /* our PID                      */
                    
                    if(fcntl(file_fd, F_SETLK, &fl) < 0){
                        sprintf(buf,"This account is locked.\n");
                        write(requestP[i].conn_fd, buf, strlen(buf));
                    }
                    else{
                        int balance = Read_Account(file_fd, num);
                        sprintf(buf,"%d %d\n", num, balance);
                        write(requestP[i].conn_fd, buf, strlen(buf));
                        fl.l_type = F_UNLCK;
                        fcntl(file_fd,F_SETLK,&fl);
                    }
                    
                    FD_CLR(i, &master);
                    close(requestP[i].conn_fd);
                    free_request(&requestP[i]);
                    
                }
            }
        }		
    }
    close(file_fd);
    free(requestP);
    return 0;
}


// ======================================================================================================
// You don't need to know how the following codes are working
#include <fcntl.h>

static void* e_malloc(size_t size);


static void init_request(request* reqP) {
    reqP->conn_fd = -1;
    reqP->buf_len = 0;
    reqP->item = 0;
    reqP->wait_for_write = 0;
}

static void free_request(request* reqP) {
    /*if (reqP->filename != NULL) {
        free(reqP->filename);
        reqP->filename = NULL;
    }*/
    init_request(reqP);
}

// return 0: socket ended, request done.
// return 1: success, message (without header) got this time is in reqP->buf with reqP->buf_len bytes. read more until got <= 0.
// It's guaranteed that the header would be correctly set after the first read.
// error code:
// -1: client connection error
static int handle_read(request* reqP) {
    int r;
    char buf[512];

    // Read in request from client
    r = read(reqP->conn_fd, buf, sizeof(buf));
    if (r < 0) return -1;
    if (r == 0) return 0;
	char* p1 = strstr(buf, "\015\012");
	int newline_len = 2;
	// be careful that in Windows, line ends with \015\012
	if (p1 == NULL) {
		p1 = strstr(buf, "\012");
		newline_len = 1;
		if (p1 == NULL) {
			ERR_EXIT("this really should not happen...");
		}
	}
	size_t len = p1 - buf + 1;
	memmove(reqP->buf, buf, len);
	reqP->buf[len - 1] = '\0';
	reqP->buf_len = len-1;
    return 1;
}

static void init_server(unsigned short port) {
    struct sockaddr_in servaddr;
    int tmp;

    gethostname(svr.hostname, sizeof(svr.hostname));
    svr.port = port;

    svr.listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (svr.listen_fd < 0) ERR_EXIT("socket");

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    tmp = 1;
    if (setsockopt(svr.listen_fd, SOL_SOCKET, SO_REUSEADDR, (void*)&tmp, sizeof(tmp)) < 0) {
        ERR_EXIT("setsockopt");
    }
    if (bind(svr.listen_fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        ERR_EXIT("bind");
    }
    if (listen(svr.listen_fd, 1024) < 0) {
        ERR_EXIT("listen");
    }
}

static void* e_malloc(size_t size) {
    void* ptr;

    ptr = malloc(size);
    if (ptr == NULL) ERR_EXIT("out of memory");
    return ptr;
}




#else




#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define ERR_EXIT(a) { perror(a); exit(1); }
typedef struct account{
    int id;
    int balance;
}Account;

typedef struct {
    char hostname[512];  // server's hostname
    unsigned short port;  // port to listen
    int listen_fd;  // fd to wait for a new connection
} server;

typedef struct {
    char host[512];  // client's host
    int conn_fd;  // fd to talk with client
    char buf[512];  // data sent by/to client
    size_t buf_len;  // bytes used by buf
    // you don't need to change this.
    int item;
    int wait_for_write;  // used by handle_read to know if the header is read or not.
} request;

server svr;  // server
request* requestP = NULL;  // point to a list of requests
int maxfd;  // size of open file descriptor table, size of request list

const char* accept_read_header = "ACCEPT_FROM_READ";
const char* accept_write_header = "ACCEPT_FROM_WRITE";

// Forwards

static void init_server(unsigned short port);
// initailize a server, exit for error

static void init_request(request* reqP);
// initailize a request instance

static void free_request(request* reqP);
// free resources used by a request instance

static int handle_read(request* reqP);
// return 0: socket ended, request done.
// return 1: success, message (without header) got this time is in reqP->buf with reqP->buf_len bytes. read more until got <= 0.
// It's guaranteed that the header would be correctly set after the first read.
// error code:
// -1: client connection error
int Read_Account(int file_fd, int idx){
    if(lseek(file_fd, sizeof(Account)*(idx-1), SEEK_SET)== -1){
        fprintf(stderr, "read account wrong\n");
        exit(1);
    }
    Account temp;
    read(file_fd, &temp, sizeof(temp));
    return temp.balance;
}
void Write_Account(int file_fd, int idx, int cost){
    if(lseek(file_fd, sizeof(Account)*(idx-1), SEEK_SET)== -1){
        fprintf(stderr, "write account wrong\n");
        exit(1);
    }
    Account temp;
    temp.id = idx;
    temp.balance = cost;
    write(file_fd, &temp, sizeof(temp));
    return;
}

int main(int argc, char** argv) {
    int i, ret;

    struct sockaddr_in cliaddr;  // used by accept()
    int clilen;

    int conn_fd;  // fd for a new connection with client
    int file_fd;  // fd for file that we open for reading
    char buf[512];
    int buf_len;

    // Parse args.
    if (argc != 2) {
        fprintf(stderr, "usage: %s [port]\n", argv[0]);
        exit(1);
    }

    // Initialize server
    init_server((unsigned short) atoi(argv[1]));

    fd_set master;
    fd_set read_fds;
    FD_ZERO(&master);
    FD_ZERO(&read_fds);
    // Get file descripter table size and initize request table
    maxfd = getdtablesize();
    requestP = (request*) malloc(sizeof(request) * maxfd);
    if (requestP == NULL) {
        ERR_EXIT("out of memory allocating all requests");
    }
    for (i = 0; i < maxfd; i++) {
        init_request(&requestP[i]);
    }
    requestP[svr.listen_fd].conn_fd = svr.listen_fd;
    strcpy(requestP[svr.listen_fd].host, svr.hostname);

    int listener = svr.listen_fd;
    FD_SET(listener, &master);
    // Loop for handling connections
    fprintf(stderr, "\nstarting on %.80s, port %d, fd %d, maxconn %d...\n", svr.hostname, svr.port, svr.listen_fd, maxfd);
    // add
    file_fd = open("account_list", O_RDWR);
    int lock[20];
    for(int i = 0; i < 20; i++){
        lock[i] = 0;
    }
    while (1){
        // TODO: Add IO multiplexing
        read_fds = master; // 複製 master
        if(select(maxfd, &read_fds, NULL, NULL, NULL) == -1) {
            perror("select");
            exit(4);
        }
        for(int i = 0; i < maxfd; i++){
            if(FD_ISSET(i, &read_fds)){
                if(i == listener){
                    clilen = sizeof(cliaddr);
                    conn_fd = accept(svr.listen_fd, (struct sockaddr*)&cliaddr, (socklen_t*)&clilen);
            
                    if (conn_fd < 0) {
                        if (errno == EINTR || errno == EAGAIN) continue;  // try again
                        if (errno == ENFILE) {
                            (void) fprintf(stderr, "out of file descriptor table ... (maxconn %d)\n", maxfd);
                            continue;
                        }
                        ERR_EXIT("accept")
                    }
                    FD_SET(conn_fd, &master);
                    requestP[conn_fd].conn_fd = conn_fd;
                    strcpy(requestP[conn_fd].host, inet_ntoa(cliaddr.sin_addr));
                    fprintf(stderr, "getting a new request... fd %d from %s\n", conn_fd, requestP[conn_fd].host);
                }
                else if(requestP[i].wait_for_write == 0){
                    ret = handle_read(&requestP[i]); // parse data from client to requestP[conn_fd].buf
                    if (ret < 0) {
                        fprintf(stderr, "bad request from %s\n", requestP[i].host);
                        continue;
                    }
                    requestP[i].item = atoi(requestP[i].buf);

                    struct flock fl;
                    fl.l_type   = F_WRLCK;  /* F_RDLCK，F_WRLCK，F_UNLCK    */
                    fl.l_whence = SEEK_SET; /* SEEK_SET，SEEK_CUR，SEEK_END */
                    fl.l_start  = sizeof(Account)*(requestP[i].item - 1);        /* Offset from l_whence         */
                    fl.l_len    = sizeof(Account);        /* length，0 = to EOF           */
                    
                    if(fcntl(file_fd, F_SETLK, &fl) < 0 || lock[requestP[i].item - 1] == 1){
                        sprintf(buf,"This account is locked.\n");
                        write(requestP[i].conn_fd, buf, strlen(buf));
                        
                        FD_CLR(i, &master);
                        close(requestP[i].conn_fd);
                        free_request(&requestP[i]);
                    }
                    else{
                        sprintf(buf,"This account is modifiable.\n");
                        write(requestP[i].conn_fd, buf, strlen(buf));
                        requestP[i].wait_for_write = 1;
                        lock[requestP[i].item - 1] = 1;
                    }
                }
                else{
                    ret = handle_read(&requestP[i]); // parse data from client to requestP[conn_fd].buf
                    if (ret < 0) {
                        fprintf(stderr, "bad request from %s\n", requestP[i].host);
                        continue;
                    }
                    //save
                    if(strstr(requestP[i].buf, "save") != NULL){
                        char *token;
                        token = strtok(requestP[i].buf, " ");
                        token = strtok(NULL, " \n");
                        int cost = atoi(token);
                        if(cost < 0){
                            sprintf(buf,"Operation failed.\n");
                            write(requestP[i].conn_fd, buf, strlen(buf));    
                        }
                        else{
                            Write_Account(file_fd, requestP[i].item, cost + Read_Account(file_fd, requestP[i].item));
                        }
                    }
                    //withdraw
                    else if(strstr(requestP[i].buf, "withdraw") != NULL){
                        char *token;
                        token = strtok(requestP[i].buf, " ");
                        token = strtok(NULL, " \n");
                        int cost = atoi(token);
                        if(cost > Read_Account(file_fd, requestP[i].item)){
                            sprintf(buf,"Operation failed.\n");
                            write(requestP[i].conn_fd, buf, strlen(buf));    
                        }
                        else{
                            Write_Account(file_fd, requestP[i].item, Read_Account(file_fd, requestP[i].item) - cost);
                        }
                    }
                    //transfer
                    else if(strstr(requestP[i].buf, "transfer") != NULL){
                        char *token;
                        token = strtok(requestP[i].buf, " ");
                        token = strtok(NULL, " \n");
                        int item = atoi(token);
                        token = strtok(NULL, " \n");
                        int cost = atoi(token);
                        if(cost < 0 || Read_Account(file_fd, requestP[i].item) < cost || item > 20 || item < 1){
                            sprintf(buf,"Operation failed.\n");
                            write(requestP[i].conn_fd, buf, strlen(buf));
                        }
                        else{
                            Write_Account(file_fd, requestP[i].item, Read_Account(file_fd, requestP[i].item) - cost);
                            Write_Account(file_fd, item, Read_Account(file_fd, item) + cost);
                        }   
                    }
                    //balance
                    else if(strstr(requestP[i].buf, "balance") != NULL){
                        char *token;
                        token = strtok(requestP[i].buf, " ");
                        token = strtok(NULL, " \n");
                        int cost = atoi(token);
                        if(cost < 0){
                            sprintf(buf,"Operation failed.\n");
                            write(requestP[i].conn_fd, buf, strlen(buf));    
                        }
                        else{
                            Write_Account(file_fd, requestP[i].item, cost);
                        }
                    }

                    struct flock fl;
                    fl.l_type   = F_UNLCK;  /* F_RDLCK，F_WRLCK，F_UNLCK    */
                    fl.l_whence = SEEK_SET; /* SEEK_SET，SEEK_CUR，SEEK_END */
                    fl.l_start  = sizeof(Account)*(requestP[i].item - 1);        /* Offset from l_whence         */
                    fl.l_len    = sizeof(Account);        /* length，0 = to EOF           */
                    fcntl(file_fd, F_SETLK, &fl);
                    lock[requestP[i].item - 1] = 0;
                    FD_CLR(i, &master);
                    close(requestP[i].conn_fd);
                    free_request(&requestP[i]);
                    
                    //sprintf(buf,"%s : %s\n",accept_write_header,requestP[conn_fd].buf);
                    //write(requestP[conn_fd].conn_fd, buf, strlen(buf));
                }
            }
        }
    }
    close(file_fd);
    free(requestP);
    return 0;
}


// ======================================================================================================
// You don't need to know how the following codes are working
#include <fcntl.h>

static void* e_malloc(size_t size);


static void init_request(request* reqP) {
    reqP->conn_fd = -1;
    reqP->buf_len = 0;
    reqP->item = 0;
    reqP->wait_for_write = 0;
}

static void free_request(request* reqP) {
    /*if (reqP->filename != NULL) {
        free(reqP->filename);
        reqP->filename = NULL;
    }*/
    init_request(reqP);
}

// return 0: socket ended, request done.
// return 1: success, message (without header) got this time is in reqP->buf with reqP->buf_len bytes. read more until got <= 0.
// It's guaranteed that the header would be correctly set after the first read.
// error code:
// -1: client connection error
static int handle_read(request* reqP) {
    int r;
    char buf[512];

    // Read in request from client
    r = read(reqP->conn_fd, buf, sizeof(buf));
    if (r < 0) return -1;
    if (r == 0) return 0;
    char* p1 = strstr(buf, "\015\012");
    int newline_len = 2;
    // be careful that in Windows, line ends with \015\012
    if (p1 == NULL) {
        p1 = strstr(buf, "\012");
        newline_len = 1;
        if (p1 == NULL) {
            ERR_EXIT("this really should not happen...");
        }
    }
    size_t len = p1 - buf + 1;
    memmove(reqP->buf, buf, len);
    reqP->buf[len - 1] = '\0';
    reqP->buf_len = len-1;
    return 1;
}

static void init_server(unsigned short port) {
    struct sockaddr_in servaddr;
    int tmp;

    gethostname(svr.hostname, sizeof(svr.hostname));
    svr.port = port;

    svr.listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (svr.listen_fd < 0) ERR_EXIT("socket");

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    tmp = 1;
    if (setsockopt(svr.listen_fd, SOL_SOCKET, SO_REUSEADDR, (void*)&tmp, sizeof(tmp)) < 0) {
        ERR_EXIT("setsockopt");
    }
    if (bind(svr.listen_fd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        ERR_EXIT("bind");
    }
    if (listen(svr.listen_fd, 1024) < 0) {
        ERR_EXIT("listen");
    }
}

static void* e_malloc(size_t size) {
    void* ptr;

    ptr = malloc(size);
    if (ptr == NULL) ERR_EXIT("out of memory");
    return ptr;
}


#endif
