#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <dirent.h> // Pour lister les fichiers
#include <fcntl.h>  // Pour manipuler les fichiers
#include <sys/stat.h> // Pour les fichiers

#define PIERRE 1
#define FEUILLE 2
#define CISEAUX 3
#define QUIT 0
#define BUFFER_SIZE 1024

#define CLIENT_PORT 4016
#define SERVER_PORT 2730
typedef struct player {

    char nom[255];
    int victoire;
    int choix;

}t_player;
