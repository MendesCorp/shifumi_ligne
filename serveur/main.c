#include "global.h"

#define CLIENTS 2

int id_client[BUFFER_SIZE];

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
        
        // init player1 avec valeurs par défaut modifiables avec les entrées utilisateur des clients
        t_player player1;
        strcpy(player1.nom, "joueur");
        player1.victoire = 0;                       
        player1.choix = QUIT;                         

        // init player2
        t_player player2;
        strcpy(player2.nom, "joueur");
        player2.victoire = 0;
        player2.choix = QUIT;
        
        char buf_playerName[255]; memset(buf_playerName, 0, 255);
        // MEMO l'incrémentation sert à vérifier la condition (pour que la boucle s'arrête)

        ///recv des noms des joueurs
        error = recv(id_client[0], buf_playerName, sizeof(buf_playerName), 0); perror("recv");
        if(error == -1) return EXIT_FAILURE;

        if (error > 0) {                                    // si nom joueur a été reçu (error à remplacer par nb_data_recues)
            strcpy(player1.nom, buf_playerName);
            memset(buf_playerName, 0, 255);                 // réinitialise le tableau à 0
            printf("%s a joué\n", player1.nom);
        }

        error = recv(id_client[1], buf_playerName, sizeof(buf_playerName), 0); perror("recv");
        if(error == -1) return EXIT_FAILURE;

        if (error > 0) {
            strcpy(player2.nom, buf_playerName);
            memset(buf_playerName, 0, 255);
            printf("%s a joué\n", player2.nom);
        }
    
        int round = 0 ;
        //char tampon[255];memset(tampon,0,255);
        char score[255]; memset(score, 0, 255);

        while(round < 10) {
            
            ////RECV DES CHOIX DES JOUEURS
            char recup_choix[255]; memset(recup_choix, 0, 255); ///recup_choix = buffer pour stocker le choix à transferer dans player.choix

            error = recv(id_client[0], recup_choix , sizeof(recup_choix), 0); perror("recv");
            if(error == -1) return EXIT_FAILURE;
            player1.choix = writingChoix(recup_choix);
            printf("%s\n", recup_choix);

            memset(recup_choix, 0, 255);

            error = recv(id_client[1], recup_choix , sizeof(recup_choix), 0); perror("recv");
            if(error == -1) return EXIT_FAILURE;
            player2.choix = writingChoix(recup_choix);
            printf("%s\n", recup_choix);

            ///passage par fonction
            updateScore(&player1, &player2, round);

            round++;

            printScore(score, player1, player2); 
            
            error = send(id_client[0], score , sizeof(score), 0); perror("send");
            if(error == -1) return EXIT_FAILURE;

            error = send(id_client[1], score , sizeof(score), 0); perror("send");
            if(error == -1) return EXIT_FAILURE;

        }
    }

    close(serv_fd);

    return 0;
}