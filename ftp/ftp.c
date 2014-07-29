#include "ftp.h"

void my_cd(int argc, char argv[3][10],int fd_client)
{
    int iret;
    char buf[1024]="";
    bzero(buf,1024);
    if (argc == 1)
    {
        iret = chdir("~");
        sprintf(buf,"cwd: %s\n", getcwd(NULL, 0));
        send(fd_client,buf,strlen(buf),0);
    }else if(argc == 2)
    {
       // printf("ok\n");
       // printf("%s\n", argv[1]);
        //printf("ok\n");
        iret = chdir(argv[1]);
        //printf("cwd: %s\n", getcwd(NULL, 0));
        sprintf(buf,"cwd: %s\n", getcwd(NULL, 0));
        if (send(fd_client,buf,strlen(buf),0)== -1)
        {
            perror("send error");
        }
        //getchar();
    }
    if (iret != 0)
    {
        perror("chdir fail:");
    }
}
void my_ls2(int argc, char argv[3][10], int fd_client)
{
    char buf[1024]="";
    char lbuf[1024]="";
    DIR* pDIR;
    struct dirent* myent;
    int col=0;
    if (argc ==1)
    {
        pDIR= opendir(".");
    }else
    {
        pDIR=opendir(argv[1]);
    }
    if (pDIR==NULL)
    {
        perror("open dir fail");
        exit(-1);
    }
    while((myent=readdir(pDIR))!= NULL)
    {
        memset(buf,0,1024);
        if (strncmp(myent->d_name,".",1)!=0 && strncmp(myent->d_name,"..",2)!=0)
        {
            sprintf(buf,"%-10s\n",myent->d_name);
            strcat(lbuf,buf);
            col ++ ;
            if(col % 5 == 0) 
            {
                //printf("\n");
            }
        }
    }
    memset(buf,0,1024);
    sprintf(buf,"\n%s",lbuf);
    send(fd_client,buf,strlen(buf),0);
}

void my_ls(int argc,char argv[3][10], int fd_client)
{
    int iret;
    char buf[1024]="";
    DIR* pDir;
    char* ptm;
    struct dirent* myent;
    struct stat mystat;
    struct tm* local;
    char str_mode[11]="";
    int col=0;

    if (argc == 1)
    {
        pDir=opendir(".");
    }else
    {
        pDir=opendir(argv[1]);
    }
    if (pDir == NULL)
    {
        exit(-1);
    }
    //printf("mode\tlink\tuid\tgid\tsize\tctime\tname\t\n");
    //sprintf(buf,"mode\tlink\tuid\tgid\tsize\tctime\tname\t\n");
    //send(fd_client,buf,strlen(buf),0); 
    while((myent = readdir(pDir)) != NULL)
    {
        memset(&mystat, 0, sizeof(mystat));
        stat(myent -> d_name, &mystat);
        memset(str_mode, 0, 11);
        mode_to_str(&mystat.st_mode, str_mode);
        local=localtime(&mystat.st_atime);
        ptm=ctime(&mystat.st_atime);
        format(ptm);
        if (strncmp(myent->d_name, ".", 1)!= 0 && strncmp(myent->d_name, "..", 2))
        {
            memset(buf,0,1024);
            //printf("%10s.%2d %-5s %-5s %5d %d %d %d:%d %s\n",str_mode,mystat.st_nlink,getpwuid(mystat.st_uid)->pw_name,getgrgid(mystat.st_gid)->gr_name,mystat.st_size,local->tm_mon+1,local->tm_mday,local->tm_hour,local->tm_min,myent->d_name);
            sprintf(buf,"%10s.%2d %-5s %-5s %5d %d %d %d:%d %s\n",str_mode,mystat.st_nlink,getpwuid(mystat.st_uid)->pw_name,getgrgid(mystat.st_gid)->gr_name,mystat.st_size,local->tm_mon+1,local->tm_mday,local->tm_hour,local->tm_min,myent->d_name);
            send(fd_client,buf,strlen(buf),0);
        }
    }
    //printf("\n");
    send(fd_client,"\n",1,0);

}

void mode_to_str(mode_t md,char *str)
{
    strcpy(str,"----------");
    if(S_ISDIR(md))
    {
        str[0]='d';
    }
    if(md & S_IRUSR)
    {
        str[1]='r';
    }
    if(md & S_IWUSR)
    {
        str[2]='w';
    }
    if(md & S_IXUSR)
    {
        str[3]='x';
    }
    if(md & S_IRGRP)
    {
        str[4]='r';
    }
    if(md & S_IWGRP)
    {
        str[5]='w';
    }
    if(md & S_IXGRP)
    {
        str[6]='x';
    }
    if(md & S_IROTH)
    {
        str[7]='r';
    }
    if(md & S_IWOTH)
    {
        str[8]='w';
    }
    if(md & S_IXOTH)
    {
        str[9]='x';
    }
}

void format(char *p)
{
    while(*p)
    {
        p++;
    }
    while(*p!=':')
    {
        p--;
    }
    *p = '\0';
}

void my_pwd(int argc, char argv[3][10], int fd_client)
{
    int iret;
    char buf[1024]="";
    bzero(buf,1024);
    //printf("current directory: %s \n", getcwd(NULL, 0));
    sprintf(buf,"current directory: %s \n", getcwd(NULL, 0));
    if (send(fd_client,buf,strlen(buf),0)== -1)
    {
        perror("send error");
    }
}

void my_mv(int argc, char argv[3][10], int fd_client)
{
    if (argc != 3)
    {
        printf("USAGE:EXE SRC DEST\n");
        exit(-1);
    }
    int fd_rd,fd_wr;
    int read_n;
    char buf[1024];
    fd_rd = open(argv[1], O_RDONLY);
    fd_wr = open(argv[2], O_WRONLY | O_CREAT, 0666);
    if (fd_rd == -1 || fd_wr == -1)
    {
        perror("open");
        exit(-1);
    }
    while(memset(buf, 0, 1024),(read_n = read(fd_rd, buf, 1024))>0)
    {
        write(fd_wr, buf, read_n);
    }
    send(fd_client,"mv ok!",6,0);
    close(fd_rd);
    close(fd_wr);
    unlink(argv[1]);
}

void handle_request(char buf[], int fd_client)
{
    int num=0;
    char req[3][10];
    
    sscanf(buf,"%s %s %s",req[0],req[1],req[2]);
    if (strcmp(req[0],"") != 0)
    {
        num++;
    }
    if (strcmp(req[1],"") != 0)
    {
        num++;
    }
    if (strcmp(req[2],"") != 0)
    {
        num++;
    }
   // printf("%s\n", req[0]);
   // printf("%s\n", req[1]);
    //printf("%s\n", req[2]);
   // printf("%d\n", num);


    if (strncmp(req[0],"ls",2)==0)
    {
        my_ls2(num,req, fd_client);
    }else if (strncmp(req[0],"pwd",3)== 0)
    {
        my_pwd(num, req, fd_client);
    }else if (strncmp(req[0],"cd",2)==0)
    {
        my_cd(num,req, fd_client);
    }else if (strncmp(req[0],"mv",2)== 0)
    {
        my_mv(num,req, fd_client);
    }else if(strncmp(req[0],"download",8)==0)
    {
        char fbuf[1024]="";
        bzero(fbuf,1024);
        sprintf(fbuf,"download %s",req[1]);
        send(fd_client,fbuf,strlen(fbuf),0);
        download_file(req,fd_client);
    }else if (strncmp(req[0],"upload",6)==0)
    {
        char fbuf[1024]="";
        bzero(fbuf,1024);
        sprintf(fbuf,"upload %s", req[1]);
        send(fd_client,fbuf,strlen(fbuf),0);
        upload_file(req, fd_client);
    }
}

void download_file(char req[3][10],int fd_client)
{
    int fd_file;
    int read_n;
    char buf[1024];
    MSG snd_msg;
    printf("recv request :%s \n", req[1]);
    fd_file = open(req[1],O_RDONLY);
    while(memset(&snd_msg,0,sizeof(snd_msg)), (read_n = read(fd_file,snd_msg.s_buf,MSG_SIZE)) > 0)
    {
        bzero(buf,1024);
        recv(fd_client,&buf,1024,0);
        if (strncmp(buf,"recv ok!",8)==0)
        {
            snd_msg.s_len = read_n ;
            send(fd_client, &snd_msg, snd_msg.s_len + MSG_LEN ,0);
        }else
        {
            send(fd_client, "download error", 14, 0);
            break;
        }
    }
    snd_msg.s_len = 0 ;
    send(fd_client, &snd_msg, snd_msg.s_len + MSG_LEN ,0);
    close(fd_file);
}

void upload_file(char req[3][10],int fd_client)
{
    int fd_file;
    int total = 0 ;
    MSG rcv_msg;
    fd_file = open(req[1],O_WRONLY|O_CREAT,0666);
    while(1)
    {
        memset(&rcv_msg, 0, sizeof(MSG));
        recv(fd_client,&rcv_msg,MSG_LEN, 0);
        total += rcv_msg.s_len ;
        system("clear");
        printf("dowloading...%.2f kb \n",(double)total/ 1024);
        if(rcv_msg.s_len > 0)
        {
            recv(fd_client,&rcv_msg.s_buf,rcv_msg.s_len, 0);
            write(fd_file,rcv_msg.s_buf,rcv_msg.s_len);
        }else 
        {
            break ;
        }
    }
    close(fd_file);
}
