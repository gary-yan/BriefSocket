#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define SERV_PORT  8000
int main()
{

	int lfd, cfd, pid;
	struct sockaddr_in serv_addr, clin_addr;
	socklen_t clin_len;
	char buf[1024]; 
	int len;
	//结构组变量serv_addr 用来存储 IP和PORT
	//AF_INET : IPV4   SOCK_STREAM : stream 协议  0:tcp
	lfd = socket(AF_INET, SOCK_STREAM, 0);

	//IP + PORT
	serv_addr.sin_family = AF_INET;  //表示TCP/IP协议 ipv4 // sin_family协议簇 
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 构造地址。 表示绑定的地址为本地地址 htonl = host to net long 
	//INADDR_ANY 本机的任意一个一个地址 任意一个网卡都可以接收
	//sin_addr是一个联合体 用联合体可以用多种形式表达IP地址
	serv_addr.sin_port = htons(SERV_PORT);  //host to net short  网络序－－大端存储
	bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)); //(struct sockaddr *)&serv_addr强制类型转换   泛型指针 void＊

	listen(lfd,128);
while(1){


	printf("======waiting for client's request======\n");  

	clin_len = sizeof(clin_addr);
	cfd = accept(lfd, (struct sockaddr *)&clin_addr, &clin_len); //cfd connect f d
	pid_t pid = fork();
	if (pid==0)
	{
		printf("我是子进程\n");
            close(lfd);
            // do_something
            // char time_message[100];
            // timer_t now_time = (timer_t)time(NULL);
            // snprintf(time_message, sizeof(time_message), "%.24s\n", ctime((const timer_t)&now_time));
            // send(connfd, time_message, sizeof(time_message), 0);

            // close(cfd);
            exit(0);/* code */
	} else if (pid == -1) {
            close(cfd);
            continue;
        } else {
            close(cfd);
        }

    }
	// len = read(cfd, buf, sizeof(buf)); //读取存到缓存中 buf buffer
	// write(STDOUT_FILENO, buf, len );//标准输出 打印到屏幕上
	// close(lfd);
	// close(cfd);
	// return 0;

close(lfd);
return 0;
}