#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define  BUFF_SIZE   1024

int main(){
    int client_socket;
    struct sockaddr_in server_addr;
    char buff[BUFF_SIZE];
    FILE *file;


    client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if( -1 == client_socket){
        printf("socket error \n");
        exit(1);
    }
    printf("client\n");
    memset(&server_addr, 0, sizeof (server_addr));
    printf("bb\n");
    server_addr.sin_family = AF_INET;
    printf("cc\n");
    server_addr.sin_port = htons(9900);
    printf("dd\n");
    server_addr.sin_addr.s_addr = inet_addr("192.168.10.100"); //172.30.1.254

    if(-1 == connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr))){
        printf("connect failed \n");
        exit(1);
    }
    printf("connect!\n");

    file = fopen("/root/Desktop/array.txt","r");
    if(file == NULL){
        printf("Can 't find file \n");
        exit(1);
    }
    else printf("file open \n");

    while(fgets(buff, BUFF_SIZE, file) != NULL){
        if(feof(file) != 0){
             printf("file done\n");
             break;
        }
        fgets(buff, BUFF_SIZE, file);
        printf("fgets done \n");
        if(-1 == send(client_socket, buff, BUFF_SIZE,0)){
            printf("send error \n");
            exit(1);
        }
        printf("send \n");
    }
    printf("finish\n");
    fclose(file);
    close(client_socket);


}

