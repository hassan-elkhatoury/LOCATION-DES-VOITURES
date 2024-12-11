#ifndef CLIENT_H
#define CLIENT_H

#include <stdbool.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <ctype.h>
#include <string.h>
#include "display_mod.h"
#include "client.h" 
#include "colors.h" 

void display_car_models_menu(const char *nom);

// Client structure definition
typedef struct {
    char nom[100];
    char address[100];
    char phone[20];
    int age;
    char cin[50];
    char email[50];
    char password[50];
} Client;

bool isValidEmail(const char *email) {
    const char *at = strchr(email, '@');  // pour trouver '@' dans email
    const char *dot = strrchr(email, '.'); // pour trouver '.' dans email

    // verifier si '@' trouvee, '.' trouvee, et '.' vient apres '@'
    return (at != NULL && dot != NULL && dot > at);
}

void getPassword(char *password, int maxLen) {
    int i = 0;
    char ch;
    while (i < maxLen - 1) {
        ch = getch();  
        if (ch == '\r') {
            break;
        } else if (ch == '\b' && i > 0) {  
            i--;
            printf("\b \b");  
        } else if (isprint(ch)) {  
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0'; 
}

int isValidPhoneNumber(const char *phone) {
    if (strlen(phone) != 10) {
        return 0;  
    }
    for (int i = 0; i < 10; i++) {
        if (!isdigit(phone[i])) {
            return 0; 
        }
    }
    return 1;
}



int hasFirstAndLastName(char *fullName) {
    int spaceCount = 0;
    for (int i = 0; i < strlen(fullName); i++) {
        if (isspace(fullName[i])) {
            spaceCount++;
        }
    }
    return spaceCount > 0;
}

void combineNames(char *fullName) {
    char firstName[50], lastName[50], *token;
    char *words[50];
    int count = 0;

    token = strtok(fullName, " ");
    while (token != NULL) {
        words[count++] = token;
        token = strtok(NULL, " ");
    }

    if (count > 1) {
        strcpy(firstName, words[0]);
        strcpy(lastName, words[count - 1]);
        sprintf(fullName, "%s_%s", firstName, lastName);
    }
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

void saisie() {
    Client client1;
    FILE *fsaisie;
    FILE *fclient;
    char test_pass[50];
    char *line = malloc(2000 * sizeof(char)); // Allocate memory for line dynamically
    int error_colone = 58,error_line=37; // Fixed conolne and line for error messages
    static int is_first_call = 1;

    if (line == NULL) {
        fprintf(stderr, "Echec de l'allocation de memoire\n");
        return;
    }

    system("cls"); // Clear the screen

    // Draw the title frame
    cadre1(43,1,54,34, "_");
    cadre1(50, 0, 40, 2, "INSCRIPTION DU CLIENT");
    printf(RESET);
    // Draw frames for input sections
    cadre(45, 3, 50, 3, "Nom Complet:");
    cadre(45, 7, 50, 3, "Adresse:");
    cadre(45, 11, 50, 3, "Numero de Telephone:");
    cadre(45, 15, 50, 3, "Age:");
    cadre(45, 19, 50, 3, "CIN:");
    cadre(45, 23, 50, 3, "Email:");
    cadre(45, 27, 50, 3, "Mot de Passe:");
    cadre(45, 31, 50, 3, "Confirmation de Mot de Passe");

    // Input client details
    gotoxy(47, 5); printf(YELLOW ">> " RESET);
    if (!is_first_call) {clearInputBuffer();} // clear the input buffer
    fgets(client1.nom, sizeof(client1.nom), stdin);
    client1.nom[strcspn(client1.nom, "\n")] = '\0';
    is_first_call = 0;
    if (hasFirstAndLastName(client1.nom)) {
        combineNames(client1.nom);
    }

    gotoxy(47, 9); printf(YELLOW ">> " RESET);
    fgets(client1.address, sizeof(client1.address), stdin);
    client1.address[strcspn(client1.address, "\n")] = '\0';

    // Validate phone number
    while (1) {
        gotoxy(47, 13); printf(YELLOW ">> " RESET);
        scanf("%19s", client1.phone);

        if (isValidPhoneNumber(client1.phone)) {
             gotoxy(error_colone,error_line); printf("                                    "); // Clear invalid input
            gotoxy(error_colone-6,error_line+1); printf("                                              "); // Clear invalid input

            break;
        } else {
            gotoxy(error_colone,error_line); printf(RED "Erreur: Numero invalide!" RESET);
            gotoxy(error_colone-6, error_line+1); printf(RED "Il doit contenir exactement 10 chiffres." RESET);
            gotoxy(47, 13); printf("                       "); // Clear invalid input
        }
    }

    gotoxy(47, 17); printf(YELLOW ">> " RESET);
    scanf("%d", &client1.age);

    gotoxy(47, 21); printf(YELLOW ">> " RESET);
    scanf("%s", client1.cin);

    // Email Validation
    while (1) {
        int email_exists = 0;
        gotoxy(47, 25); printf(YELLOW ">> " RESET);
        scanf("%49s", client1.email);

        if (!isValidEmail(client1.email)) {
            gotoxy(error_colone,error_line); printf(RED "Erreur: Email invalide!                   " RESET);
            gotoxy(error_colone-7,error_line+1); printf(RED "Assurez-vous qu'il contient '@' et '.'." RESET);
            gotoxy(47, 25); printf("                         "); // Clear invalid input

            continue;
        }
        else if (isValidEmail(client1.email)){
            gotoxy(error_colone,error_line); printf("                                                     "); // Clear invalid input
            gotoxy(error_colone-7,error_line+1); printf("                                                      "); // Clear invalid input
        }

        fsaisie = fopen("fsaisie.txt", "r");
        if (fsaisie == NULL) {
            fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
            free(line);
            return;
        }

        while (fgets(line, 2000, fsaisie)) {
            if (strstr(line, client1.email) != NULL) {
                email_exists = 1;
                break;
            }
        }
        fclose(fsaisie);
        if (email_exists) {
            gotoxy(error_colone-3,error_line); printf(RED "Erreur: Cet email existe deja!" RESET);
            gotoxy(47, 25); printf("                         "); // Clear invalid input
        } else {
            gotoxy(error_colone-3,error_line); printf("                                        "); // Clear invalid input
            break;
        }
    }

    // Password Validation
    while (1) {
        gotoxy(47, 29); printf(YELLOW ">> " RESET);
        getPassword(client1.password, sizeof(client1.password));
        printf("\n");

        gotoxy(47, 33);printf(YELLOW ">> " RESET);
        getPassword(test_pass, sizeof(test_pass));
        printf("\n");

        if (strcmp(client1.password, test_pass) == 0) {
            gotoxy(error_colone,error_line); printf("                                                    "); // Clear invalid input
            break;
        } else {
            gotoxy(error_colone,error_line); printf(RED "Erreur: Mot de passe sont pas identiques!" RESET);
            gotoxy(47, 29); printf("                         "); // Clear invalid input
            gotoxy(47, 33); printf("                         "); // Clear invalid input
        }
    }

    // Save client data
    fsaisie = fopen("fsaisie.txt", "a+");
    if (fsaisie == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier fsaisie.txt\n");
        free(line);
        return;
    }

    fprintf(fsaisie, "%s\t%s\t%s\t%d\t%s\t%s\t%s\n", client1.nom, client1.address, client1.phone, client1.age, client1.cin, client1.email, client1.password);
    fclose(fsaisie);

    fclient = fopen("fclient.txt", "a+");
    if (fclient == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier fclient.txt\n");
        free(line);
        return;
    }
    fprintf(fclient, "\n%s\t%s\t%s", client1.nom, client1.email, client1.password);
    fclose(fclient);

    // Success Message
    gotoxy(error_colone, error_line); printf(GREEN"Compte Cree avec Succes");
    gotoxy(error_colone-7,error_line+1); printf(CYAN "Essayez de vous connecter via l'option:" RESET);
    gotoxy(error_colone+1, error_line+2); printf(MAGENTA BOLD "J'ai deja un compte.\n" RESET);
    gotoxy(error_colone-8, error_line+3);printf(RESET "Appuyez sur une touche pour reessayer...");
    getch();
    free(line);
}

void login() {
    FILE *fclient;
    char email[50];
    char password[50];
    Client client1;
    char *line = malloc(2000 * sizeof(char)); // Allocate memory for line dynamically

    if (line == NULL) {
        fprintf(stderr, "echec de l'allocation de memoire\n");
        return;
    }

    while (1) {
        system("cls"); // Clear screen for a fresh login screen
        cadre1(47,4,56,10,"_");
        // Draw login title
        cadre1(55, 3, 40, 2, "LOGIN CLIENT"); // Draw frame for the title

        // Draw table for email input and for password input
            cadre(50, 6, 50, 3, YELLOW "Email:");
            cadre(50, 10, 50, 3, YELLOW "Mot de Passe:");

        
         gotoxy(52, 8); printf(YELLOW ">> " RESET);
        scanf("%49s", email);

        // Validate email
        if (!isValidEmail(email)) {
            gotoxy(46, 16); 
            printf(LIGHT_RED "Erreur: Email invalide! Assurez-vous qu'il contient '@' et '.'");
            gotoxy(56, 17);
            printf(RESET "Appuyez sur une touche pour reessayer...");
            getch();
            continue; // Restart the loop
        }

        // Input for password
        gotoxy(52, 12); printf(YELLOW ">> " RESET); // Position cursor inside the table for password input
        getPassword(password, sizeof(password));
        printf("\n");

        // Open file to check cREDentials
        fclient = fopen("fclient.txt", "r");
        if (fclient == NULL) {
            gotoxy(48, 14);
            printf(LIGHT_RED "Erreur: Impossible d'ouvrir le fichier fclient.txt");
            free(line);
            return;
        }

        int authenticated = 0;
        while (fgets(line, 2000, fclient)) {
            char fileEmail[50], filePassword[50], fileNom[100];

            if (sscanf(line, "%49[^\t]\t%49[^\t]\t%49s", fileNom, fileEmail, filePassword) == 3) {  // [^\t] means any character except tab
                // Check if the email and password match
                if (strcmp(email, fileEmail) == 0 && strcmp(password, filePassword) == 0) {
                    authenticated = 1;
                    strncpy(client1.email, fileEmail, sizeof(client1.email) - 1); // allows to limit the number of characters copied 
                    client1.email[sizeof(client1.email) - 1] = '\0';   
                    strncpy(client1.nom, fileNom, sizeof(client1.nom) - 1);
                    client1.nom[sizeof(client1.nom) - 1] = '\0';
                    break;
                }
            }
        }
        fclose(fclient);

        if (authenticated) {
            // Success Message
            gotoxy(52, 16);
            printf(LIGHT_GREEN "Connexion reussie! Bienvenue, %s." RESET, client1.nom);
            gotoxy(54, 17);
            printf(RESET "Appuyez sur une touche pour continuer...");
            getch();
            display_car_models_menu(client1.nom);
            free(line);
            return;
        } else {
            // Error Message
            gotoxy(54, 16);
            printf(LIGHT_RED "Erreur: Email ou mot de passe incorrect!");
            gotoxy(54, 17);
            printf(RESET "Appuyez sur une touche pour reessayer...");
            getch();
        }
    }

    free(line); // Free memory before exiting
}


#endif // CLIENT_H
