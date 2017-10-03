#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <ctype.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main()
{
    int sock_cli = socket(AF_INET,SOCK_STREAM, 0);

    if(sock_cli == -1){
        printf("socket error");
        return -1;
    }

    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;/*使用IPv4协议*/
    servaddr.sin_port = htons(9001);/*需要连接的远程服务器端口*/
    // servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");/*需要连接的远程服务器IP*/
        // servaddr_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY);


    if(connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr))  == -1){
        printf("connect error");
        return -1;
    }

    char str[64];
    read(sock_cli, str, 64);
    printf("hh:%s\n",str);

    close(sock_cli);
}
