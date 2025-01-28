#pragma once
#define BUFFER_SIZE 1024

#define CLIENT_PORT 8010
#define SERVER_PORT 3005



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
