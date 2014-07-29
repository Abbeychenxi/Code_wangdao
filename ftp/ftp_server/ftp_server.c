/*************************************************************************
	> File Name: ftp_server.c
	> Author: Comst
	> Mail:750145240@qq.com 
	> Created Time: 2014年04月05日 星期六 14时46分59秒
 ************************************************************************/

#include "ftp.h"
void* client_handle(void* arg)
{
	socket_t fd_client = *(int *)arg ;
	char recv_buf[BUF_SIZE] ;
	int sum_len = 0 ;
	while(1 )
	{
	//	bzero(recv_buf, BUF_SIZE);
		recv(fd_client, &sum_len, sizeof(int),0);
		recvn(fd_client, recv_buf, sum_len);
		if(strncmp("cd", recv_buf, 2) == 0)
		{
			char dir[128]= "";
			sscanf(recv_buf +3, "%s", dir );
			chdir(dir);
			getcwd(dir, 128);
			int len = strlen(dir);
			send(fd_client,&len, sizeof(int), 0 );
			sendn(fd_client, dir, strlen(dir));
		}else if(strncmp("ls", recv_buf,2) == 0)
		{
			DIR* pdir = opendir("./");
			if(pdir == NULL)
			{
				int flag = -1 ;
				send(fd_client, &flag, sizeof(int), 0);
			}else
			{
				struct dirent* mydir ;
				char send_buf[1024];
				int len ;
				while( (mydir = readdir(pdir)) != NULL)
				{
					if(strncmp(mydir->d_name, ".", 1) == 0 || strncmp(mydir->d_name,"..", 2) == 0)
					{
						continue ;
					}
					struct stat mystat;
					bzero(&mystat, sizeof(stat));
					stat(mydir->d_name, &mystat);
					bzero(send_buf, 1024);
					sprintf(send_buf, "%-20s %10dB",mydir->d_name, mystat.st_size );
					len =  strlen(send_buf);
					send(fd_client, &len, sizeof(int),0);
					sendn(fd_client, send_buf, len);
				}
				len = 0 ;
				send(fd_client, &len, sizeof(int),0);
			}
		}else if( strncmp("puts", recv_buf, 4)== 0)
		{
				char file_name[256];
				int file_pos = 5 ;
				while(bzero(file_name, 256), sscanf(recv_buf + file_pos,"%s", file_name) == 1)
				{
					file_pos += strlen(file_name) + 1 ;
					if(download(fd_client,file_name )== 0)
					{
						printf("file -> %s download success \n", file_name);
					}else
					{
					
						printf("file -> %s download failed \n", file_name);
					}
				}
		}else if( strncmp("gets", recv_buf, 4)== 0)
		{
			char file_name[256];
			int file_pos = 5 ;
			while(bzero(file_name, 256),sscanf(recv_buf + file_pos,"%s", file_name ) == 1)
			{
				file_pos += strlen(file_name) + 1; 
				if(upload(fd_client, file_name) == 0)
				{
					printf(" file-> %s upload success\n", file_name);
				}else 
				{
					printf(" file-> %s upload failed\n", file_name);
				}
				
			}
		
		}else if( strncmp("remove", recv_buf, 6)== 0)
		{
			char cmd[256] ="" ;
			sprintf(cmd, "rm -f %s", recv_buf + 10);
			system(cmd);
			char send_buf[256] = "";
			sprintf(send_buf,"%s removed", recv_buf + 10);
			int len = strlen(send_buf);
			send(fd_client, &len, sizeof(int),0);
			sendn(fd_client, send_buf, len);
			
		}


	}
}
int main(int argc, char* argv[])
{
	int pid ;
	pid = fork() ;
	if(pid > 0)
	{
		return 0 ;
	}else 
	{
	setsid();
	chdir("/");
	umask(0);
	int i ;
	for(i = 0 ; i < 1024; i++)
	{
		close(i);
	}
	int fd_log = open("ftp.log", O_WRONLY|O_APPEND);
	if(fd_log == -1)
	{
		printf("open");
		return 0 ;
	}
//		fflush(stdout);
		//close(fd_log);
	int conn_num = 0 ;
	char log_buf[128];
	char* ip = argv[1];
	char* port = argv[2];
	socket_t fd_server = socket_server(ip, port);
	socket_t fd_client ; 
	pthread_t thd ;
	if(fd_server == -1)
	{
		perror("socket_server");
		exit(-1);
	}
	while(1)
	{
		fd_client = accept(fd_server, NULL, NULL);
		bzero(log_buf, 128);
		sprintf(log_buf, "%d connect\n",++conn_num );
		write(fd_log, log_buf, strlen(log_buf));
		pthread_create(&thd, NULL, client_handle,(void*)&fd_client );
	}
	return 0 ;
	}

}
