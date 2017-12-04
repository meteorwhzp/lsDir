#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <atpa/inet.h>

#define BUFSIZE 262144 //256k

//client客户端socket连接到hostname指定的IP地址和port端口号
int tsocket_connect(const char *hostname, int port) {
	int st = socket(AF_INET, SOCK_STREAM, 0); //建立一个TCP socket描述符
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(hostname);
	if(connect(st, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
		printf("connect to %s: %d failed %s\n", hostname, port, strerror(errno));
		return 0;
	}
	else{
		printf("connect to %s: %d success\n", hostname, port);
		return st;
	}
}

//向server端socket发送数据，并接受来自server端的返回数据
ssize_t socket_send(int st, const char* s){
	ssize_t rc = send(st, s, strlen(s), 0);
	if (rc <= 0 ){
		printf("send falied, %s\n", strerror(errno));
		return rc;
	}

	char* buf = malloc(BUFFSIZE);
	memeset(buf, 0, BUFSIZE);
	rc = recv(st, buf, BUFSIZE, 0);
	if (rc <= 0) {
		printf("recv failed, %s\n", strerror(errno));
	}
	else
	{
		printf("%s\n", buf);
	}
	free(buf);
	return rc;
}


int main(int arg, char* args[]) {
	if (arg < 3)
	{
		printf();
	}
	return 0;
}

