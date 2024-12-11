#ifndef DISPLAY_MOD_H
#define DISPLAY_MOD_H

#include "interface.h"
#include "connexion.h"
#include "voiture.h"
#include "display_mod.h"

void connexion();
void display_car_models_menu(const char *nom);

void display_car_models_menu(const char *nom) {
    Options options;
    char *CAR_OPTIONS[] = {
        BOLD "Modeles de voiture",
        BOLD "Recherche d'une voiture ",
        BOLD "Reservation d'une voiture ",
        BOLD "Retour au menu de connexion ",
        BOLD "Quitter le programme"
    };
    snprintf(options.title, sizeof(options.title), YELLOW "BIENVENUE, %s! ", nom);
    options.ops = CAR_OPTIONS;
    options.len = sizeof(CAR_OPTIONS) / sizeof(CAR_OPTIONS[0]);

    int option = select_menu(options);
   
    switch (option) {
        case 0:
            system("cls");
            display_car_models();
            display_car_models_menu(nom);
            break;
        case 1:
            rechercher_voiture(nom);
            break;
        case 2:
            printf("pas en coure...");
            system("pause");
            break;
        case 3: 
            connexion();
        case 4:
            exit(0);
        default:
            printf("Option invalide.\n");
            break;
    } 
    
}


#endif 
