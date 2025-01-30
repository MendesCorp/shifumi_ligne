#pragma once
#include "global.h"

char player1[255];
char player2[255];
int choix_p1;   int choix_p2;
int tour  = 0;
int victoire_p1 = 0;    int defaite_p1 = 0;
int victoire_p2 = 0;    int defaite_p2 = 0;

// void player (char *prenom) {

//     printf("Qui est en train de jouer ?\n");
//     fgets(*player1 & *player2, 255, stdin);
    
// }

int result (choix_p1, choix_p2) {

    for(int i = 0; i < tour; i++) {

        if((choix_p1 == 1 && choix_p2 == 3) && (choix_p1 == 2 && choix_p2 == 1) && (choix_p1 == 3 && choix_p2 == 2)) {
            printf("%s gagne pour cette fois\n", player1);
            victoire_p1 ++;
            defaite_p2 ++;

        }else if ((choix_p2 == 1 && choix_p1 == 3) && (choix_p2 == 2 && choix_p1 == 1) && (choix_p2 == 3 && choix_p1 == 3)) {
            printf ("bravo %s tu as gagné cette partie\n", player2);
            victoire_p2 ++;
            defaite_p1 ++;
        }

        }if (choix_p1 == choix_p2) {
            printf ("Ex- aequo\n");
            tour ++;
        }
}

