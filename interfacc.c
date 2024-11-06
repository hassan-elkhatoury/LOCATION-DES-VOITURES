#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
#include <conio.h>

// Define ANSI color codes
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"

// Define ANSI codes for styles
#define BOLD        "\033[1m"
#define ITALIC      "\033[3m"
#define RESET       "\033[0m"

// Windows Console Color Defines
#define black           0
#define blue            1
#define green           2
#define cyan            3  // aqua
#define red             4
#define purple          5
#define yellow          6
#define white           7
#define gray            8
#define light_blue      9
#define light_green     10
#define light_aqua      11
#define light_red       12
#define light_purple    13
#define light_yellow    14
#define bright_white    15

void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
typedef struct {
    char nom[50];
    char address[50];
    char phone[20];

    int age;
    char cin[50];
    char email[50];
    char password[50];
}client;

typedef struct {
 char entreprise[50];
    char modele[50];
    float prix;
}voiture;

int isValidEmail(const char *email) {
    const char *at = strchr(email, '@');  // Find the '@' character
    const char *dot = strrchr(email, '.'); // Find the last '.' character

    // Check if '@' exists, '.' exists, and '.' comes after '@'
    return (at != NULL && dot != NULL && dot > at);
}

void getPassword(char *password, int maxLen) {
    int i = 0;
    char ch;
    while (i < maxLen - 1) {
        ch = getch();  // Read character without displaying it
        if (ch == '\r') {  // Enter key
            break;
        } else if (ch == '\b' && i > 0) {  // Backspace handling
            i--;
            printf("\b \b");  // Remove '*' from screen
        } else if (isprint(ch)) {  // Store printable character
            password[i++] = ch;
            printf("*");  // Display '*' for each character typed
        }
    }
    password[i] = '\0';  // Null-terminate the password
}

int isValidPhoneNumber(const char *phone) {
    if (strlen(phone) != 10) {
        return 0;  // Must be exactly 10 characters
    }
    for (int i = 0; i < 10; i++) {
        if (!isdigit(phone[i])) {
            return 0;  // Each character must be a digit
        }
    }
    return 1;
}



void saisie() {
    client client1,client2;
    FILE *fsaisie;
    char line[2000];
    const char *header ="Nom Complet\t\tAddress\t\t\tPhone\t\tAge\tCIN\t\t\tEmail\t\t\t\tPassword\n";
    
    printf(CYAN);
    printf("Ecrire votre nom complet : \n");
    fgets(client1.nom, sizeof(client1.nom), stdin);
    client1.nom[strcspn(client1.nom, "\n")] = '\0';  // Remove trailing newline if present

    printf("Ecrire votre address : \n");
    fgets(client1.address, sizeof(client1.address), stdin);
    client1.address[strcspn(client1.address, "\n")] = '\0'; 
     while(1){
     printf("ecrire votre phone : \n");
     scanf("%19s", client1.phone);

     if (isValidPhoneNumber(client1.phone)) {
            break;  // Exit loop if phone number is valid
        } else {
            printf(RED"Numero de telephone invalide! Assurez-vous qu'il contient exactement 10 chiffres.\n");
            setColor(cyan); 
        }
     }

     printf("ecrire votre age : \n");
     scanf("%d",&client1.age);
     printf("ecrire votre cin : \n");
     scanf("%s",client1.cin);

   while (1) {
        int email_exists = 0;
        printf("ecrire votre email : \n");
        scanf("%49s", client1.email);

        // Check email format
        while (!isValidEmail(client1.email)) {
            printf(RED"Email invalide! Assurez-vous qu'il contient '@' et '.' \n");
            setColor(cyan);  // Reset color
            printf("Essayez de l'entrer a nouveau :\n");
            scanf("%49s", client1.email);
        }

        // Check if the email already exists
        fsaisie = fopen("fsaisie.txt", "r");
        if (fsaisie != NULL) {
            while (fgets(line, sizeof(line), fsaisie)) {
                if (strstr(line, client1.email) != NULL) {
                    email_exists = 1;
                    break;
                }
            }
            fclose(fsaisie);
        }

        if (email_exists) {
            printf(RED"Cet email est deja existe !!\n");
            setColor(cyan);
            printf("essayez de l'entrer a nouveau !:\n");
        } else {
            break;
        }
    } 

     printf("ecrire votre password : \n");
    getPassword(client1.password, sizeof(client1.password));
    printf("\n");
    printf("ecrire votre password a nouveau : \n");
    getPassword(client2.password, sizeof(client2.password));
    printf("\n");
    if (strcmp(client1.password, client2.password) == 0) {
        printf(GREEN "Merci! Votre compte a ete cree avec succes.\n");
        printf(CYAN  "Veuillez essayer de vous connecter en selectionnant l'option :"MAGENTA" J'ai deja un compte.\n");
        windows("pause");
    } 
        else {
            printf(RED"les deux password sont different \n");
            printf(CYAN"  essayez de l'entrer a nouveau !:\n");
            getPassword(client1.password, sizeof(client1.password));


        }

fsaisie=fopen("fsaisie.txt","a+");
    if(fsaisie==NULL){
        printf(RED"Error in opening file");
        exit(1);
    }
    fseek(fsaisie,0,SEEK_END);
    if(ftell(fsaisie)==0) {
        fprintf(fsaisie,"%s",header);
        fprintf(fsaisie,"%s","-----------------------------------------------------------------------------------------------------\n");
    }
     fprintf(fsaisie,"%s\t%s\t%s\t%s\t%d\t%s\t%s\t%s\n",client1.nom,client1.address,client1.phone,client1.age,client1.cin,client1.email,client1.password);
     fclose(fsaisie);
 }
// Function to log in with an existing account


typedef struct Options{
    char **ops;
    int len;
    char *title;
}Options;

// Function to calculate the visible length of a string (ignoring ANSI codes)
int visible_length(const char *text) {
    int len = 0;
    int in_escape = 0;
    
    while (*text) {
        if (*text == '\033') {  // Start of escape sequence
            in_escape = 1;
        } else if (in_escape && *text == 'm') {  // End of escape sequence
            in_escape = 0;
        } else if (!in_escape) {
            len++;  // Count visible characters
        }
        text++;
    }
    
    return len;
}

// Function to center text with ANSI codes based on console width
void print_centered(const char *text) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Get console screen buffer info
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    
    // Calculate the console width
    int console_width = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    // Calculate the visible text length (ignoring ANSI codes)
    int text_len = visible_length(text);

    // Calculate padding
    int padding = (console_width - text_len) / 2;

    // Print padding spaces
    for (int i = 0; i < padding; i++) {
        printf(" ");
    }

    // Print the actual text with ANSI color codes
    printf("%s\n", text);
}


void draw(int op,Options options){
    system("cls"); 
    char line[50];
    sprintf(line, YELLOW BOLD "%s\n" , options.title);
    print_centered(line);
    for (int i = 0 ; i <  options.len ; i++) { 
        sprintf(line,ITALIC "%s%s%s" RESET, op == i ? BLUE "[" : WHITE " " , options.ops[i], op == i ? BLUE "]" : WHITE " ");
        print_centered(line);  
    }
}

int select_menu(Options options) {
    int current_option = 0;
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);  // Get the input handle

    // Set input mode to enable window input (for arrow keys)
    DWORD mode;
    GetConsoleMode(hInput, &mode);
    SetConsoleMode(hInput, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));

    draw(current_option , options);

    INPUT_RECORD input;
    DWORD events;
    while (1) {
        ReadConsoleInput(hInput, &input, 1, &events);  // Read input from console
        if (input.EventType == KEY_EVENT && input.Event.KeyEvent.bKeyDown) {
            switch (input.Event.KeyEvent.wVirtualKeyCode) {
                case VK_UP:
                    if (current_option > 0) {
                        current_option--;
                        draw(current_option , options);
                    }
                    break;
                case VK_DOWN:
                    if (current_option < options.len-1) {
                        current_option++;
                        draw(current_option , options);
                    }
                    break;
                case VK_RETURN:  // Enter key pressed
                    return current_option;
            }
        }
    }
}

void display_car_models_menu() {
    Options options;
    char *CAR_OPTIONS[] = {
       BOLD "Modeles de voiture",
       BOLD "Sortir",
       BOLD "Reservation d'une voiture"
    };
    options.title = "MENU DES MODELES DE VOITURE";
    options.ops = CAR_OPTIONS;
    options.len = sizeof(CAR_OPTIONS) / sizeof(CAR_OPTIONS[0]);

    int option = select_menu(options);
   
    printf("# Selected: %s\n", options.ops[option]);
    // Implement the logic based on the selected option (e.g., show car models)
}
int login() {
    FILE *fsaisie;
    char email[30];
    char password[50];
    char line[2000];
    int authenticated = 0;
    client client1;

    // Prompt user for email
    setColor(purple);
    printf("Enter your email: ");
    scanf("%49s", email);

    // Prompt user for password (hidden input)
    printf("Enter your password: ");
    getPassword(password, sizeof(password));

    // Open the file to check credentials
    fsaisie = fopen("fsaisie.txt", "r");
    if (fsaisie == NULL) {
        printf(RED"Error opening the file.\n");
        return 0;
    }

    // Search for matching email and password
    while (fgets(line, sizeof(line), fsaisie)) {
        char fileEmail[2000];
        char filePassword[1000];

        // Assuming fields are tab-separated, parse the email and password from the line
        sscanf(line, "%*s %*s %*s %*s %*d %*s %49s %49s", fileEmail, filePassword);

        // Check if email and password match
        if (strcmp(email, fileEmail) == 0 && strcmp(password, filePassword) == 0) {
            authenticated = 1;
            break;
        }
    }
    fclose(fsaisie);

    // Check if login was successful
    if (authenticated) {
    display_car_models_menu();
    
    } 
    else {
        printf(RED "\n Invalid email or password. Please try again.\n");
        return 0;
    }
}
int main() {
   Options options;
    char *LOGIN_OPTIONS[] = {
    BOLD  "Cree un compte",
    BOLD "J'ai deja un compte",
    BOLD "Sortir"
    };
    options.title = "MENU DE CONNECTION";
    options.ops = LOGIN_OPTIONS;
    options.len = sizeof(LOGIN_OPTIONS) / sizeof(LOGIN_OPTIONS[0]);

    int option = select_menu(options);
    switch(option) {
        case 0:
            saisie();
            break;
        case 1:
            login();
            break;
        case 2: 
            exit(0);
            break;
        default:
            printf("Option invalide.\n");
            break;
    } 
}