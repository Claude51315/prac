#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>

#define PERROR_AND_RETURN(str) fprintf(stderr,str "\n"); \
        return -1


#define MAX_EVENTS 64

static int create_and_bind(char* port); 
static int make_socket_non_blocking(int sfd);

int main(int argc , char *argv[])
{
    int sfd, s;
    int efd;
    struct epoll_event event;
    struct epoll_event *events;
    if(argc != 2 ){
        PERROR_AND_RETURN("need to specify port number");
    }
    sfd = create_and_bind(argv[1]);
    if(sfd ==-1){
        PERROR_AND_RETURN("cannot bind the port"); 
    }
    s = make_socket_non_blocking(sfd);
    if(s == -1){
        PERROR_AND_RETURN("set non blocking error");
    }
    s = listen(sfd , SOMAXCONN);
    if(s == -1){
        PERROR_AND_RETURN("listen error");
    }
    efd = epoll_create1(0);
    if(efd == -1){
        PERROR_AND_RETURN("epoll create error");
    }

    event.data.fd =sfd ;
    event.events = EPOLLIN | EPOLLET ; 
    s = epoll_ctl(efd, EPOLL_CTL_ADD, sfd, &event);
    if(s == -1){
        PERROR_AND_RETURN("epoll ctl error");
    }
    /* start to listen */
    events = calloc(MAX_EVENTS,sizeof(event));
    while(1)
    {
        int n, i ; 
        n = epoll_wait(efd, events, MAX_EVENTS, /*timeout = */ -1); 
        if(n == 0)
        {
            printf("there is no connection\n");
            return 0;
        }
        for(i = 0; i < n ; i ++)
        {
            if( (events[i].events & EPOLLERR) ||
                (events[i].events & EPOLLHUP) ||
                (!(events[i].events & EPOLLIN)))
            {
                close(events[i].data.fd);
                PERROR_AND_RETURN("epoll error");
            
            }else if(sfd == events[i].data.fd){
               /* there is a new connection*/ 
                while(1){
                    struct sockaddr in_addr;
                    socklen_t in_len;
                    int infd;
                    char hbuf[NI_MAXHOST],  sbuf[NI_MAXSERV];
                    in_len = sizeof(in_addr);
                    infd = accept(sfd, &in_addr, &in_len);
                    if(infd == -1){
                        if( (errno == EAGAIN) ||
                            (errno == EWOULDBLOCK))
                        {
                            break;
                        }
                        else
                        {
                            PERROR_AND_RETURN("accept error");
                        }
                    }
                    s = getnameinfo(&in_addr, in_len, 
                                    hbuf, sizeof (hbuf),
                                    sbuf, sizeof (sbuf),
                                    NI_NUMERICSERV | NI_NUMERICHOST);
                    if(s==0){
                        printf("accept connection on fd %d"
                                "(host = %s , port = %s)\n", infd, hbuf,sbuf);
                    }
                    s = make_socket_non_blocking(infd);
                    if(s == -1 ){
                        PERROR_AND_RETURN("make non blocking error");
                    }
                    event.data.fd = infd;
                    event.events = EPOLLIN | EPOLLET ; 
                    s = epoll_ctl(efd, EPOLL_CTL_ADD, infd, &event);
                    if(s == -1){
                        PERROR_AND_RETURN("epoll ctl error");
                    }
                    continue;
                }
            }
            else{
                int done = 0;
                while(1)
                {
                    ssize_t count;
                    char buf[512];
                    count = read(events[i].data.fd, buf, sizeof(buf));
                    if(count == -1){
                        if(errno != EAGAIN)
                        {
                            PERROR_AND_RETURN("read error");
                        }
                        break;
                    }else if(count ==0){
                        done = 1 ;
                        break;
                    }
                    /* write to stdout*/
                    s = write(1, buf, count);
                    if(s == -1){
                        PERROR_AND_RETURN("write error");
                    }
                    /* send ack back*/
                    memset(buf,0 , 512);
                    strcpy(buf , "recieved!");
                    s = write(events[i].data.fd , buf , 10); 
                    if(s == -1){
                        PERROR_AND_RETURN("write error");
                    }
                }
                if(done == 1){
                    printf("close connection on file descriptor %d\n", events[i].data.fd);
                    close(events[i].data.fd);
                }
            }
        }   
    }
    free(events);
    close(sfd); 
    return 0; 
}
static int create_and_bind(char* port)
{
    struct addrinfo hints; 
    struct addrinfo *result, *rp;
    int s, sfd ; 
    memset(&hints , 0 , sizeof(struct addrinfo)); 
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM; 
    hints.ai_flags = AI_PASSIVE; 
    s = getaddrinfo(NULL, port , &hints, &result);
    if(s!= 0 ){
        PERROR_AND_RETURN("getaddrinfo error");
    }
    for(rp = result ; rp!=NULL ; rp = rp->ai_next){
        sfd = socket(rp->ai_family,rp->ai_socktype, rp->ai_protocol);
        if(sfd == -1)
            continue;
        s = bind (sfd, rp->ai_addr , rp->ai_addrlen);
        if(s == 0) {
            /*bind success*/
            break ;
        }
        /*close when there is no binding sucess*/
        close(sfd);
    }
    if(rp ==NULL){
        PERROR_AND_RETURN("bind fail"); 
    }
    freeaddrinfo(result);
    return sfd; 
}
static int make_socket_non_blocking(int sfd)
{
    int flags, s ; 
    flags = fcntl(sfd, F_GETFL, 0);
    if(flags == -1){
        PERROR_AND_RETURN("fcntl error");
    }
    flags |= O_NONBLOCK ; 
    s = fcntl(sfd, F_SETFL , flags); 
    if(s== -1){
        PERROR_AND_RETURN("fcntl error");
    }
    return 0 ; 
}
