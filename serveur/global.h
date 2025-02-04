#pragma once
#define PIERRE 1
#define FEUILLE 2
#define CISEAUX 3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <dirent.h> // listing des fichiers
#include <fcntl.h>  // gérer ls fichiers
#include <sys/stat.h> 
#include <pthread.h> // pr ls threads
#define BUFFER_SIZE 1024
#define SERVER_PORT 8936

typedef struct player {

    char nom[255];
    int victoire;
    int choix;

}t_player;
#include "fonction.c"