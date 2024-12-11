#ifndef FRST_MENU_H
#define FRST_MENU_H

#include "interface.h"
#include "connexion.h"

void connexion();
void frstmenu() {
    Options options;
    char *LOGIN_OPTIONS[] = {
        BOLD "je suis un client ",
        BOLD "je suis un emploiye ",
        BOLD "Quitter le programme"
    };
    strcpy(options.title, YELLOW "BIENVENUE AU SITE DE RESERVATION DES VOITURES ");
    options.ops = LOGIN_OPTIONS;
    options.len = sizeof(LOGIN_OPTIONS) / sizeof(LOGIN_OPTIONS[0]);

    int option = select_menu(options);
    switch (option) {
        case 0:
            connexion();
            break;
        case 1:
            printf("nous avons encoure ...");
            system("pause");
            break;
        case 2: 
            exit(0);
            break;
        default:
            printf("Option invalide.\n");
            break;
    } 
}

#endif 
