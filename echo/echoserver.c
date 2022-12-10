#include "csapp.h"


void echo(int fd_conn);

int main(int argc, char** argv)
{
    int fd_listen, fd_conn;
    socklen_t client_len;
    struct sockaddr_storage client_addr;
    char client_hostname[MAXLINE], client_port[MAXLINE];

    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }

    fd_listen = Open_listenfd(argv[1]);
    while (1)
    {
        client_len = sizeof(struct sockaddr_storage);
        fd_conn = Accept(fd_listen, (struct sockaddr*)&client_addr, &client_len);
        Getnameinfo((struct sockaddr*)&client_addr, client_len, client_hostname, MAXLINE, client_port, MAXLINE, 0);
        printf("Connected to (%s, %s)\n", client_hostname, client_port);
        echo(fd_conn);
        Close(fd_conn);
    }
    Close(fd_listen);

    return 0;
}

void echo(int fd_conn)
{
    size_t n;
    char buf[MAXLINE];
    rio_t rio;

    Rio_readinitb(&rio, fd_conn);
    while ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0)
    {
        printf("server received %d bytes\n", (int)n);
        Rio_writen(fd_conn, buf, n);
    }
}