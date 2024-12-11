#ifndef COLORS_H
#define COLORS_H

#include <windows.h>

// Define ANSI color codes
// ANSI Color Codes for UNIX/Linux
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"

// Bright ANSI Colors
#define LIGHT_RED     "\033[91m"
#define LIGHT_GREEN   "\033[92m"
#define LIGHT_YELLOW  "\033[93m"
#define LIGHT_BLUE    "\033[94m"
#define LIGHT_MAGENTA "\033[95m"
#define LIGHT_CYAN    "\033[96m"
#define LIGHT_WHITE   "\033[97m"

// ANSI Styles
#define BOLD        "\033[1m"
#define ITALIC      "\033[3m"
#define RESET       "\033[0m"

// Windows Console Color Codes
#define black           0
#define blue            1
#define green           2
#define cyan            3  
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
// Windows-Style Colors Matching Additional ANSI Colors
#define bright_red        light_red
#define bright_green      light_green
#define bright_yellow     light_yellow
#define bright_cyan       light_aqua
#define bright_blue       light_blue
#define bright_magenta    light_purple


void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}




#endif // COLORS_H
