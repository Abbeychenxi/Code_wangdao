/*************************************************************************
	> File Name: ftp.h
	> Author: Comst
	> Mail:750145240@qq.com 
	> Created Time: 2014年04月05日 星期六 14时37分59秒
 ************************************************************************/
#ifndef __FTP_H__
#define __FTP_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <fcntl.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#define BUF_SIZE 8*1024
typedef int socket_t ;
socket_t socket_server(char* ip, char* port);
int recvn(socket_t fd_recv, char* recv_buf, int len );
int readn(int fd_read, char* read_buf, int len );
int sendn(socket_t fd_send, char* send_buf, int len );
int writen(int fd_write, char* write_buf, int len );
socket_t socket_client(char* ip, char* port);
void trim_space(char* src);
int upload(socket_t fd_up, char* file_name);
int download(socket_t fd_down, char* file_name);
#endif


