#include "global.h"

#define CLIENTS 2

int id_client[BUFSIZ];

void * thread_accept(void* arg) {

    int serv_fd = socket(AF_INET, SOCK_STREAM, 0);perror("socket");
    int error = listen(serv_fd, BUFSIZ); perror("listen");
    if(error == -1) return NULL;

    printf("Server listen on port : %d\n",SERVER_PORT);
    
    struct sockaddr_in client_addr;
    socklen_t len;

    int client_fd = accept(serv_fd, (struct sockaddr*) &client_addr, &len); perror("accept");
    if(client_fd == -1) return NULL;
}

int main() {

    int serv_fd = socket(AF_INET, SOCK_STREAM, 0);perror("socket");
    // Si la création échoue je ferme mon programme
    if(serv_fd == -1) return EXIT_FAILURE;

    struct sockaddr_in serv_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(SERVER_PORT),
        .sin_addr.s_addr = INADDR_ANY
    };

    int error = bind(serv_fd, (struct sockaddr*) &serv_addr, sizeof serv_addr); perror("bind");
    if(error == -1) return EXIT_FAILURE; 

    error = listen(serv_fd, BUFSIZ); perror("listen");
    if(error == -1) return EXIT_FAILURE; 

    printf("Server listen on port : %d\n",SERVER_PORT);
    
    struct sockaddr_in client_addr;
    socklen_t len;

    int client_fd;


    // PARCOURIR SOCKETS DES DEUX CLIENTS
    for(int i = 0; i < CLIENTS; i++) {
        client_fd = accept(serv_fd, (struct sockaddr*) &client_addr, &len); perror("accept");
        if(client_fd == -1) return EXIT_FAILURE;
        id_client[i] = client_fd;
    }
    
    for(int i = 0; i < CLIENTS; i++) {
        error = send(id_client[i], "test", 4, 0); perror("send");
        if(error == -1) return EXIT_FAILURE;
    }



    char buf[255]; memset(buf, 0, 255);

    pthread_t scd_client;
    pthread_create(&scd_client, NULL, thread_accept, NULL);
    pthread_join(scd_client, NULL);












    close(serv_fd);

    return 0;
}
    












