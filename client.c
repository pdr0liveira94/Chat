#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <strings.h>

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
	int sock,lenght;
	struct sockaddr_in name;
	struct hostent *hp, *gethostbyname();
	int countRcved = 0;
	int clientSize;
	char mensagem[250], mensagemServ[250];
	
	printf("Informe o seu nick: ");
	gets(mensCli.nickCli);

	if(argc != 3){
        	printf("Use: %s ip porta\n",argv[0]);
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
    hp = gethostbyname(argv[1]);
    if (hp==0){
    	fprintf(stderr, "%s: unknown host ", argv[2]);
    	exit(2);
	}

    bcopy ((char *)hp->h_addr, (char *)&name.sin_addr, hp->h_length);

    name.sin_family = AF_INET;
    name.sin_port = htons(atoi(argv[2]));
    printf("\e[H\e[2J");
    printf("CHAT DA GALERA! DIGITE SUAS MENSAGENS E ESPERE A RESPOSTA =D\n\n");


	while(1){

		printf("%s: ",mensCli.nickCli);
		gets(mensCli.mensagemCli);

        /* Envia */
        if (sendto (sock,(char *) &mensCli,sizeof(mensCli), 0, (struct sockaddr *)&name,sizeof name)<0)
        		perror("sending datagram message");

        if(recvfrom(sock,(char *) &mensSer,sizeof(mensSer),0,(struct sockaddr *) &name,&clientSize)<0){
        		perror("receiving datagram message");
        		exit(1);
        }

        printf("%s: %s\n",mensSer.nickSer, mensSer.mensagemSer);

	}

    close(sock);
    exit(0);
}
