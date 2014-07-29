#include "ftp.h"
#define MYIP "192.168.1.3"
#define MYPORT 8888
#define MYKEY 12345
#define SIZE 10240


int main(int argc, char const *argv[])
{
    char buf[1024];
    bzero(buf,1024);

    int fd_server,fd_client;
    socklen_t server_len,client_len;
    SA server_addr,client_addr;
    printf("●～●～●～●～server initialization●～●～●～●～\n");
    fd_server=socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family= AF_INET;
    server_addr.sin_port= htons(MYPORT);
    server_addr.sin_addr.s_addr= inet_addr(MYIP);
    server_len= sizeof(SA);
    //允许重复使用本地地址和套接字绑定
    int on = 1;
    setsockopt(fd_server, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    if (bind(fd_server,(struct sockaddr*)&server_addr, server_len)==-1)
    {
        perror("bind");
        exit(-1);
    }

    if (listen(fd_server, 5)== -1)
    {
        perror("listen");
        exit(-1);
    }

    client_len= sizeof(client_addr);
    pid_t ppid,pid;

    while(1)
    {
        if ((fd_client=accept(fd_server,(struct sockaddr*)&client_addr,&client_len))==-1)
        {
            perror("accept error");
            exit(1);
        }
        else
        {
            send(fd_client,"You have connect Server!",strlen("You have connect Server!"),0);
        }
        printf("\n%s:%d Login server!\n\n", inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));

        ppid=fork();

        if (ppid== -1)
        {
            printf("fork 1 failed:\n");
        }else if (ppid== 0)
        {
            int recvbytes;
            pid=fork();

            if (pid == -1)
            {
                printf("fork 2 failed:\n");
                exit(1);
            }else if (pid == 0)
            {
                while(1)
                {
                    bzero(buf,1024);
                    //收 发
                    if ((recvbytes = recv(fd_client,buf,1024,0))== -1)
                    {
                        perror("read fd_client failed:");
                    }else if (recvbytes != 0)
                    {
                        buf[recvbytes]= '\0';
                        usleep(10000);
                        //printf("%s:%d said:%s\n", inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port), buf);
                        handle_request(buf,fd_client);
                        bzero(buf,1024);
                        //if (send(fd_client,buf,recvbytes,0)== -1)
                        //{
                          //  perror("send error");
                            //break;
                        //}
                    }
                }
            }
            else if (pid>0)
            {
                
            }
        }
        else if (ppid>0)
        {
            close(fd_client);
        }
    }
    return 0;
}