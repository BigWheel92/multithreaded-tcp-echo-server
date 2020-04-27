#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <iostream>
#include <arpa/inet.h>
using namespace std;

int main(int argc, char *argv[])
{
  if (argc<2)
  {
     cout<<"Please pass the ip address of the server as well as the port on which the server is listening."<<endl;
     return 1;
  }

 sockaddr_in remote_server;
 int sock_fd;

 if ( (sock_fd= socket(AF_INET, SOCK_STREAM, 0) ) ==-1) 
 {
    perror("socket: ");
    exit(-1);
 }

 remote_server.sin_family=AF_INET;
 remote_server.sin_port= htons(atoi(argv[2])); 
 remote_server.sin_addr.s_addr= inet_addr(argv[1]);
 bzero(&remote_server.sin_zero, 8);
 

 if (connect(sock_fd, (sockaddr*) &remote_server, sizeof(sockaddr))==-1)
 {
   perror("connect: ");
   close(sock_fd);
   exit(-1);
 }

 char userInput[100]="";

 while (strcmp(userInput, "exit")!=0)
 {
   cout<<"Please enter the input to be sent to the server: ";
   cin.getline(userInput, 99);

   int bytes_sent= send(sock_fd, userInput, strlen(userInput)+1, 0);
   if (bytes_sent==-1)
   {
    perror("send: ");
    close(sock_fd);
    exit(-1);
   }

   char recv_message[100];
   int bytes_recv=recv(sock_fd, recv_message,  100, 0);
   if (bytes_recv==-1)
   {
    perror("recv: ");
    close(sock_fd);
    exit(-1);
   }

   cout<<"The server sent: "<<recv_message<<endl;

 }//end of while loop

 close(sock_fd);

}
