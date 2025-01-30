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
#include <pthread.h> // pr ls threads

#define BUFFER_SIZE 1024
#define SERVER_PORT 7778

#define PIERRE 1
#define FEUILLE 2
#define CISEAUX 3
