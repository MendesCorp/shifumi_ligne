#include "global.h"
#include "fonction.c"

#define CLIENTS 2

int id_client[BUFFER_SIZE];

void * thread_accept(void* arg) {

    // int serv_fd = socket(AF_INET, SOCK_STREAM, 0);perror("socket");
    // int error = listen(serv_fd, BUFFER_SIZE); perror("listen");
    // if(error == -1) return NULL;

    //printf("Server listen on port : %d\n",SERVER_PORT);
    
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

    error = listen(serv_fd, BUFFER_SIZE); perror("listen");
    if(error == -1) return EXIT_FAILURE; 

    printf("Server listening on port : %d\n",SERVER_PORT);
    

    // PARCOURIR SOCKETS DES DEUX CLIENTS
    while(1) {

        struct sockaddr_in client_addr;
        socklen_t len;
        int client_fd;
        
        for(int i = 0; i < CLIENTS; i++) {
            client_fd = accept(serv_fd, (struct sockaddr*) &client_addr, &len); perror("accept");
            if(client_fd == -1) return EXIT_FAILURE;

            id_client[i] = client_fd;                   // id_client[i] pour distinguer les deux clients 
            printf("client[%d] connecté\n",i);
        }
        
        // init player1 
        t_player player1;
        strcpy(player1.nom, "joueur");
        player1.victoire = 0;                           //struct avec valeurs par défaut qu'on va ensuite venir modifier avec les entrées utilisateur des clients
        player1.choix = QUIT;                           // #define -1 possible pour nochoice

        // init player2
        t_player player2;
        strcpy(player2.nom, "joueur");
        player2.victoire = 0;
        player2.choix = QUIT;
        
        char buf_name_player[255]; memset(buf_name_player, 0, 255);
        // MEMO incrémentation pour vérifier la condition (pour que la boucle s'arrête)

        ///recv des noms des joueurs
        error = recv(id_client[0], buf_name_player, sizeof(buf_name_player), 0); perror("recv");
        if(error == -1) return EXIT_FAILURE;

        if (error > 0) {        // si nom joueur a été reçu (error à remplacer par nbdatarecues)
            strcpy(player1.nom, buf_name_player);
            memset(buf_name_player, 0, 255);                 // réinitialise le tableau à 0
            printf("%s est connecté\n", player1.nom);
            
        }

        error = recv(id_client[1], buf_name_player, sizeof(buf_name_player), 0); perror("recv");

        if (error > 0) {
            strcpy(player2.nom, buf_name_player);
            memset(buf_name_player, 0, 255);
            printf("%s est connecté\n", player2.nom);
            
        }
        

        int round = 0 ;
        char tampon[255];memset(tampon,0,255);
        char score[255]; memset(score, 0, 255);

        while(round < 10) {
            ////RECV DES CHOIX DES JOUEURS
            char recup_choix[255]; memset(recup_choix, 0, 255); ///recup_choixfer pour stocker le choix à transferer dans player.choix

            error = recv(id_client[0], recup_choix , sizeof(recup_choix), 0); perror("recv");
            if(error == -1) return EXIT_FAILURE;
            player1.choix = writingChoix(recup_choix);
            printf("%s\n", recup_choix);

            memset(recup_choix, 0, 255);

            error = recv(id_client[1], recup_choix , sizeof(recup_choix), 0); perror("recv");
            if(error == -1) return EXIT_FAILURE;
            player2.choix = writingChoix(recup_choix);
            printf("%s\n", recup_choix);

            // error = send(id_client[0], tampon , sizeof(tampon), 0); perror("send"); ///tempon a renvoyer au joueur opposé
            // if(error == -1) return EXIT_FAILURE;

            // error = send(id_client[1], tampon , sizeof(tampon), 0); perror("send");  ///tempon a renvoyer au joueur opposé
            // if(error == -1) return EXIT_FAILURE;



            ///passage par fonction
            updateScore(&player1,&player2);

            round++;

            printScore(score, player1, player2); 
            
            error = send(id_client[0], score , sizeof(score), 0); perror("send");
            if(error == -1) return EXIT_FAILURE;

            error = send(id_client[1], score , sizeof(score), 0); perror("send");
            if(error == -1) return EXIT_FAILURE;


            //if(round > 10){break;}
        }

        int results;
        results = atoi(score);

        *score = (player1.victoire, player1.choix, player2.victoire, player2.choix);
        printf("score : %s \n", score);
        sprintf(score, "victoire %s : %d\nvictoire %s : %d\n", player1.nom, player1.victoire, player2.nom, player2.victoire); //sprintf pr séréaliser
        error = send(serv_fd, score, sizeof(score), 0); perror("send");
        if(error == -1) return EXIT_FAILURE;
    }


    close(serv_fd);

    return 0;
}