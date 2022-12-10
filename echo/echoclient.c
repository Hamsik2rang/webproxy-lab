#include "csapp.h"

#

int main(int argc, char** argv)
{
    int fd_client;
    char* host, * port, buf[MAXLINE];
    rio_t rio;

    if (argc != 3)
    {
        fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
        exit(0);
    }

    host = argv[1];
    port = argv[2];

    fd_client = Open_clientfd(host, port);
    Rio_readinitb(&rio, fd_client);

    while (Fgets(buf, MAXLINE, stdin) != NULL)
    {
        Rio_writen(fd_client, buf, strlen(buf));
        Rio_readlineb(&rio, buf, MAXLINE);
        Fputs(buf, stdout);
    }
    Close(fd_client);

    return 0;
}