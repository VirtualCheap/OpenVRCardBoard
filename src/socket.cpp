#include "socket.h"

void TcpServer::init(char* port){
    int one = 1;
    running = true;
    sockfd = socket(AF_INET, SOCK_STREAM, 0); // Create socket
    if (sockfd < 0) {
        // TO-DO Make error react diffrently
       perror("ERROR create socket");
       exit(1);
    }
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof one);    //allow reuse of port
    //bind to a local address
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(port);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
       perror("ERROR on bind");
       // TO-DO Make error react diffrently
       exit(1);
    }
    t1 = std::thread(thread);
}

void TcpServer::thread(){
     xyzMutex.lock();
     float xyz[3] = {0, 0, 0};
     xyzMutex.unlock();
     socklen_t clilen;
     char buffer[BUFLEN];
     int n;
     while (running){
         listen(sockfd,5);
         //accept incoming connections
         clilen = sizeof(cli_addr);
         newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
         if (newsockfd < 0) {
            perror("ERROR on accept");
            exit(1);
         }
         printf("connection accepted\n");
         while (running) {
             bzero(buffer,BUFLEN);
             n = read(newsockfd,buffer,BUFLEN);
             if (n < 0) {
                perror("ERROR read from socket");
                // TO-DO Make error react diffrently
             }

             if (strcmp("", buffer) != 0){
                 std::string bufferStr(buffer); //Convert to C++ Strings
                 std::stringstream ss(bufferStr); //Create a String Stream
                 float tempxyz[3] = {0, 0, 0};
                 ss >> tempxyz[0] >> tempxyz[1] >> tempxyz[2]; //Convert the string to float's
                 xyzMutex.lock();
                 xyz[0] += tempxyz[0];
                 xyz[1] += tempxyz[1];
                 xyz[2] += tempxyz[2];
                 xyzMutex.unlock();
                 std::cout << "X: " << xyz[0] << " Y: " << xyz[1] << " Z: " << xyz[2] << std::endl;
             }
        }
    }
}

float* TcpServer::getChange(){
    float* out = new float[3];
    xyzMutex.lock();
    out[0] = xyz[0];
    out[1] = xyz[1];
    out[2] = xyz[2];
    xyz[0] = 0;
    xyz[1] = 0;
    xyz[2] = 0;
    xyzMutex.unlock();
    return out;
}
