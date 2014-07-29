#include "socket_tcp.h"
#include "server_main.h"


void set_addr(struct sockaddr_in* addr, char * ip, unsigned short port)
{
    (*addr).sin_family = AF_INET;
    (*addr).sin_port = htons(port);
    (*addr).sin_addr.s_addr = inet_addr(ip);
}



int socket_init_tcp(struct sockaddr_in s_address)           //没有listen
{
    int fd_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (fd_socket == -1) ERR_EXIT("Socket!!!");

    if (bind(fd_socket, (struct sockaddr *)&s_address,
             sizeof(struct sockaddr_in)) == -1)
    {
        ERR_EXIT("Bind!!!");
    }
    return fd_socket;                    //返回socket文件描述符
}



int socket_init_udp(struct sockaddr_in s_address)
{
    int fd_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd_socket == -1) ERR_EXIT("Socket!!!");

    if (bind(fd_socket, (struct sockaddr *)&s_address,
             sizeof(struct sockaddr_in)) == -1)
    {
        ERR_EXIT("Bind!!!");
    }
    return fd_socket;      
}




int my_accept(int fd_socket, struct sockaddr_in * client_addr)
{
    unsigned int addrlen = sizeof(struct sockaddr);
    int new_fd = accept(fd_socket, (struct sockaddr *)client_addr, &addrlen);
    if(-1 == new_fd)
    {
        ERR_EXIT("Accept!!!");
    }
    return new_fd;
}

void my_connect(int fd_socket, struct sockaddr_in * server_addr)
{    
    if(connect(fd_socket,
        (struct sockaddr*)server_addr, sizeof(struct sockaddr))==-1)
    {
        ERR_EXIT("Connect!!!");
    }
}




// void send_file_tcp(char *path, int fd_client)
// {
//     int file = open(path, O_RDONLY);
//     unsigned char head = 0; // 标注发送长度，单位：B
//     int count = 0, check;

//     if (-1 == file)
//     {
//         char error[20] = "No such file!";
//         head = strlen(error) ;
//         send(fd_client, &head, 1 , 0);
//         send(fd_client, error , strlen(error) , 0);
//         close(file);
//     }

//     char buff[256], sig;
//     while (memset(buff, 0, 256), (head = read(file, buff, 255)) > 0)
//     {
//         send(fd_client, &head, 1 , 0);
//         send(fd_client, buff, strlen(buff) , 0);
//         count += head;
//         recv(fd_client, &sig, 1, 0);
//     }
//     printf("Totally %d kB!\n", count);
//     close(file);
// }

void send_file_tcp(char *path, int fd_client)
{
    int file = open(path, O_RDONLY);
    unsigned int head = 0; // 标注发送长度，单位：B
    int count = 0, check;

    if (-1 == file)
    {
        char error[20] = "No such file!";
        head = strlen(error) ;
        send(fd_client, &head, sizeof(int) , 0);
        send(fd_client, error , strlen(error) , 0);
        close(file);
    }

    char buff[1025], sig;
    while (memset(buff, 0, 1025), (head = read(file, buff, 1024)) > 0)
    {
        if(-1 ==send(fd_client, &head, sizeof(int) , 0))
            ERR_EXIT("send1!!!");

        if(-1 ==send(fd_client, buff, head , 0))
            ERR_EXIT("send2!!!");

        count += head;
        if(-1 ==recv(fd_client, &sig, 1, 0))
            ERR_EXIT("recv!!!");

    }
    printf("Totally %d kB!\n", count);
    close(file);
}




// void recv_file_tcp(char * path, int fd_source)
// {
//     int file = open(path, O_WRONLY|O_CREAT, 0666);
//     char buff[256];
//     unsigned char head = 0; // 标注发送长度，单位：B
//     int count = 0;

//     do
//     {
//         memset(buff, 0, 256);
//         recv(fd_source, &head, 1, 0);
//         recv(fd_source, buff, head, 0);
//         write(file, buff, head);
//         count += head;
//         send(fd_source, "1", 1, 0);
//     } while(head == 255);

//     printf("Totally %d kB!\n", count);
//     close(file);   
// }


void recv_file_tcp(char * path, int fd_source)
{
    int file = open(path, O_WRONLY|O_CREAT, 0666);
    char buff[1025];
    unsigned int head = 0; // 标注发送长度，单位：B
    int count = 0;

    do
    {
        memset(buff, 0, 1025);
// printf("0,\n");
        if(-1 ==recv(fd_source, &head, sizeof(int), 0))
            ERR_EXIT("recv1!!!");
// printf("1\n");
        if(-1 ==recv(fd_source, buff, head, 0))
            ERR_EXIT("recv2!!!");
// printf("2\n");
        if(-1 == write(file, buff, head))
            ERR_EXIT("write!!!");
// printf("3\n");
        count += head;
        if(-1 ==send(fd_source, "1", 1, 0))
            ERR_EXIT("send!!!");
// printf("4\n");
    } while(head == 1024);

    printf("Totally %d kB!\n", count);
    close(file);   
}









