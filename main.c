#include <stdio.h>
#include <winsock2.h>


int main(int argc , char *argv[])
{
	int resp;
	do
	{
        setvbuf(stdout, NULL, _IONBF, 0);
        setvbuf(stderr, NULL, _IONBF, 0);
        WSADATA wsa;
        SOCKET s;
        struct sockaddr_in server;
        char message[64], *message_fmt, resposta[2000];
        int resposta_tamanho;
        if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
        {
            printf("Falha. Error Code : %d",WSAGetLastError());
            return 1;
        }

        printf("Inicializado.\n");
        
        //Create a socket
        if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
        {
            printf("Could not create socket : %d" , WSAGetLastError());
        }
        char ip[15];
        printf("Socket Criado\n");
        printf("Insira o IP desejado.\n");
        
        scanf("%s", &ip);
        server.sin_addr.s_addr = inet_addr(ip);
        server.sin_family = AF_INET;
        server.sin_port = htons( 8888 );

        //Connect to remote server
        if (connect(s , (struct sockaddr *)&server , sizeof(server)) < 0)
        {
            puts("ERROR CONEXAO");
            return 1;
        }

        puts("CONECTADO\n");
        printf("insira o comando desejado\n");
        char *consult[8];
        scanf("%s", &consult);
        message_fmt = "%s\r\n\r\n";
        sprintf(message,message_fmt,consult);
        //Send some data
        int q = atoi(&message[4]);
        //message = "hello";
        if( send(s , message , strlen(message) , 0) < 0)
        {
            puts("Falha de envio");
            return 1;
        }
        puts("Solicitacao enviada\n");
        for(int i=0; i < q; i++)
        {
            if((resposta_tamanho = recv(s , resposta , 2000 , 0)) == SOCKET_ERROR)
            {
                puts("Falha de resposta");
            }
            puts("Resposta Recebida\n");
            //Add a NULL terminating character to make it a proper string before printing
            resposta[resposta_tamanho] = '\0';
            puts(resposta);
        }
        
        printf("Digite 1 para continuar ou 0 para sair \n");
        scanf("%d", &resp);
	}
	while ( resp == 1);
    return 0;
}
