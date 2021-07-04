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

void send_frame(int client_fd, int imgSize, const uchar *data);
static void init_server(unsigned short port);

int main(int argc, char ** argv){
    if(argc != 2){
        fprintf(stderr, "usage: ./server [port]\n");
        exit(1);
    }

    int client_fd;                               

    init_server((unsigned short) atoi(argv[1]));
    
    while(1){
        struct sockaddr_in clientAddr;
        fprintf(stderr, "Waiting for connections...\n");
        int addrLen = sizeof(struct sockaddr_in); 
        if((client_fd = accept(svr.listen_fd, (struct sockaddr *)&clientAddr, (socklen_t*)&addrLen)) < 0)
            ERR_EXIT("accept failed!");
        fprintf(stderr, "Connection accepted\n");
        while(1){    
            MESSAGE msg;
            recv_msg(client_fd, &msg);

            if(msg.type == LS_REQ){
                fprintf(stderr, "LS_REQ\n");
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

                send_msg(client_fd, new_LS(ls_info));
                send_msg(client_fd, new_FINISH());
            }
            else if(msg.type == PLAY_REQ){
                Mat imgServer;
                VideoCapture cap("./tmp.mpg");
                int width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
                int height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
                fprintf(stderr, "video width: %d height: %d\n", width, height);
                imgServer = Mat::zeros(height, width, CV_8UC3);
                if(!imgServer.isContinuous()){
                    imgServer = imgServer.clone();
                }
                send_msg(client_fd, new_WH(width, height)); //send width and height first
                while(1){
                    cap >> imgServer;
                    if (imgServer.empty()) break;
                    int imgSize = imgServer.total() * imgServer.elemSize();
                    fprintf(stderr, "imgSize: %d\n", imgSize);
                    
                    MESSAGE msg;
                    msg.type = IMG_SIZE;
                    msg.content.imgSize = imgSize;
                    send_msg(client_fd, msg);
                    
                    msg.type = FRAME;
                    for(int i = 0; i < imgSize; i += BUFF_SIZE){
                        memcpy(msg.content.frame, imgServer.data + i, min(BUFF_SIZE, imgSize - i));
                        send_msg(client_fd, msg);
                    }
                    
                }
                cap.release();
                send_msg(client_fd, new_FINISH());
                fprintf(stderr, "send FINISH\n");
            }
            else if(msg.type == DOWN_REQ){
                char svr_path[100] = "./server_folder/";
                strcat(svr_path, msg.content.file_name);
                read_and_send(client_fd, svr_path);
            }
            else if(msg.type == UP_REQ){
                char svr_path[100] = "./server_folder/";
                strcat(svr_path, msg.content.file_name);
                recv_and_write(client_fd, svr_path);
            }
            else if(msg.type == EXIT){
                close(client_fd);
                fprintf(stderr, "wait for next connection\n");
                break;
            }
        }
    }
    return 0;
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


