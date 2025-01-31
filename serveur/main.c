#include "global.h"
#include "fonction.c"

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

    printf("Server listening on port : %d\n",SERVER_PORT);
    
    struct sockaddr_in client_addr;
    socklen_t len;

    int client_fd;


    // PARCOURIR SOCKETS DES DEUX CLIENTS
    while(1) {

        for(int i = 0; i < CLIENTS; i++) {
            client_fd = accept(serv_fd, (struct sockaddr*) &client_addr, &len); perror("accept");
            if(client_fd == -1) return EXIT_FAILURE;
            id_client[i] = client_fd;
        }
        
        for(int i = 0; i < CLIENTS; i++) {
            error = send(id_client[i], "test", 4, 0); perror("send");
            if(error == -1) return EXIT_FAILURE;
        }


        
        ///struc joueur id_client[i]
        struct player player1;
        strcpy(player1.nom, "Yaya");
        player1.victoire = 0;
        player1.choix = 1;
        struct player player2;
        strcpy(player2.nom, "Antho");
        player2.victoire = 0;
        player2.choix = 1;
        
        char player[255]; memset(player, 0, 255);


        ///recv des noms des joueurs
        error = recv(id_client[0], player, sizeof(player), 0); perror("recv");
        strcpy(player1.nom, player);
        memset(player, 0, 255);
        error = recv(id_client[1], player, sizeof(player), 0); perror("recv");
        strcpy(player2.nom, player);




        int round = 1;
        while(1){
            ////RECV DES CHOIX DES JOUEURS
            char buf[255]; memset(buf, 0, 255); ///buffer pour stocker le choix à transferer dans player.choix
            error = recv(id_client[0], buf , sizeof(buf), 0); perror("recv");
            if(error == -1) return EXIT_FAILURE;
            player1.choix = atoi(buf);
            

            error = recv(id_client[1], buf , sizeof(buf), 0); perror("recv");
            if(error == -1) return EXIT_FAILURE;
            player2.choix = atoi(buf);
        
            ///passage par fonction
            updateScore( &player1,&player2);

            round++;


            /// a changer pour un send 
            printf(" nom :%s\n victoire :%d\n choix : %d\n", player1.nom, player1.victoire, player1.choix);
            printf(" \n\n nom :%s\n victoire :%d\n choix : %d\n", player2.nom, player2.victoire, player2.choix);
            if(round > 10){break;}
        }







        // pthread_t scd_client;
        // pthread_create(&scd_client, NULL, thread_accept, NULL);
        // pthread_join(scd_client, NULL);
    }











    close(serv_fd);

    return 0;
}
    












