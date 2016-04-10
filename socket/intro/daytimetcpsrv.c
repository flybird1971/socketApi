#include	"unp.h"
#include	<time.h>

int
main(int argc, char **argv)
{
	int					listenfd, connfd;
	struct sockaddr_in	servaddr;
	char				buff[MAXLINE];
	time_t				ticks;

	if (argc != 2)
		err_quit("usage: a.out <Port>");

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	// servaddr.sin_port        = htons(13);	/* daytime server */
	servaddr.sin_port        = htons(atoi(argv[1]));	/* daytime server */

	Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));

	Listen(listenfd, LISTENQ);

	printf("list %d and host:%d port : %d\n",LISTENQ,INADDR_ANY,servaddr.sin_port);
	fflush(stdout);

	for ( ; ; ) {
		connfd = Accept(listenfd, (SA *) NULL, NULL);

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        int lens = strlen(buff);
        int i;
        for (i = 0; i < lens; ++i){
        	Write(connfd,buff+i,1);
        	printf("%c ",buff[i]);
        }
        printf("\r\n");
        fflush(stdout);
        // Write(connfd, buff, strlen(buff));

		Close(connfd);
		printf("client socket close\r\n");
	}
}
