#define BUFF_SIZE 3000
#define ERR_EXIT(a) { perror(a); exit(1); }

typedef struct{
    int width;
    int height;
}WH;

typedef struct{
    char data[BUFF_SIZE];
    int size;
}DA;
typedef union{
    WH wh; // width and height of the frame
    unsigned char frame[BUFF_SIZE];
    int imgSize;
    char ls_info[BUFF_SIZE]; // ls info
    char file_name[BUFF_SIZE];
    DA data;
}MSG;

typedef enum{
    EXIT,
    WIDTH_HEIGHT,
    IMG_SIZE,
    DATA,
    FRAME,
    LS_INFO,
    LS_REQ,
    UP_REQ,
    DOWN_REQ,
    PLAY_REQ,
    FINISH,
    SERVER,
    NONE,
    ESC_REQ
}MSG_TYPE;

typedef struct{
    MSG_TYPE type;
    MSG content;
}MESSAGE;


void send_msg(int client_fd, MESSAGE msg){
    if(send(client_fd, &msg, sizeof(MESSAGE), 0) < 0)
        ERR_EXIT("send failed");
}
int recv_msg(int client_fd, MESSAGE *msg){
    if (recv(client_fd, msg, sizeof(MESSAGE), MSG_WAITALL) < 0){
        ERR_EXIT("recv failed");
    }
    return msg->type;
}
int peek_recv_msg(int client_fd, MESSAGE *msg){
    if (recv(client_fd, msg, sizeof(MESSAGE), MSG_PEEK | MSG_DONTWAIT) < 0){
        ERR_EXIT("recv failed");
    }
    return msg->type;
}
MESSAGE new_LS(const char *content){
    MESSAGE msg;
    msg.type = LS_INFO;
    strcpy(msg.content.ls_info, content);
    return msg;
}
MESSAGE new_FINISH(){
    MESSAGE msg;
    msg.type = FINISH;
    return msg;
}
MESSAGE new_WH(int width, int height){
    MESSAGE msg;
    msg.type = WIDTH_HEIGHT;
    msg.content.wh.width = width;
    msg.content.wh.height = height;
    return msg;
}

MESSAGE new_req(MSG_TYPE req_type, const char *more_info){
    MESSAGE msg;
    msg.type = req_type;
    strcpy(msg.content.file_name, more_info);
    return msg;
}

void read_and_send(int client_fd, const char *file_name){
    FILE *fp;
    if ((fp = fopen(file_name, "r")) == NULL){
        fprintf(stderr, "No such file\n");
    }
    //int i = 0;
    while(!feof(fp)) {
        MESSAGE msg;
        msg.type = DATA; 
        msg.content.data.size = fread(msg.content.data.data, 1, BUFF_SIZE, fp);
        send_msg(client_fd, msg);
        //fprintf(stderr, "%d\n", i++);
    }
    fclose(fp);
    send_msg(client_fd, new_FINISH());
    fprintf(stderr, "send FINISH\n");
}

void recv_and_write(int client_fd, const char *file_name){
    FILE *fp = fopen(file_name, "w+");
    while(1){
        MESSAGE msg;
        if(recv_msg(client_fd, &msg) == FINISH){
            fprintf(stderr, "recv FINISH\n");
            break;
        }
        else{
            //fprintf(stderr, "get file\n");
            fwrite(msg.content.data.data, 1, msg.content.data.size, fp);
        }
    }
    fclose(fp);
}