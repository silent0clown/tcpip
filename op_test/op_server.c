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
    int serv_sock, clnt_sock;
    char message[BUF_SIZE];
    char send_msg[BUF_SIZE];
    int str_len, op_cnt;

    struct sockaddr_in serv_adr;
    struct sockaddr_in clnt_adr;
    socklen_t clnt_adr_sz;

    if(argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock=socket(PF_INET, SOCK_STREAM, 0);   
    if(serv_sock==-1)
        error_handling("socket() error");

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family=AF_INET;
    serv_adr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_adr.sin_port=htons(atoi(argv[1]));

    if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr))==-1)
        error_handling("bind() error");

    if(listen(serv_sock, 5)==-1)
        error_handling("listen() error");

    clnt_adr_sz=sizeof(clnt_adr);


    clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
    if(clnt_sock==-1)
        error_handling("accept() error");
    else
        printf("Connected client \n");


    read(clnt_sock, message, BUF_SIZE);
    op_cnt = atoi(message);
    printf("Get count is %d\n", op_cnt);

    int list[op_cnt];
    int ret_msg = 0;
    for(int i = 0; i < op_cnt; i++) {
        str_len = read(clnt_sock, message, BUF_SIZE);
        message[str_len] = 0;
        list[i] = atoi(message);
        printf("Get num : %d\n", list[i]);
    }

    str_len = read(clnt_sock, message, BUF_SIZE);
    message[str_len] = 0;
    // printf("Get opter : %s,strlen is %ld", message, strlen(message));

    if(!strcmp( message, "+\n")) {
        printf("do add\n");
        for(int i = 0; i < op_cnt; i++){
            ret_msg += list[i];
        }
        printf("value is %d\n", ret_msg);
        
    }
    sprintf(send_msg,"%d",ret_msg);
    write(clnt_sock, send_msg, strlen(send_msg));


    close(clnt_sock);
    

    close(serv_sock);
    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}