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

    printf("pre-boucle while\n");
    // PARCOURIR SOCKETS DES DEUX CLIENTS
    while(1) {

        printf("pre-boucle for; dans boucle while\n");
        
        for(int i = 0; i < CLIENTS; i++) {
            client_fd = accept(serv_fd, (struct sockaddr*) &client_addr, &len); perror("accept");
            if(client_fd == -1) return EXIT_FAILURE;

            id_client[i] = client_fd;   // id_client[i] pour distinguer les deux clients 
            printf("client[%d] connecté\n",i);
        }
        

        struct player player1;
        strcpy(player1.nom, "joueur");
        player1.victoire = 0;                           //struct avec valeurs par défaut qu'on va ensuite venir modifier avec les entrées utilisateur des clients
        player1.choix = 1;

        struct player player2;
        strcpy(player2.nom, "joueur");
        player2.victoire = 0;
        player2.choix = 0;
        
        char player[255]; memset(player, 0, 255);
        int nb_recv = 0;

        while(nb_recv < 2) {
            ///recv des noms des joueurs
            error = recv(id_client[0], player, sizeof(player), 0); perror("recv");
            if(error == -1) return EXIT_FAILURE;

            if (error > 0){

                strcpy(player1.nom, player);
                memset(player, 0, 255);     // réinitialise le tableau à 0
                printf("%s a joué\n", player1.nom);
                nb_recv++;

            }else{ perror("recv");}

                error = recv(id_client[1], player, sizeof(player), 0); perror("recv");

            if (error > 0){

                strcpy(player2.nom, player);
                memset(player, 0, 255);
                printf("%s a joué\n", player2.nom);
                nb_recv++;
                
            }else{ perror("recv");}
        }

        int round = 0 ;
        char tampon[255];memset(tampon,0,255);
        char score[255]; memset(score, 0, 255);

        while(1){
            ////RECV DES CHOIX DES JOUEURS
            char buf[255]; memset(buf, 0, 255); ///buffer pour stocker le choix à transferer dans player.choix

            error = recv(id_client[0], buf , sizeof(buf), 0); perror("recv");
            if(error == -1) return EXIT_FAILURE;
            player1.choix = atoi(buf);

            error = send(id_client[1], tampon , sizeof(tampon), 0); perror("send");  ///tempon a renvoyer au joueur opposé
            if(error == -1) return EXIT_FAILURE;

            error = recv(id_client[1], buf , sizeof(buf), 0); perror("recv");
            if(error == -1) return EXIT_FAILURE;
            player2.choix = atoi(buf);

            error = send(id_client[0], tampon , sizeof(tampon), 0); perror("send"); ///tempon a renvoyer au joueur opposé
            if(error == -1) return EXIT_FAILURE;

            ///passage par fonction
            updateScore( &player1,&player2);

            round++;
            /// a changer pour un send 

            printScore(score, player1, player2); 
            
            error = send(id_client[0], score , sizeof(score), 0); perror("send");
            if(error == -1) return EXIT_FAILURE;

            error = send(id_client[1], score , sizeof(score), 0); perror("send");
            if(error == -1) return EXIT_FAILURE;


            if(round > 10){break;}
        }

            
            int results;
            results = atoi(score);

            *score = (player1.victoire, player1.choix, player2.victoire, player2.choix);
            error = send(serv_fd, score, sizeof(score), 0); perror("send");
            if(error == -1) return EXIT_FAILURE;






        // pthread_t scd_client;
        // pthread_create(&scd_client, NULL, thread_accept, NULL);
        // pthread_join(scd_client, NULL);
    }











    close(serv_fd);

    return 0;
}
    












