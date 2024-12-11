#ifndef CONNEXION_H
#define CONNEXION_H

#include "client.h"
#include "interface.h"
#include "frst_menu.h"

void saisie();
void login();
int select_menu(Options options);

void connexion();
void connexion() {
    Options options;
    char *LOGIN_OPTIONS[] = {
        BOLD "Cree un compte",
        BOLD "J'ai deja un compte ",
        BOLD "Retour au menu principal",
        BOLD "Quitter le programme",
    };
    strcpy(options.title, YELLOW "MENU DE CONNECTION");
    options.ops = LOGIN_OPTIONS;
    options.len = sizeof(LOGIN_OPTIONS) / sizeof(LOGIN_OPTIONS[0]);
    
    int option = select_menu(options);
    switch (option) {
        case 0:
            saisie();
            connexion();  
            break;
        case 1:
            login();
            break;
        case 2: 
            frstmenu();
            break;
        case 3:
        exit(0);
        default:
            printf("Option invalide.\n");
            break;
    } 
}

#endif
