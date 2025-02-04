#pragma once
#define BUFFER_SIZE 1024

#define CLIENT_PORT 8026
#define SERVER_PORT 8935

typedef struct player {

    char nom[255];
    int victoire;
    int choix;

}t_player;


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <dirent.h> // Pour lister les fichiers
#include <fcntl.h>  // Pour manipuler les fichiers
#include <sys/stat.h> // Pour les fichiers
