#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <iostream>
using namespace std;

struct ThreadData
{
  int fd;
  sockaddr_in client;
};

void* serverThread(void* param)
{
   ThreadData *clientData= ( (ThreadData*) param);

   char clientInput[100]="";
   
   while (strcmp(clientInput, "exit")!=0)
   {
     int bytes_recv= recv(clientData->fd, clientInput, 100, 0);
     if (bytes_recv==-1)
     {
        perror("recv");
        break;
     }
 
     cout<<"Data Received from client ("<<inet_ntoa(clientData->client.sin_addr)<<"):  "<<clientInput<<endl<<endl;
     
     int bytes_sent=send(clientData->fd, clientInput,  strlen(clientInput)+1, 0);
     if (bytes_sent==-1)
     {
        perror("send");
        break;
     }

   }
  
  cout<<"Client ("<<inet_ntoa(clientData->client.sin_addr)<<") disconnected."<<endl<<endl;
  close(clientData->fd);
  delete clientData;
  pthread_exit(NULL);

}

int main(int argc, char *argv[])
{
  if (argc==1)
  {
     cout<<"Please pass the port number on which you want the server to listen."<<endl;
     return 1;
  }
  
  int sock_fd;
  sockaddr_in server;

  if ((sock_fd= socket(AF_INET, SOCK_STREAM, 0))==-1)
  {
     perror("socket: ");
     exit(-1);
  }

 server.sin_family= AF_INET;
 server.sin_port= htons(atoi(argv[1]));
 server.sin_addr.s_addr= INADDR_ANY;
 bzero(&server.sin_zero, 8);

 int len=sizeof(sockaddr_in);
 
 if ((bind(sock_fd, (sockaddr*) &server, len))==-1)
 {
  perror("bind:");
  exit(-1);
 }

 if (listen(sock_fd, 10)==-1)
 {
       perror("listen:");
       exit(-1);
 }

 while (true)
 {
   ThreadData *newClient=new ThreadData;
   len=sizeof(sockaddr_in);
	 
   if( (newClient->fd=accept(sock_fd, (sockaddr*) &(newClient->client), (socklen_t*) &len) )==-1)
   {
	perror("accept:");
	exit(-1);
   }
   
  pthread_t tid=0;
  if ( (pthread_create(&tid, NULL, &serverThread, newClient))==-1)
  {
    perror("thread");
    continue;
  }  

  pthread_detach(tid);

 }//end of while loop

}
