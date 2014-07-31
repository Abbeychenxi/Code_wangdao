#ifndef POLL_T_H
#define POLL_T_H

#include <poll.h>

#define ERR_EXIT(m)\
    do{\
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

typedef struct {
    struct pollfd clients_[2048];
    int listenfd_;
    int maxi_;
    int nready_;
    void (*handle_callback_)(int, char*);
}poll_t;

void poll_init(poll_t *_poll, int listenfd, void(*handler)(int, char*));
void poll_do_wait(poll_t *_poll);
void poll_handle_accept(poll_t *_poll);
void poll_handle_data(poll_t *_poll);


#endif