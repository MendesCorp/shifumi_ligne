#include <stdio.h>
#include "global.h"

#define PIERRE 1
#define FEUILLE 2
#define CISEAUX 3



int main() {

    
    struct player player1;
    strcpy(player1.nom, "Yaya");
    player1.victoire = 2;
    player1.choix = 1;

    struct player player2;
    strcpy(player2.nom, "gilbert");
    player2.victoire = 1;
    player2.choix = 2;

    printf(" nom :%s\n victoire :%d\n choix : %d\n", player1.nom, player1.victoire, player1.choix);
    printf(" \n\n nom :%s\n victoire :%d\n choix : %d\n", player2.nom, player2.victoire, player2.choix);

    updateScore( &player1,&player2);
    printf("\n\napres le round : \n\n\n");

    printf(" nom :%s\n victoire :%d\n choix : %d\n", player1.nom, player1.victoire, player1.choix);
    printf(" \n\n nom :%s\n victoire :%d\n choix : %d\n", player2.nom, player2.victoire, player2.choix);

    int a = 1;
    player2.choix = a;
    printf(" \n\n nom :%s\n victoire :%d\n choix : %d\n", player2.nom, player2.victoire, player2.choix);

    //// fonction fonctionnelle (conasse)
    return 0;
}