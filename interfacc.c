#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
// Define ANSI color codes
#define RESET       "\033[0m"
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
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

typedef struct {
    char nom[50];
    char prenom[50];
    char address[50];
    int phone,age;
    char cin[50];
    char email[50];
    char password[50];
}client;

typedef struct {
 char entreprise[50];
    char modele[50];
    float prix;
}voiture;

void saisie() {
    client client1;
    FILE *fsaisie;
    char line[2000];
    const char *header ="nom\t\tprenom\t\taddress\t\t\tphone\t\tage\tcin\t\t\temail\t\t\t\tpassword\n";
    
    setColor(3);
     printf("ecrire votre nom : \n");
     scanf("%s",client1.nom);
     printf("ecrire votre prenom : \n");
     scanf("%s",client1.prenom);
     printf("ecrire votre address : \n");
     scanf("%s",client1.address);
     printf("ecrire votre phone : \n");
     scanf("%d",&client1.phone);
     printf("ecrire votre age : \n");
     scanf("%d",&client1.age);
     printf("ecrire votre cin : \n");
     scanf("%s",client1.cin);

    printf("ecrire votre email : \n");
    scanf("%s",client1.email);


    fsaisie = fopen("fsaisie.txt", "r");

        while (fgets(line, sizeof(line), fsaisie)) {
            while (strstr(line, client1.email) != NULL) {
                printf(" \033[31m cet email est deja existe !!\n");
                setColor(3);
                printf("essayez de l'entrer a nouveau !:\n");
                scanf("%s",client1.email);
            }
        }
    fclose(fsaisie);  

     printf("ecrire votre password : \n");
    scanf("%s",client1.password);
fsaisie=fopen("fsaisie.txt","a+");
    if(fsaisie==NULL){
        printf("Error in opening file");
        exit(1);
    }
    fseek(fsaisie,0,SEEK_END);
    if(ftell(fsaisie)==0) {
        fprintf(fsaisie,"%s",header);
        fprintf(fsaisie,"%s","-----------------------------------------------------------------------------------------------------\n");
    }
     fprintf(fsaisie,"%s\t%s\t%s\t%d\t%d\t%s\t%s\t%s\n",client1.nom,client1.prenom,client1.address,client1.phone,client1.age,client1.cin,client1.email,client1.password);
     fclose(fsaisie);
 }

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
    sprintf(line, MAGENTA BOLD "%s\n" , options.title);
    print_centered(line);
    for (int i = 0 ; i <  options.len ; i++) { 
        sprintf(line,ITALIC "%s%s%s" RESET, op == i ? GREEN "[" : WHITE " " , options.ops[i], op == i ? GREEN "]" : WHITE " ");
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

int main() {
    
    Options options ;
    char *MAIN_OPTIONS[] = {
        "cree un compte",
        "j'ai deja un compte",
        "les modules des voiture",
        "reservation d'une voiture",
        "sort"
    };
    options.title = "BIENVENUE SUR LE SITE DE RESERVATION DE VOITURE";


    options.ops = MAIN_OPTIONS;
    options.len = sizeof(MAIN_OPTIONS) / sizeof(MAIN_OPTIONS[0]);

    int option = select_menu(options);
    if(options.ops[option]=="cree un compte"){
        saisie();
    }
    else if (options.ops[option]=="j'ai deja un compte"){
        printf("hello");    
    }
    else if (options.ops[option]=="les modules des voiture"){
    
    }
    else if (options.ops[option]=="reservation d'une voiture"){
    
    }
    else if (options.ops[option]=="sort"){
            exit(0);
    }

    return 0;
}