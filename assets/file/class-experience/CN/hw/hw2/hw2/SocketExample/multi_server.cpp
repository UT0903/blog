#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h> 
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include "msg_type.h"

using namespace std;
using namespace cv;

typedef struct {
    char hostname[512];  // server's hostname
    unsigned short port;  // port to listen
    int listen_fd;  // fd to wait for a new connection
} server;
server svr;

typedef struct {
    MSG_TYPE type;
    char info[BUFF_SIZE];
    FILE *fp;
    int is_connected;
    VideoCapture *cap;
    Mat *imgServer;
} REQUEST;

std::vector<REQUEST> requestP;

static void init_request(int num);
void send_frame(int client_fd, int imgSize, const unsigned char *data);
static void init_server(unsigned short port);

int main(int argc, char ** argv){

    if(argc != 2){
        fprintf(stderr, "usage: ./server [port]\n");
        exit(1);
    }
    fprintf(stderr, "size of MESSAGE: %lu\n", sizeof(MESSAGE));
    struct sockaddr_in clientAddr;                              

    init_server((unsigned short) atoi(argv[1]));

    fd_set master;
    fd_set read_fds;
    FD_ZERO(&master);
    FD_ZERO(&read_fds);

    // Get file descripter table size and initize request table
    int maxfd = getdtablesize();

    for(int i = 0; i < maxfd; i++){
        REQUEST r;
        requestP.push_back(r);
        init_request(i);
    }

    requestP[svr.listen_fd].type = SERVER;
    //strcpy(requestP[svr.listen_fd].host, svr.hostname);

    FD_SET(svr.listen_fd, &master);
    int debug = 0;
    // Loop for handling connections
    fprintf(stderr, "\nstarting on %.80s, port %d, fd %d, maxconn %d...\n", svr.hostname, svr.port, svr.listen_fd, maxfd);
    struct timeval timeout = {0,0};
    while(1){
        read_fds = master; // 複製 master
        if(select(maxfd + 1, &read_fds, NULL, NULL, &timeout) == -1) {
            perror("select");
            exit(4);
        }
        //fprintf(stderr, "new cycle\n");
        if(FD_ISSET(svr.listen_fd, &read_fds)){ //first in, accept
            int addrLen = sizeof(struct sockaddr_in); 
            int client_fd; 
            if((client_fd = accept(svr.listen_fd, (struct sockaddr *)&clientAddr, (socklen_t*)&addrLen)) < 0)
                ERR_EXIT("accept failed!");
            fprintf(stderr, "Connection accepted fd: %d\n", client_fd);
            FD_SET(client_fd, &master);
            requestP[client_fd].is_connected = 1;
        }
        for(int i = 0; i < maxfd; i++){ //deal with none finish fds
            if(i == svr.listen_fd) continue;
            if(requestP[i].is_connected){ 
                if(FD_ISSET(i, &read_fds) && requestP[i].type == NONE){
                    MESSAGE msg;  //get request info
                    recv_msg(i, &msg);
                    requestP[i].type = msg.type;
                    strcpy(requestP[i].info, msg.content.file_name);
                }

                if(requestP[i].type == LS_REQ){
                    fprintf(stderr, "LS_REQ, fd:%d\n", i);
                    char ls_info[BUFF_SIZE] = {};
                    DIR *dir;
                    struct dirent *rent;
                    dir = opendir("./server_folder");
                    while((rent=readdir(dir))){
                        char fn[100];
                        strcpy(fn,rent->d_name);
                        if (fn[0]!='.' && fn){
                            strcat(ls_info, fn);
                            strcat(ls_info, " ");
                        }   
                    }
                    send_msg(i, new_LS(ls_info));
                    send_msg(i, new_FINISH());
                    init_request(i);
                }
                else if(requestP[i].type == UP_REQ && FD_ISSET(i, &read_fds)){
                    fprintf(stderr, "UP_REQ, fd:%d\n", i); 
                    if(requestP[i].fp == NULL){ // upload request
                        char svr_path[100] = "./server_folder/";
                        strcat(svr_path, requestP[i].info);
                        requestP[i].fp = fopen(svr_path, "w+");
                        fprintf(stderr, "open file\n");
                    }
                    
                    //recv_and_write(client_fd, svr_path);
                    MESSAGE msg;
                    if(recv_msg(i, &msg) == FINISH){
                        fprintf(stderr, "recv FINISH\n");
                        fclose(requestP[i].fp);
                        init_request(i);
                    }
                    else{
                        fwrite(msg.content.data.data, 1, msg.content.data.size, requestP[i].fp);
                    }
                }
                else if(requestP[i].type == DOWN_REQ){
                    fprintf(stderr, "DOWN_REQ, fd:%d\n", i); 
                    if(requestP[i].fp == NULL){ // download request
                        char svr_path[100] = "./server_folder/";
                        strcat(svr_path, requestP[i].info);
                        if((requestP[i].fp = fopen(svr_path, "r")) == NULL){
                            fprintf(stderr, "No such file\n");
                        }
                        fprintf(stderr, "open file\n");
                    }
                    if(feof(requestP[i].fp)){
                        send_msg(i, new_FINISH());
                        fprintf(stderr, "send %s FINISH\n", requestP[i].info);
                        fclose(requestP[i].fp);
                        init_request(i);
                    }
                    else{
                        MESSAGE msg;
                        msg.type = DATA; 
                        msg.content.data.size = fread(msg.content.data.data, 1, BUFF_SIZE, requestP[i].fp);
                        send_msg(i, msg);
                        fprintf(stderr, "send\n");
                    }
                }
                else if(requestP[i].type == PLAY_REQ){
                    fprintf(stderr, "PLAY_REQ fd: %d\n", i);
                    if(requestP[i].cap == NULL){
                        char svr_path[100] = "./server_folder/";
                        strcat(svr_path, requestP[i].info);
                        requestP[i].cap = new VideoCapture(svr_path);
                        int cap_width = (*requestP[i].cap).get(CV_CAP_PROP_FRAME_WIDTH);
                        int cap_height = (*requestP[i].cap).get(CV_CAP_PROP_FRAME_HEIGHT);
                        send_msg(i, new_WH(cap_width, cap_height)); //send width and height first
                        //fprintf(stderr, "debug send No: %d\n", debug++);
                        requestP[i].imgServer = new Mat(cap_height, cap_width, CV_8UC3);//Mat::zeros(cap_height, cap_width, CV_8UC3);
                        if(!(*requestP[i].imgServer).isContinuous()){
                            (*requestP[i].imgServer) = (*requestP[i].imgServer).clone();
                        }
                    }
                    else if(FD_ISSET(i, &read_fds)){
                        fprintf(stderr, "something in buffer\n");
                        MESSAGE peek_msg;
                        if(peek_recv_msg(i, &peek_msg) == ESC_REQ){ //recv ESC signal
                            recv_msg(i, &peek_msg);
                            fprintf(stderr, "ESC_REQ fd: %d\n", i);
                            send_msg(i, new_FINISH());
                            //fprintf(stderr, "debug send No: %d\n", debug++);
                            (*requestP[i].cap).release();
                            //delete requestP[i].cap;
                            fprintf(stderr, "send FINISH\n");
                            init_request(i);
                            continue;
                        }
                    }

                    
                    (*requestP[i].cap) >> (*requestP[i].imgServer);

	                if((*requestP[i].imgServer).empty()){
	                	(*requestP[i].cap).release();
	                	//delete requestP[i].cap;
	                	send_msg(i, new_FINISH());
	                	fprintf(stderr, "send FINISH\n");
                        init_request(i);
	                }
	                else{
	                	int imgSize = (*requestP[i].imgServer).total() * (*requestP[i].imgServer).elemSize();
	                    //fprintf(stderr, "imgSize: %d\n", imgSize);
	                    MESSAGE msg;
	                    msg.type = IMG_SIZE;
	                    msg.content.imgSize = imgSize;
	                    send_msg(i, msg);
	                    //fprintf(stderr, "debug send No: %d\n", debug++);
	                    msg.type = FRAME;
	                    for(int k = 0; k < imgSize; k += BUFF_SIZE){
	                        memcpy(msg.content.frame, (*requestP[i].imgServer).data + k, min(BUFF_SIZE, imgSize - k));
	                        send_msg(i, msg);
                            //fprintf(stderr, "debug send No: %d\n", debug++);
	                    }
	                }         
	            }
                else if(requestP[i].type == EXIT){
                    FD_CLR(i, &master);
                    close(i);
                    requestP[i].is_connected = 0;
                    init_request(i);
                    fprintf(stderr, "connection close\n");
                }
            }
        }
    }
}

static void init_request(int num){
    requestP[num].type = NONE;
    requestP[num].fp = NULL;
    //free(requestP[num].cap);
    requestP[num].cap = NULL;
    //free(requestP[num].imgServer);
    requestP[num].imgServer = NULL;
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