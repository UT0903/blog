#include "opencv2/opencv.hpp"
#include <iostream>
#include <sys/socket.h> 
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h> 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <deque>
#include <mutex>
#include <thread>
#include "msg_type.h"
#define MAXBUFFERSIZE 10000
using namespace std;
using namespace cv;

static void init_client(char *ip_port);
uchar* recv_frame(int client_fd);

int client_fd;
std::mutex mut;
std::deque<MESSAGE> msg_buf;
int recv_finish;
void load_msg(){
    MESSAGE msg;
    while(1){
        if(msg_buf.size() < MAXBUFFERSIZE){
            if(recv_msg(client_fd, &msg) == FINISH){
                fprintf(stderr, "recv finish\n");
                recv_finish = 1;
                break;
            }
            fprintf(stderr, "new in\n");
            mut.lock();
            msg_buf.push_back(msg);
            mut.unlock();
        }
    }
}

int main(int argc , char *argv[])
{
    if(argc != 2){
        fprintf(stderr, "usage: ./client [ip:port]\n");
        exit(1);
    }

    init_client(argv[1]);
    while(1){
        fprintf(stderr, "Please enter new order\n");
        char order[BUFF_SIZE];
        fscanf(stdin, "%s", order);
        if(strcmp(order, "ls") == 0){ //LS
            send_msg(client_fd, new_req(LS_REQ, "lalala"));
            
            MESSAGE msg;
            recv_msg(client_fd, &msg);
            fprintf(stdout, "%s\n", msg.content.ls_info);
            if(recv_msg(client_fd, &msg) != FINISH){
                ERR_EXIT("Why no FINISH message???");
            }
            fprintf(stderr, "recv FINISH\n");
        }
        else if(strcmp(order, "put") == 0){ //PUT <filename>
            char file_name[BUFF_SIZE];
            fscanf(stdin, "%s", file_name);
            send_msg(client_fd, new_req(UP_REQ, file_name));
            //upload file
            char cli_path[100] = "./client_folder/";
            strcat(cli_path, file_name);
            read_and_send(client_fd, cli_path);
        }
        else if(strcmp(order, "get") == 0){ //GET <filename>
            char file_name[BUFF_SIZE];
            fscanf(stdin, "%s", file_name);
            send_msg(client_fd, new_req(DOWN_REQ, file_name));

            //download file
            char cli_path[100] = "./client_folder/";
            strcat(cli_path, file_name);
            recv_and_write(client_fd, cli_path);
        }
        else if(strcmp(order, "play") == 0){
            char file_name[BUFF_SIZE];
            fscanf(stdin, "%s", file_name);
            fprintf(stderr, "want to play %s\n", file_name);
            send_msg(client_fd, new_req(PLAY_REQ, file_name));
            //download file and play
            MESSAGE msg;
            if(recv_msg(client_fd, &msg) != WIDTH_HEIGHT){
                ERR_EXIT("WHY NO WIDTH_HEIGHT???");
            }
            //fprintf(stderr, "debug recv No: %d\n", debug++);
            Mat imgClient;
            imgClient = Mat::zeros(msg.content.wh.height, msg.content.wh.width, CV_8UC3);
            if(!imgClient.isContinuous()){
                 imgClient = imgClient.clone();
            }
            fprintf(stderr, "frame size: %d, %d\n", msg.content.wh.height, msg.content.wh.width);
            //create thread
            thread t1(load_msg);

            while(1){
                while(msg_buf.size() <= 0){
                    if(recv_finish) goto STOP;
                };
                ///critical section
                mut.lock();
                msg = msg_buf.front();
                msg_buf.pop_front();
                mut.unlock();
                ///critical section
                if(msg.type == FINISH){
                    fprintf(stderr, "recv FINISH\n");
                    destroyAllWindows();
                    break;
                }
                else if(msg.type != IMG_SIZE){
                    ERR_EXIT("WHY NO IMG_SIZE???");
                }

                int imgSize = msg.content.imgSize;
                
                uchar *buf = imgClient.data;
                for(int i = 0; i < imgSize; i += BUFF_SIZE){
                    while(msg_buf.size() <= 0){
                        if(recv_finish) goto STOP;
                    };
                    fprintf(stderr, "new play\n");
                    ///critical section
                    mut.lock();
                    msg = msg_buf.front();
                    msg_buf.pop_front();
                    mut.unlock();
                    ///critical section
                    //recv_msg(client_fd, &msg);
                    //fprintf(stderr, "debug recv No: %d\n", debug++);
                    memcpy(buf + i, msg.content.frame, min(BUFF_SIZE, imgSize - i));
                }
                imshow("Video", imgClient);
                char c = (char)waitKey(33.3333);
                if(c == 27){
                    fprintf(stderr, "ESC\n");
                    send_msg(client_fd, new_req(ESC_REQ, "lalala"));
                    while(1){
                        while(msg_buf.size() <= 0){
                            if(recv_finish) goto STOP;
                        };
                        fprintf(stderr, "new play\n");
                        ///critical section
                        mut.lock();
                        msg_buf.pop_front();
                        mut.unlock();
                    }

                    fprintf(stderr, "ESC finish\n");
                    break;
                }
            }
STOP:
            t1.join();
            msg_buf.clear();
            destroyAllWindows();
            recv_finish = 0;
        }
        else if(strcmp(order, "exit") == 0){
            send_msg(client_fd, new_req(EXIT, "lalala"));
            break;
        }
        else{
            fprintf(stderr, "No this command\n");
        }

    }
    

    printf("close Socket\n");
    close(client_fd);
    return 0;
}

static void init_client(char *ip_port) {
    const char *delim = ":";

    if ((client_fd = socket(AF_INET , SOCK_STREAM , 0)) == -1)
        ERR_EXIT("Fail to create a socket.");

    struct sockaddr_in info;
    bzero(&info,sizeof(info));

    info.sin_family = PF_INET;
    info.sin_addr.s_addr = inet_addr(strtok(ip_port, delim));
    info.sin_port = htons(atoi(strtok(NULL, delim)));

    if(connect(client_fd,(struct sockaddr *)&info,sizeof(info)) == -1)
        ERR_EXIT("Connection error");
}
