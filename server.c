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
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>


void error(const char *msg)//Sunartisi biaiou termatismou.
{
    perror(msg);
    exit(1);
}

void upper_string(char s[]) {//Sunartisi pou metatrepei kathe mikro gramma se kefalaio.
   int c = 0;
   
   while (s[c] != '\0') {
      if (s[c] >= 'a' && s[c] <= 'z') {
         s[c] = s[c] - 32;
      }
      c++;
   }
}
int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno,nsockfd,varread;
     socklen_t clilen;
     char buffer[512];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     //Elenxos orismatwn.
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }

     sockfd = socket(AF_INET, SOCK_STREAM, 0);//Dimiourgia socket.
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;//Epilogi Internet.
     serv_addr.sin_addr.s_addr = INADDR_ANY;//Anathesi dieuthinsis.
     serv_addr.sin_port = htons(portno);//Anathesi port apantisis.
     if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) //Elenxos sindesis Ip kai socket.
              error("ERROR on binding");
     listen(sockfd,5);//Eisagwgi stoixeiwn.
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr,  &clilen);//Apodoxi sundesis me ton client.
     if (newsockfd < 0) //Elenxos sundesis.
          error("ERROR on accept");
          
          
          //Dimiourgia neou arxeiou me kefalaia grammata.
          FILE *fp;
         int ch = 0;
            fp = fopen("text_receive.txt","w"); //Anoigma arxeiou me dinami sungraphis.           
            int words;
		read(newsockfd, &words, sizeof(int));//Diabasma aitimatos apo ton client.
            
          while(ch != words)
       	   {
        	 read(newsockfd , buffer , 512);
		  upper_string(buffer); 
	   	 fprintf(fp , " -%s" , buffer);  
		 ch++;
	   }
     	printf("The file was received successfully\n");
        printf("The new file created is text_receive.txt");
	fclose(fp);//Kleisimo arxeiou.

	fp = fopen("text_receive.txt","r");  //Anoigma arxeiou me dinami anagnwsis.
	 while((ch=getc(fp))!=EOF)			
	{	
		fscanf(fp, " %s" , buffer);
		send(newsockfd,buffer,strlen(buffer),0);//Apostoli ston client.
		
	}
	
       fclose(fp);//Kleisimo arxeiou.


	
//Kleisimo sindesis server me client.
     close(newsockfd);
     close(sockfd);
     return 0; 
}

