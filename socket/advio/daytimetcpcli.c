#include	"unp.h"

int
main(int argc, char **argv)
{
	int					sockfd, n;
	char				recvline[MAXLINE + 1];
	struct sockaddr_in	servaddr;

	// if (argc != 2)
	// 	err_quit("usage: a.out <IPaddress>");
	if (argc != 3)
		err_quit("usage: a.out <IPaddress> <Port>");

	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	// if ( (sockfd = socket(9999, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	// servaddr.sin_port   = htons(13);	/* daytime server */
	servaddr.sin_port   = htons(atoi(argv[2]));	/* daytime server */
	printf("port : %d\n",atoi(argv[2]) );
	fflush(stdout);

	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		err_quit("inet_pton error for %s", argv[1]);

	if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
		err_sys("connect error");

	int times = 0;
	while ( (n = read(sockfd, recvline, 6)) > 0) {
	// while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0;	/* null terminate */
		if (fputs(recvline, stdout) == EOF)
			err_sys("fputs error");
		times += 1;
	}
	printf("times gt 0 : %d\n",times);
	fflush(stdout);
	if (n < 0)
		err_sys("read error");

	exit(0);
}
