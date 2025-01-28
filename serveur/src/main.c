#include "shifumi_ligne/client/modules/global.h"

int main() {

    int serv_fd = socket(AF_INET, SOCK_STREAM, 0);perror("socket");
    // Si la création échoue je ferme mon programme
    if(serv_fd == -1) return EXIT_FAILURE;

    struct sockaddr_in server_addr = {
        .sin_addr.s_addr = INADDR_ANY,
        .sin_family = AF_INET,
        .sin_port = htons(SERVER_PORT)
    };

    int error = bind(serv_fd,(struct sockaddr*)&server_addr,sizeof server_addr);perror("bind");
    if(error == -1) { close(serv_fd); return EXIT_FAILURE; }

    error = listen(serv_fd,BUFSIZ);perror("listen");
    if(error == -1) { close(serv_fd); return EXIT_FAILURE; }

    printf("Server listen on port : %d\n",SERVER_PORT);
    
    struct sockaddr_in client_addr;
    socklen_t len;
    int client_fd = accept(serv_fd,(struct sockaddr*)&client_addr,&len);
 
    // int nb_clients_acceptes = 0;

    // for(nb_clients_acceptes; nb_clients_acceptes < 3; nb_clients_acceptes ++) {
        
    // }

