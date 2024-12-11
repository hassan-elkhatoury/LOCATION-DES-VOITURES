#ifndef VOITURE_H
#define VOITURE_H

#include <conio.h>
#include "interface.h"

#define MAX_CARS 100

typedef struct {
    char marque[50];
    char model[50];
    char prix[10];
    char matricule[20];
    char disponibilite[20];
} Car;

void display_car_models_menu(const char *nom);

// Function to display the car details in a table format
void display_car_table(Car *cars, int count,int startY) {
    int screenWidth = 160; //terminal width
    int tableWidth = 99; // Width of the table
    int startX = (screenWidth - tableWidth) / 2; // X position for centering

    // Table header
    gotoxy(startX, startY++);
    printf(GREEN BOLD "+------------------+------------------+------------------+--------------------+-------------------+\n" RESET);
    gotoxy(startX, startY++);
    printf(GREEN BOLD "| %-16s | %-16s | %-16s | %-18s | %-17s |\n" RESET, "Marque", "Modele", "Prix/jour", "Matricule", "Disponibilite");
    gotoxy(startX, startY++);
    printf(GREEN BOLD "+------------------+------------------+------------------+--------------------+-------------------+\n" RESET);

    // Table rows for each car
    for (int i = 0; i < count; i++) {
        gotoxy(startX, startY++);
        printf(GREEN BOLD "|" RESET " %-16s " GREEN BOLD "|" RESET " %-16s " GREEN BOLD "|" RESET " %-16s " GREEN BOLD "|" RESET " %-18s " GREEN BOLD "|" RESET " %-17s " GREEN BOLD "|\n" RESET,
               cars[i].marque, cars[i].model, cars[i].prix, cars[i].matricule, cars[i].disponibilite);
    }
    gotoxy(startX, startY++);
    printf(GREEN BOLD "+------------------+------------------+------------------+--------------------+-------------------+\n" RESET);
}


// Function to display all car models
void display_car_models() {
    FILE *file = fopen("fvoiture.txt", "r");
    if (file == NULL) {
        printf(RED BOLD "Erreur : Impossible d'ouvrir 'fvoiture.txt'.\n" RESET);
        return;
    }

    Car cars[MAX_CARS]; // Array to hold car data
    int row = 0;
    char line[256];

    // Read each line and parse the car details
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%49s %49s %9s %19s %19s", cars[row].marque, cars[row].model, cars[row].prix, cars[row].matricule, cars[row].disponibilite) == 5) {
            row++;
            if (row >= MAX_CARS) break; // Stop if the array is full
        }
    }

    // Check if any cars were found and display them
    if (row > 0) {
        cadre1(57, 0, 40, 2, "Modeles des voitures");
        display_car_table(cars, row,3); // Use the display_car_table function to display all cars
        gotoxy(58, 35);
        printf(RESET "Appuyez sur une touche pour reessayer...");
        getch();
    } else {
        printf(RED BOLD "\nAucune voiture disponible dans la liste !\n" RESET);
    }

    fclose(file);
}

void R_P_matricule(const char *nom) {
    Car cars[MAX_CARS];
    char terme_recherche1[20] = "";
    char ligne[256];
    int count = 0;
    int trouve = 0;
    static int buffer_cleared = 0;  // Flag to check if the buffer has been cleared

    FILE *fvoiture = fopen("fvoiture.txt", "r");
    if (fvoiture == NULL) {
        printf(RED BOLD "Erreur : Impossible d'ouvrir 'fvoiture.txt'.\n" RESET);
        return;
    }

    // Clear the input buffer only for the first call
    if (!buffer_cleared) {
        while (getchar() != '\n');  // Clear leftover characters in the buffer
        buffer_cleared = 1;  // Mark that the buffer has been cleared
    }

    system("cls");
    // Prompt the user for the matricule to search for
        cadre1(47,3,56,6,"_");
        // Draw login title
        cadre1(55, 2, 40, 2, "Chercher par matricule"); // Draw frame for the title

        // Draw table for email input and for password input
        cadre(50, 5, 50, 3, YELLOW "Entrez le matricule de la voiture :");

    gotoxy(52, 7); printf(YELLOW ">> " RESET);
    fgets(terme_recherche1, sizeof(terme_recherche1), stdin);
    terme_recherche1[strcspn(terme_recherche1, "\n")] = 0; // Remove the newline character

    // Read and compare each line in the file
    while (fgets(ligne, sizeof(ligne), fvoiture)) {
        Car car_temp;
        if (sscanf(ligne, "%49s %49s %9s %19s %19s", 
                   car_temp.marque, 
                   car_temp.model, 
                   car_temp.prix, 
                   car_temp.matricule, 
                   car_temp.disponibilite) == 5) {
            if (strcasecmp(car_temp.matricule, terme_recherche1) == 0) {
                cars[count++] = car_temp; // Add the car to the array
                trouve = 1;
            }
        }
    }

    fclose(fvoiture);

    // Display the results if any cars are found
    if (trouve) {
        cadre1(57, 10, 40, 2, "Modeles des voitures trouvee");
        display_car_table(cars, count ,13); // Show the cars found
        gotoxy(58, 19);
            printf(RESET "Appuyez sur une touche pour reessayer...");
            getch();
    } else {
         gotoxy(47, 11);printf(RED BOLD "Aucune voiture trouvee correspondant au matricule fournie.\n" RESET);
        gotoxy(55, 12);
        printf(RESET "Appuyez sur une touche pour reessayer...");
        getch();
    }
}


void R_P_marque(const char *nom) {
    Car cars[MAX_CARS];
    char terme_recherche[50] = "";
    char ligne[256];
    int count = 0;
    int trouve = 0;
    static int buffer_cleared = 0;  // Flag to check if the buffer has been cleared

    FILE *fvoiture = fopen("fvoiture.txt", "r");
    if (fvoiture == NULL) {
        printf(RED BOLD "Erreur : Impossible d'ouvrir 'fvoiture.txt'.\n" RESET);
        return;
    }

    // Clear the input buffer only for the first call
    if (!buffer_cleared) {
        while (getchar() != '\n');  // Clear leftover characters in the buffer
        buffer_cleared = 1;  // Mark that the buffer has been cleared
    }
        system("cls");
         // Prompt the user for the marque to search for
        cadre1(47,3,56,6,"_");
        // Draw login title
        cadre1(55, 2, 40, 2, "Chercher par marque"); // Draw frame for the title

        // Draw table for email input and for password input
        cadre(50, 5, 50, 3, YELLOW "Entrez la marque de la voiture :");

    gotoxy(52, 7); printf(YELLOW ">> " RESET);
    fgets(terme_recherche, sizeof(terme_recherche), stdin);
    terme_recherche[strcspn(terme_recherche, "\n")] = 0; // Remove the newline character

    // Convert the input to lowercase for case-insensitive search
    for (int i = 0; terme_recherche[i]; i++) {
        terme_recherche[i] = tolower(terme_recherche[i]);
    }

    // Read and compare each line in the file
    while (fgets(ligne, sizeof(ligne), fvoiture)) {
        Car car_temp;
        if (sscanf(ligne, "%49s %49s %9s %19s %19s", 
                   car_temp.marque, 
                   car_temp.model, 
                   car_temp.prix, 
                   car_temp.matricule, 
                   car_temp.disponibilite) == 5) {
            // Convert the car marque to lowercase for comparison
            for (int i = 0; car_temp.marque[i]; i++) {
                car_temp.marque[i] = tolower(car_temp.marque[i]);
            }

            if (strstr(car_temp.marque, terme_recherche) != NULL) {
                cars[count++] = car_temp; // Add the car to the array
                trouve = 1;
            }
        }
    }

    fclose(fvoiture);

    // Display the results if any cars are found
    if (trouve) {
        cadre1(57, 10, 40, 2, "Modeles des voitures trouvee");
        display_car_table(cars, count,13); // Show the cars found
        gotoxy(58, 19);
            printf(RESET "Appuyez sur une touche pour reessayer...");
            getch();    
            } else {
         gotoxy(47, 11);printf(RED BOLD "Aucune voiture trouvee correspondant au matricule fournie.\n" RESET);
        gotoxy(55, 12);
        printf(RESET "Appuyez sur une touche pour reessayer...");
        getch();

    }
}

void rechercher_voiture(const char *nom) {
    Options options;
    char *LOGIN_OPTIONS[] = {
        BOLD "Chercher par marque ",
        BOLD "Chercher par matricule",
        BOLD "Retour"
    };

    strcpy(options.title, YELLOW "RECHERCHE D'UNE VOITURE ");
    options.ops = LOGIN_OPTIONS;
    options.len = sizeof(LOGIN_OPTIONS) / sizeof(LOGIN_OPTIONS[0]);
    int option = select_menu(options);

    switch (option) {
        case 0: // Search by brand
            R_P_marque(nom);
            display_car_models_menu(nom);
            break;
        case 1: // Search by matricule
            R_P_matricule(nom);
            display_car_models_menu(nom);
            break;
        case 2: // Return to car models menu
            display_car_models_menu(nom);
            break;
        default: // Invalid option
            printf("Choix invalide.\n");
            exit(0);
    }
}
#endif