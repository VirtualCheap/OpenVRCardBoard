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
        static void init(char* port);
        static float* getChange();
        static bool running;
    private:
        static std::thread t1;
        static float xyz[3];
        static std::mutex xyzMutex;
        static const int BUFLEN = 5000;
        static int sockfd, newsockfd, portno;
        static struct sockaddr_in serv_addr, cli_addr;
        static void thread();

};
#endif /* SOCKET_H */

