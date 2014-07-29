
#include "server_main.h"
#include "socket_tcp.h"

struct sockaddr_in server_addr;

void requset_handle(struct sockaddr_in client_addr);


// void sig_handle(int num)
// {
//     while(waitpid(-1, NULL, WNOHANG) > 0) ;  //这个不懂……待研究
// }


int main(int argc, char const *argv[])
{
    set_addr(&server_addr, SERVER_IP, SERVER_PORT);

    int fd_server_udp = socket_init_udp(server_addr);

    char buf[5];

    struct sockaddr_in client_addr;  // 用于和客户通信，由accept写入
    int addrlen = sizeof(struct sockaddr_in);
    while (1)
    {
        memset(&client_addr, 0, sizeof(client_addr));
        recvfrom(fd_server_udp, buf, 1, 0, (struct sockaddr *)&client_addr, (unsigned int *)&addrlen);
        printf("okserver\n");
        sendto(fd_server_udp,"1",1,0,(struct sockaddr*)&client_addr,sizeof(client_addr));
  
        printf("%s login!~~\n", inet_ntoa(client_addr.sin_addr));

        if(0==fork()){
            close(fd_server_udp);
            requset_handle(client_addr);
        }
        // else
        // getchar();
    }
    return 0;
}



void requset_handle(struct sockaddr_in client_addr)
{
    // sleep(1);
    int fd_server_tcp = socket(AF_INET, SOCK_STREAM, 0); //主动连接客户端
    my_connect(fd_server_tcp, &client_addr);
    printf("Connect client %s successfully!\n",inet_ntoa(client_addr.sin_addr));

    char command_buf[128], pwd[128], answer_buf[1024];
    char ls[64], yesno;
    int flag;

    while(1)
    {
        memset(command_buf, 0, 128);
        memset(pwd, 0, 128);
        memset(answer_buf, 0, 1024);
        strcpy(ls, "ls ");
        yesno = 'n';
        FILE* fp_temp = NULL;

        getcwd(pwd, 128);       //刷新当前目录
        send(fd_server_tcp, pwd, 128, 0);

        if(0==recv(fd_server_tcp, command_buf, 128, 0)){
            printf("%s logout!\n", inet_ntoa(client_addr.sin_addr));
            exit(0);
        } 
        printf("%s: %s\n", inet_ntoa(client_addr.sin_addr), command_buf);

        flag = 0;


        if (0==strncmp("ls", command_buf, 2))
        {
            strcat(ls, command_buf+2);
// printf("%s\n", ls);
            fp_temp = popen(ls, "r");
            fread(answer_buf, 1, 1024, fp_temp);
            pclose(fp_temp);
        }
        else if (0==strncmp("rm", command_buf, 2))
        {
            if(0==unlink(command_buf+2)){
                sprintf(answer_buf, "File successfully removed.\n"); 
            }
            else{
                sprintf(answer_buf, "Removed file failed!\n"); 
            }
        }
        else if (0==strncmp("download", command_buf, 8))
        {
            sprintf(answer_buf, "Do you really want to download this file? (y/n)\n");
            flag = 1; 
        }
        else if (0==strncmp("upload", command_buf, 6))
        {
            sprintf(answer_buf, "Do you really want to upload this file? (y/n)\n");
            flag = 2; 
        }
        else if (0==strncmp("cd", command_buf, 2))
        {
            if(chdir(command_buf+2)){
                sprintf(answer_buf, "CD failed!!\n");   
            }
        }
        else
        {
            sprintf(answer_buf, "Wrong Input!!\n");
        }
        send(fd_server_tcp, answer_buf, 1024, 0);

        if(1==flag)
        {
            recv(fd_server_tcp, &yesno, 1, 0);
            if('y'==yesno){
                send_file_tcp(command_buf+8, fd_server_tcp);
            }
        }

        if(2==flag)
        {
            recv(fd_server_tcp, &yesno, 1, 0);
            if('y'==yesno){
                recv_file_tcp(command_buf+6, fd_server_tcp);
            }
        }

    }
    exit(0);
}



