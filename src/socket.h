/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   socket.h
 * Author: alexandre
 *
 * Created on 3 de Julho de 2017, 22:58
 */

#ifndef SOCKET_H
#define SOCKET_H
#include <unistd.h>
#include <netinet/in.h>
#include <iostream>
#include <string.h>
#include <sstream>
#ifdef __cplusplus
extern "C" {

#endif

    typedef struct coord;
    coord xyz;
    int socketserv();



#ifdef __cplusplus
}
#endif

#endif /* SOCKET_H */

