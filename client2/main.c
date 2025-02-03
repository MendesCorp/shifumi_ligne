#include "global.h"


int main(){

    /**
     * socket
     * Je crée le socket client
     */
    int client_fd = socket(AF_INET,SOCK_STREAM,0);perror("socket");
    // Si la création échoue je ferme mon programme
    if(client_fd == -1) return EXIT_FAILURE;

    /**
     * bind
     * Je relie le socket à un port et une ip avec la fonction bind()
     */
    struct sockaddr_in client_addr = {
        .sin_addr.s_addr = INADDR_ANY,
        .sin_family = AF_INET,
        .sin_port = htons(CLIENT_PORT)
    };
    int error = bind(client_fd,(struct sockaddr*)&client_addr,sizeof client_addr);perror("bind");
    if(error == -1) { close(client_fd); return EXIT_FAILURE; }

    /**
     * connect
     * Je connecte mon socket client au socket server situé en 127.0.0.1:SERVER_PORT
     */
    struct sockaddr_in serv_addr = {
        .sin_addr.s_addr = inet_addr("127.0.0.1"), // Attention à ne pas mettre INADDR_ANY !
        .sin_family = AF_INET,
        .sin_port = htons(SERVER_PORT)
    };

    error = connect(client_fd,(struct sockaddr*)&serv_addr,sizeof serv_addr);perror("connect");
    if(error == -1) { close(client_fd); return EXIT_FAILURE; }

        // SOCKET CLIENT PRET A COMMUNIQUER !
        char player[255]; memset(player, 0, 255);
        char choix[255]; memset(choix, 0, 255);
        char tampon[255];memset(tampon,0,255);
        printf("Qui est en train de jouer ?\n");
        fgets(player, 255, stdin);
        player[strcspn(player, "\n")] = 0;

        error = send(client_fd, player, sizeof(player), 0);
        while (1){
          
        printf("Pierre, feuille, ciseaux ?\n");
        fgets(choix, 255, stdin);
        choix[strcspn(choix, "\n")] = 0;


        error = send(client_fd, choix, sizeof(choix), 0);
        error = recv(client_fd,tampon,sizeof(tampon),0); /// tampon, qui me permet d'attendre l'autre joueur
        }
 

close(client_fd);

}