
#ifndef SOCKET
#define SOCKET

#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>

#endif

void set_addr(struct sockaddr_in* addr, char * ip, unsigned short port);

int socket_init_udp(struct sockaddr_in s_address);   //返回socket文件描述符

int socket_init_tcp(struct sockaddr_in s_address);  

int my_accept(int fd_socket, struct sockaddr_in* client_addr);

void my_connect(int fd_socket, struct sockaddr_in * server_addr);

void recv_file_tcp(char * path, int fd_source);

void send_file_tcp(char *path, int fd_client);
