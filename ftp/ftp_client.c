#include "ftp.h"
#define SERVER_PORT 8888
#define MAXDATASIZE 1024
#define SERVER_IP "192.168.1.3"

int main(int argc, char const *argv[])
{
    int fd_server,numbytes;
    int total = 0 , read_n;
    int fd_file ;
    MSG rcv_msg, snd_msg;
    char buf[MAXDATASIZE];
    SA server_addr;

    printf("\n●～●～client initialization●～●～●～\n");

    printf("●～●～●～●～Command List●～●～●～●～\n");
    printf("●～1.ls                         ●～\n");
    printf("●～2.cd                         ●～\n");
    printf("●～3.mv                         ●～\n");
    printf("●～4.download file              ●～\n");
    printf("●～5.upload file                ●～\n");
    printf("●～●～●～input your request●～●～●～\n");

    
    if ((fd_server=socket(AF_INET, SOCK_STREAM, 0))== -1)
    {
        perror("socket");
        exit(-1);
    }
    server_addr.sin_family=AF_INET;
    server_addr.sin_port= htons(SERVER_PORT);
    server_addr.sin_addr.s_addr=inet_addr(SERVER_IP);
    bzero(&(server_addr.sin_zero), sizeof(server_addr.sin_zero));

    if (connect(fd_server, (struct sockaddr*)&server_addr,sizeof(SA))== -1)
    {
        perror("connect");
        exit(1);
    }

    while(1)
    {
        bzero(buf,MAXDATASIZE);
        printf("\n Begin receive...\n");
        if ((numbytes=recv(fd_server, buf, MAXDATASIZE, 0))== -1)
        {
            perror("recv");
            exit(-1);
        }
        else if (numbytes>0)
        {
            int len, bytes_sent;
            buf[numbytes] ='\0';
            
            if (strncmp(buf,"download",8)==0)
            {
                //printf("download\n");
                char name[2][100];
                sscanf(buf,"%s %s",name[0],name[1]);
                fd_file = open(name[1],O_WRONLY|O_CREAT,0666);
                while(1)
                {
                    send(fd_server,"recv ok!",8,0);
                    memset(&rcv_msg, 0, sizeof(MSG));
                    recv(fd_server,&rcv_msg,MSG_LEN, 0);
                    total += rcv_msg.s_len ;
                    system("clear");
                    printf("dowloading...%.2f kb \n",(double)total/ 1024);
                    if(rcv_msg.s_len > 0)
                    {
                        recv(fd_server,&rcv_msg.s_buf,rcv_msg.s_len, 0);
                        write(fd_file,rcv_msg.s_buf,rcv_msg.s_len);
                    }else 
                    {
                        break ;
                    }
                }
                close(fd_file);
            }else if(strncmp(buf,"upload", 6)==0)
            {
                char name[2][100];
                sscanf(buf,"%s %s",name[0],name[1]);
                fd_file = open(name[1],O_RDONLY);
                while(memset(&snd_msg,0,sizeof(snd_msg)), (read_n = read(fd_file,snd_msg.s_buf,MSG_SIZE)) > 0)
                {
                    snd_msg.s_len = read_n ;
                    send(fd_server, &snd_msg, snd_msg.s_len + MSG_LEN ,0);
                }
                snd_msg.s_len = 0 ;
                send(fd_server, &snd_msg, snd_msg.s_len + MSG_LEN ,0);
                close(fd_file);
            }else
            {
                printf("Received: %s\n", buf);
                fflush(stdout);
                bzero(buf,1024);
            }
            

            printf("Send:\n");
            char msg[1024]="";
            bzero(msg,1024);
            gets(msg);
            len=strlen(msg);

            if (send(fd_server,msg,len,0)== -1)
            {
                perror("send error");
            }
        }
        else
        {
            printf("socket end!\n");
        }
    }
    close(fd_server);
    return 0;
}