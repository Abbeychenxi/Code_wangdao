#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)


ssize_t readline(int fd, void *usrbuf, size_t maxlen)
{
    char *bufp = usrbuf;
    int nread;
    size_t nleft = maxlen - 1;
    char c;
    while(nleft > 0)
    {
        if((nread = read(fd, &c, 1)) == -1)
        {
            if(errno == EINTR)
                continue;
            return -1;
        }else if(nread == 0)
        {
            break;
        }

        if(c == '\n')
        {
            *bufp = c;
            bufp++;
            nleft--;
            break;
        }
        *bufp = c;
        bufp++;
        nleft--;
    }
    *bufp = '\0';

    return (maxlen - nleft -1);
}

int main(int argc, const char *argv[])
{
    int fd = open("test.txt", O_RDONLY, 0666);
    if(fd == -1)
        ERR_EXIT("open");
    int ret;
    char buf[1024];
    while((ret = readline(fd, buf, 1024)))
    {
        printf("ret= %d, buf = %s\n", ret, buf);
    }
    return 0;
}
