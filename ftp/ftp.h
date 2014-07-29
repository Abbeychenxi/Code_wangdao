#ifndef __FTP_H__
#define __FTP_H__
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <dirent.h>
#include <netdb.h>
#include <signal.h>
#include <errno.h>
#include <sys/shm.h>
#include <unistd.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>
typedef struct sockaddr_in SA;
#define MSG_SIZE 8188
#define MSG_LEN (8192 - MSG_SIZE)
typedef struct tag
{
    int s_len;
    char s_buf[MSG_SIZE];
}MSG;

void my_cd(int argc,char argv[3][10],int fd_client);
void my_ls(int argc,char argv[3][10],int fd_client);
void my_ls2(int argc, char argv[3][10], int fd_client);
void my_mv(int argc,char argv[3][10],int fd_client);
void my_pwd(int argc,char argv[3][10],int fd_client);

void mode_to_str(mode_t md, char* str);
void format(char* p);

void handle_request(char* buf, int fd_client);

void download_file(char req[3][10],int fd_client);
void upload_file(char req[3][10],int fd_client);
#endif