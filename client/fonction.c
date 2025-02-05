#pragma once
#include "global.h"

// fonction qui prend en compte les != façons d'ortographier 
char writingChoix(char *choix) {

    if(strcmp(choix, "1") == 0 || strcmp(choix, "pierre") == 0 || strcmp(choix, "p") == 0) {return PIERRE;}
   
    if(strcmp(choix, "2") == 0 || strcmp(choix, "feuille") == 0 || strcmp(choix, "f") == 0) {return FEUILLE;}

    if(strcmp(choix, "3") == 0 || strcmp(choix, "ciseaux") == 0 || strcmp(choix, "c") == 0) {return CISEAUX;}
}