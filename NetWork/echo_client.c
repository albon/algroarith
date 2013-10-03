#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFSIZE    4096
#define SERV_PORT   12345
#define SA  struct  sockaddr
#define LISTENQ 1024
#define STDIN_FILENO    0
#define STDOUT_FILENO   1

int sockfd;
char    buf[BUFFSIZE];

int main(int argc, char **argv)
{

    ssize_t n;
    struct  sockaddr_in servaddr;
    if(argc != 2){
        printf("usage: cmd <IPaddress>/n");
        exit(0);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
    if(connect(sockfd, (SA *) &servaddr, sizeof(servaddr))==-1)
    {
        printf("connect failed!/n");
        exit(0);
    }

    while(1)
    {
    	if((n = read(STDIN_FILENO,buf,BUFFSIZE)) == 0)
    		continue;
    	n = write(sockfd, buf, n);
    	printf("send %d byte\n", n);
    	
        if((n = read(sockfd, buf, BUFFSIZE)) == 0)
            continue;
        printf("read %d byte\n", n);
        n = write(STDOUT_FILENO,buf,n);
    }

    exit(0);
}
