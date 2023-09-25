#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc, char *argv[])
{
    int sock;
    char message[BUF_SIZE];
    int str_len;
    struct sockaddr_in serv_adr;

    if(argc!=3) {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock=socket(PF_INET, SOCK_STREAM, 0);   
    if(sock==-1)
        error_handling("socket() error");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_adr.sin_port=htons(atoi(argv[2]));

    if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
        error_handling("connect() error!");
    else
        puts("Connected...........");
    printf("Operand count: ");

    fgets(message, BUF_SIZE, stdin);
    // printf("%d\n", count);
    int count = atoi(message);
    // printf("count is %d\n", count);
    write(sock, message, strlen(message));
    for (int i = 1; i <= count; i++) 
    {
        printf("Operand %d: ", i);
        fgets(message, BUF_SIZE, stdin);          // 应该累计到一个数组里，最后一起发
        write(sock, message, strlen(message)); 
    }
    printf("Operator(+ - * /): ");
    // 输入操作符
    fgets(message, BUF_SIZE, stdin);
    write(sock, message, strlen(message));
    str_len=read(sock, message, BUF_SIZE-1);
    message[str_len]=0;
    printf("Operand result: %s", message);

    close(sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}