#pragma once
#include "global.h"



/**
 * @param player1->choix Le choix du joueur 1 PIERRE(1), FEUILLE(2) ou CISEAUX(3)
 * @param player2->choix Le choix du joueur 2 PIERRE(1), FEUILLE(2) ou CISEAUX(3)
 */
void updateScore(struct player *player1,struct player *player2) {


    // Condition de vistoire du joueur 1
    if((player1->choix == PIERRE && player2->choix == CISEAUX) || (player1->choix == FEUILLE && player2->choix == PIERRE) || (player1->choix == CISEAUX && player2->choix == FEUILLE)) {
    
        player1->victoire ++;

    }else if ((player2->choix == PIERRE && player1->choix == CISEAUX) || (player2->choix == FEUILLE && player1->choix == PIERRE) || (player2->choix ==  CISEAUX && player1->choix == FEUILLE)) {
       
        player2->victoire ++;
    }
    
    if (player1->choix == player2->choix) {
        printf ("Ex- aequo\n");
    }

    return;
}

