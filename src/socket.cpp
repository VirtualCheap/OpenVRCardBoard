#include <unistd.h>
#include <netinet/in.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include "socket.h"

typedef struct{
    float x,y,z;
} coord;

coord xyz;


int socketserv(){
    
      xyz.x = 0.0;
      xyz.y = 0.0;    
     xyz.z = 0.0;
     
     int BUFLEN = 5000;
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[BUFLEN];
     struct sockaddr_in serv_addr, cli_addr;
     int n, i;
     int one = 1;

     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) {
        perror("ERROR create socket");
        exit(1);
     }
     setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof one);    //allow reuse of port
     //bind to a local address
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi("5000");
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on bind");
        exit(1);
     }
     listen(sockfd,5);
     //accept incoming connections
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     if (newsockfd < 0) {
        perror("ERROR on accept");
        exit(1);
     }
     printf("connection accepted\n");
     for (;;) {
         bzero(buffer,BUFLEN);
         n = read(newsockfd,buffer,BUFLEN);
         if (n < 0) {
            perror("ERROR read from socket");
         }

         if (strcmp("", buffer) != 0){
             std::string bufferStr(buffer); //Convert to C++ Strings
             std::stringstream ss(bufferStr); //Create a String Stream
             ss >> xyz.x >> xyz.y >> xyz.z; //Convert the string to float's             
             std::cout << "X: " << xyz.x << " Y: " << xyz.y << " Z: " << xyz.z << std::endl;
         }
    }
}

//int main(){
//    socketserv();
//}

