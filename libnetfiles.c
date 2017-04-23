#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>

int SD = NULL;
int sizeofSD = 0;
char* HOST_NAME = NULL;
enum error_msgs{
	HOST_NOT_FOUND = -1
};

int netserverinit(char * hostname){
	int sockfd, n, portno;
   struct sockaddr_in serv_addr;
   struct hostent *server;
   
   //extract port number
   int colonLoc = -1;
   for(colonLoc = 0; hostname[colonLoc] !=':' || hostname[colonLoc] !='\0'; colonLoc++);
   
   //if no colon, return failure
   if(colonLoc == strlen(hostname)){
      perror("ERROR connecting");
	  errno = HOST_NOT_FOUND;
	  perror(errno);
      return HOST_NOT_FOUND;// dont forget to set error know
   }
   
    //actually get the number
	char port_buffer[6];
	bzero(&port_buffer, 6);
	int index=0;
	for(colonLoc+=1; colonLoc <= strlen(hostname); colonLoc++, index++){
		port_buffer[index] = hostname[colonLoc];
	}
	
	portno = atoi(port_buffer);
   
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }
   
   server = gethostbyname(hostname);
   
   if (server == NULL) {
      fprintf(stderr,"ERROR, no such host\n");
      exit(0);
   }
   
   bzero((char *) &serv_addr, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
   serv_addr.sin_port = htons(portno);
   
   /* Now connect to the server */
   if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR connecting");
	  errno = HOST_NOT_FOUND;
	  perror(errno);
      return HOST_NOT_FOUND;// dont forget to set error know
   }
   
   //if we get here, set the socket file descriptor & store the host name as a global variable  
   //HOST_NAME is to be used in functions like netread and netwrite
   SD = (struct sockaddr_in*) malloc(sizeof(struct sockaddr_in));
   SD->in_addr = (struct in_addr*)malloc(sizeof(struct in_addr));
   bzero((char*)&SD, sizeof(struct sockaddr_in));
   SD->sin_family = AF_INET;
   bcopy((char*)server->h_addr, (char*) &SD->sin_addr->s_addr, server->h_length);
   SD->sin_port = htons(portno);
	
   
   //copy the host name sent from the command line 
   HOST_NAME = (char*)malloc(sizeof(char)*strlen(hostname)+1);
   strcpy(HOST_NAME, hostname);
   
   return 0;
}
