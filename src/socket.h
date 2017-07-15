#include <mutex>
#include <unistd.h>
#include <netinet/in.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include <thread>

#ifndef SOCKET_H
#define SOCKET_H
class TcpServer{
    public:
        TcpServer(char* port);
        float* getChange();
        bool running;
    private:
        std::thread t1;
        float xyz[3];
        std::mutex xyzMutex;
        const int BUFLEN = 5000;
        int sockfd, newsockfd, portno;
        struct sockaddr_in serv_addr, cli_addr;
        void thread();

};
#endif /* SOCKET_H */

