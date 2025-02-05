#pragma once
#include "global.h"

/**
 * @param player1->choix Le choix du joueur 1 PIERRE(1), FEUILLE(2) ou CISEAUX(3)
 * @param player2->choix Le choix du joueur 2 PIERRE(1), FEUILLE(2) ou CISEAUX(3)
 */
void updateScore(struct player *player1,struct player *player2) {

    // Condition de victoire du joueur 1
    if((player1->choix == PIERRE && player2->choix == CISEAUX) || (player1->choix == FEUILLE && player2->choix == PIERRE) || (player1->choix == CISEAUX && player2->choix == FEUILLE)) {
    
        player1->victoire ++;
    // Condition de victoire du joueur 2
    }else if ((player2->choix == PIERRE && player1->choix == CISEAUX) || (player2->choix == FEUILLE && player1->choix == PIERRE) || (player2->choix ==  CISEAUX && player1->choix == FEUILLE)) {
       
        player2->victoire ++;
    }
    // En cas d'égalité
    if (player1->choix == player2->choix) {
        printf ("Ex- aequo\n");
    }

    return;
}

// fonction qui prend en compte les != façons d'ortographier 
int writingChoix(struct player *player1,struct player *player2) {

    if (strcmp(player1->choix && player2->choix, "1") == 0 || strcmp(player1->choix && player2->choix, "pierre") == 0 || strcmp(player1->choix && player2->choix, "p") == 0) {return PIERRE;}
    
    if (strcmp(player1->choix && player2->choix, "2") == 0 || strcmp(player1->choix && player2->choix, "feuille") == 0 || strcmp(player1->choix && player2->choix, "f") == 0) {return FEUILLE;}

    if (strcmp(player1->choix && player2->choix, "3") == 0 || strcmp(player1->choix && player2->choix, "ciseaux") == 0 || strcmp(player1->choix && player2->choix, "c") == 0) {return CISEAUX;}
}

void printScore(char *score, struct player player1, struct player player2) {

    sprintf(score,
    "nom :%s\n victoire :%d\n choix : %d\n \n\n"
    "nom :%s\n victoire :%d\n choix : %d\n",
    player1.nom, player1.victoire, player1.choix,
    player2.nom, player2.victoire, player2.choix);
}
