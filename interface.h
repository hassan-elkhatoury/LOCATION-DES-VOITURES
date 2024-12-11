#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include <string.h>
#include "colors.h"

// Options structure for menu options
typedef struct Options {
    char **ops;
    int len;
    char title[100];
} Options;

int visible_length(const char *text) {
    int len = 0;
    int in_escape = 0;
    
    while (*text) {
        if (*text == '\033') {  
            in_escape = 1;
        } else if (in_escape && *text == 'm') {  
            in_escape = 0;
        } else if (!in_escape) {
            len++;  
        }
        text++;
    }
    return len;
}

void cadre(int x, int y, int width, int height, const char *title) {
    char line[200];

    // Top border
    gotoxy(x, y);
    printf(GREEN BOLD "%c", 201); // Top-left corner
    for (int i = 0; i < width; i++) {
        printf("%c", 205); // Horizontal line
    }
    printf("%c\n" RESET, 187); // Top-right corner

    // Title (centered)
    if (title != NULL && strlen(title) > 0) {
        snprintf(line, sizeof(line), YELLOW BOLD "%s" RESET, title);
        int padding = (width - visible_length(line)) / 2;
        gotoxy(x , y + 1);
        printf(GREEN BOLD "%c" RESET, 186); // Left border
        printf("%*s%s%*s", padding, "", line, padding, "");
        if (width % 2 != visible_length(line) % 2) {
            printf(" "); // Adjust padding for odd widths (impair)
        }
        printf(GREEN BOLD "%c\n" RESET, 186); // Right border
    }

    // Empty rows
    for (int i = 2; i < height; i++) {
        gotoxy(x, y + i);
        printf(GREEN BOLD "%c" RESET, 186); // Left border
        for (int j = 0; j < width; j++) {
            printf(" "); // Empty space
        }
        printf(GREEN BOLD "%c\n" RESET, 186); // Right border
    }

    // Bottom border
    gotoxy(x, y + height);
    printf(GREEN BOLD "%c", 200); // Bottom-left corner
    for (int i = 0; i < width; i++) {
        printf("%c", 205); // Horizontal line
    }
    printf("%c\n" RESET, 188); // Bottom-right corner
}

void cadre1(int x, int y, int width, int height, const char *title) {
    char line[200];

    // Top border
    gotoxy(x, y);
    printf(LIGHT_MAGENTA BOLD "%c", 201); // Top-left corner
    for (int i = 0; i < width; i++) {
        printf("%c", 205); // Horizontal line
    }
    printf("%c\n" RESET, 187); // Top-right corner

    // Title (centered)
    if (title != NULL && strlen(title) > 0) {
        snprintf(line, sizeof(line), LIGHT_BLUE BOLD "%s" RESET, title);
        int padding = (width - visible_length(line)) / 2;
        gotoxy(x , y + 1);
        printf(LIGHT_MAGENTA BOLD "%c" RESET, 186); // Left border
        printf("%*s%s%*s", padding, "", line, padding, "");
        if (width % 2 != visible_length(line) % 2) {
            printf(" "); // Adjust padding for odd widths
        }
        printf(LIGHT_MAGENTA BOLD "%c\n" RESET, 186); // Right border
    }

    // Empty rows
    for (int i = 2; i < height; i++) {
        gotoxy(x, y + i);
        printf(LIGHT_MAGENTA BOLD "%c" RESET, 186); // Left border
        for (int j = 0; j < width; j++) {
            printf(" "); // Empty space
        }
        printf(LIGHT_MAGENTA BOLD "%c\n" RESET, 186); // Right border
    }

    // Bottom border
    gotoxy(x, y + height);
    printf(LIGHT_MAGENTA BOLD "%c", 200); // Bottom-left corner
    for (int i = 0; i < width; i++) {
        printf("%c", 205); // Horizontal line
    }
    printf("%c\n" RESET, 188); // Bottom-right corner
}

void draw(int op, Options options) {
    system("cls"); // Clear the console

    int width = 60; // Width of the table
    char line[200];

    printf("\n");

    // Top border of the table
    gotoxy(45, 1); 
    printf(GREEN BOLD"%c", 201); // Top-left corner
    for (int i = 0; i < width; i++) {
        printf("%c", 205); // Horizontal line
    }
    printf("%c\n"RESET, 187); // Top-right corner

    // Centered title inside the table
    snprintf(line, sizeof(line), YELLOW BOLD"%s"RESET, options.title);
    int padding = (width - visible_length(line)) / 2;
    gotoxy(45, 2); 
    printf(GREEN BOLD"%c"RESET, 186); // Left vertical line
    printf("%*s%s%*s", padding, "", line, padding, "");
    if (width % 2 != visible_length(line) % 2) { 
        printf(" "); // Adjust padding for odd widths
    }
    printf(GREEN BOLD"%c\n", 186); // Right vertical line

    // Divider
    gotoxy(45, 3); 
    printf("%c", 204); // Left T-junction
    for (int i = 0; i < width; i++) {
        printf("%c", 205); // Horizontal line
    }
    printf("%c\n"RESET, 185); // Right T-junction

    // Options
    for (int i = 0; i < options.len; i++) {
        // Construct the line for each option
        if (op == i) {
            snprintf(line, sizeof(line), YELLOW BOLD">>"BLUE" %s "YELLOW BOLD"<<"RESET, options.ops[i]);
        } else {
            snprintf(line, sizeof(line), "   %s   ", options.ops[i]);
        }

        // Center the option line within the table
        padding = (width - visible_length(line)) / 2;
        gotoxy(45, 4 + i); 
        printf(GREEN BOLD"%c"RESET, 186); // Left vertical line
        printf( "%*s%s%*s", padding, "", line, padding, "");
        if (width % 2 != visible_length(line) % 2) { 
            printf(" "); // Adjust padding for odd widths
        }
        printf(GREEN BOLD"%c\n"RESET, 186); // Right vertical line
    }

    // Bottom border of the table
    gotoxy(45, 4 + options.len);
    printf(GREEN BOLD"%c", 200); // Bottom-left corner
    for (int i = 0; i < width; i++) {
        printf("%c", 205); // Horizontal line
    }
    printf("%c\n"RESET, 188); // Bottom-right corner
}



int select_menu(Options options) {
    int current_option = 0;
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);  
    DWORD mode;
    GetConsoleMode(hInput, &mode);
    SetConsoleMode(hInput, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));

    draw(current_option, options);

    INPUT_RECORD input;
    DWORD events;
    while (1) {
        ReadConsoleInput(hInput, &input, 1, &events);  // Read input from console
        if (input.EventType == KEY_EVENT && input.Event.KeyEvent.bKeyDown) {
            switch (input.Event.KeyEvent.wVirtualKeyCode) {
                case VK_UP:
                    if (current_option > 0) {
                        current_option--;
                        draw(current_option, options);
                    }
                    break;
                case VK_DOWN:
                    if (current_option < options.len-1) {
                        current_option++;
                        draw(current_option, options);
                    }
                    break;
                case VK_RETURN:  
                    return current_option;
            }
        }
    }
}

#endif