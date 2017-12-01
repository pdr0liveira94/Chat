#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <strings.h>
#include <arpa/inet.h>
#include <wchar.h>
#include <locale.h>

struct msgCli {
	char nickCli[50];
	char mensagemCli[250];	
}mensCli;

struct msgSer {
	char nickSer[50];
	char mensagemSer[250];	
}mensSer;

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "en_US.utf8");
	int sock, length, client_size;
	struct sockaddr_in name, client;
	char buf[1024];
	int counter = 0;
	int teste = 0;
	char mensagemCli[250], mensagem[250];
	
	printf("Informe o seu nick: ");
	gets(mensCli.nickCli);


	if(argc != 2){
        	printf("Use: %s porta\n",argv[0]);
        	exit(1);
    }

    /* Cria o socket de comunicacao */
	sock = socket(AF_INET, SOCK_DGRAM, 0);

	if(sock<0){
		/*houve erro na abertura do socket*/
		perror("opening datagram socket");
		exit(1);
	}

	/* Associa */
	length = sizeof(name);
	bzero(&name, length);//Pra que serve????
	name.sin_family = AF_INET;
	name.sin_addr.s_addr = INADDR_ANY;
	name.sin_port = htons(atoi(argv[1]));

	if (bind(sock,(struct sockaddr *)&name, length ) < 0){
		perror("binding datagram socket");
		exit(1);
	}

    /* Imprime o numero da porta */
	if (getsockname(sock,(struct sockaddr *)&name, &length) < 0){
		perror("getting socket name");
		exit(1);
	}

	printf("\e[H\e[2J");
	printf("CHAT DA GALERA! DIGITE SUAS MENSAGENS E ESPERE A RESPOSTA =D\n\n");

	while(1){

		client_size = sizeof(client);

        // le as informações através do rcv
        if(recvfrom(sock,(char *)&mensSer,sizeof(mensSer),0,(struct sockaddr *) &client,&client_size) < 0){
        		perror("receiving datagram message");
        		exit(1);
        }

        printf("%s: %s\n",mensSer.nickSer,mensSer.mensagemSer);

        fflush(stdin);

        printf("%s : ",mensCli.nickCli);

        gets(mensCli.mensagemCli);

        if (sendto (sock,(char *)&mensCli,sizeof(mensCli), 0, (struct sockaddr *)&client, sizeof client) < 0)
        		perror("sending datagram message");
    }

    close(sock);

	return 0;
    exit(0);
}
