#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#define MAXLEN 1024
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

#define RIO_BUFFER 8192

typedef struct {
    int fd_;
    int left_;
    char *bufptr_;
    char buffer_[RIO_BUFFER];
}rio_t;

void rio_init(rio_t *rp, int fd)
{
    rp -> fd_ = fd;
    rp -> left_ = 0;
    rp -> bufptr_ = rp -> buffer_;
}

ssize_t rio_read(rio_t *rp, char *usrbuf, size_t n)
{
    ssize_t nread;
    while(rp -> left_ <= 0)
    {
        nread = read(rp->fd_, rp->buffer_, sizeof(rp->buffer_));
        if(nread == -1)
        {
            if(errno == EINTR)
                continue;
            return -1;
        }else if(nread == 0)
            return 0;

        rp -> left_ = nread;
        rp -> bufptr_ = rp->buffer_;
    }
    int cnt =n;
    if(rp -> left_ <n)
        cnt = rp->left_;
    memcpy(usrbuf, rp->bufptr_, cnt);
    rp->left_ -= cnt;
    rp->bufptr_ += cnt;

    return cnt;
}

ssize_t rio_readn(rio_t *rp, void *usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nread;
    char *bufp = usrbuf;

    while(nleft > 0)
    {
        if((nread = rio_read(rp, bufp, nleft)) == -1)
        {
            return -1;
        }else if(nread == 0)
            break;

        nleft -= nread;
        bufp += nread;
    }
    return (n - nleft);
}

ssize_t rio_readline(rio_t *rp, void *usrbuf, size_t maxlen)
{
    char *bufp = usrbuf;
    char c;
    int nread;
    ssize_t i;
    for(i = 0; i < maxlen -1; ++i)
    {
        if((nread = rio_read(rp, &c, 1))== -1)
            return -1;
        else if(nread == 0)
        {
            if(i == 0)
                return 0;
            break;
        }

        *bufp++ = c;
        if(c == '\n')
            break;

    }
    *bufp = '\0';
    return i;
}

ssize_t rio_write(int fd, void *usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nwrite;

    char *bufp = usrbuf;

    while(nleft > 0)
    {
        if((nwrite = write(fd, bufp, nleft)) <= 0)
        {
            if(errno == EINTR)
                nwrite = 0;
            else
                return -1;
        }

        nleft -= nwrite;
        bufp += nwrite;
    }
    return n;
}
int main(int argc, const char *argv[])
{
/*    rio_t rio;
    rio_init(&rio, STDIN_FILENO);
    int ret;
    char buf[1024] = {0};
    while((ret = rio_readline(&rio, buf, 1024)) > 0)
    {
        rio_write(STDOUT_FILENO, buf, srlen(buf));
    }
*/
    int fd = open("test.txt", O_RDONLY);
    if(fd == -1)
        ERR_EXIT("open");
    rio_t rio;
    rio_init(&rio, fd);

    int ret;
    char buf[MAXLEN];
    while((ret = rio_readline(&rio, buf, MAXLEN)) > 0)
        rio_write(STDOUT_FILENO, buf, strlen(buf));

    return 0;
}
