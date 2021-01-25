/*
	Diktuakos Programmatismos Askisi.
	client.c

	Name:  Gerakianaki Aikaterini Maria
	AM:    2022201700024
	Email: dit17024@uop.gr

	Name:  Vlachou Eleftheria
	AM:    2022201700018
	Email: dit17018@uop.gr
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include<ctype.h>

void error(const char *msg)//Sunartisi biaiou termatismou.
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno, n,nsockfd,varread;
    struct sockaddr_in serv_addr,cli_addr;
    struct hostent *server;
    socklen_t servlen;
    char buffer[512];
    //Elenxos orismatwn.
    if (argc < 4)
    {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);//Dimiourgw to socket,bash protokolwn Internet &TCP.
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;//Epilogi xrisis Internet.
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,server->h_length);
    serv_addr.sin_port = htons(portno);//epilegw sugkekrimeni morfi gia na apothikeusw to port.
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)//Sundesi me to Socket kai elenxos.
        error("ERROR connecting");
  
        bzero(buffer,512);
        
    FILE *f;//Deiktis gia to arxeio.
    

    int words = 0;
    char c;
     f=fopen(argv[3],"r");//Anoigma arxeiou mono gia anagnwsi.
    while((c=getc(f))!=EOF)//Metrisi arithmou lekswn sto arxeio.
	{	
		fscanf(f , "%s" , buffer);
		if(isspace(c)||c=='\t')//Metrisi meta apo kathe keno.
		words++;	
	}
	
       
      
	write(sockfd, &words, sizeof(int));//Apostoli megethous sto server.
     	rewind(f);//Gurnaw ton deikth stin arxi tou arxeiou.
      
            
       
    char ch ;
       while(ch != EOF)//Apostoli dedomenwn sto server.
      {
		
		fscanf(f , "%s" , buffer);
		write(sockfd,buffer,512);
		ch = fgetc(f);
      }
	printf("The file was sent successfully");

       fclose(f); //Kleinw to arxeio 
	
	bzero(buffer,512);
	varread=read(sockfd,buffer,512);//Dexomai ta dedomena apo ton server se morfi string me "-" anamesa stis lekseis.
	
	//Tupwnw to string pou eftase apo ton server se kanoniki morfi xwris "-".
	char *token=strtok(buffer,"-");
	while(token!=NULL)
	{
	printf("\t %s",token);
	token=strtok(NULL,"-");
	}

    close(sockfd);//Kleisimo socket meta to peras tis sundesis.
    return 0;
}
