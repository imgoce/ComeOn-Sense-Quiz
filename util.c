/* 헤더 선언 */
#include "main.h"
#include "util.h"

/* 함수 */
void init() {
    system("mode con cols=190 lines=50 | title ComeOn Sense Quiz");

    HWND hwnd = GetConsoleWindow();

    if (hwnd != NULL) {
        ShowWindow(hwnd, SW_MAXIMIZE);
        ShowWindow(hwnd, SW_SHOWMAXIMIZED);
    }

    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConsoleCursor;
    ConsoleCursor.bVisible = 0;
    ConsoleCursor.dwSize = 1;
    SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}
void setcolor(int text, int back) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}
void fullscreen() {
    SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
}
void gotoxy(int x, int y) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(consoleHandle, pos);
}
int keyControl() {
    while (1) {
        char temp = getch();
        if (temp == 'w' || temp == 'W' || temp == 72) {
            return UP;
        }
        else if (temp == 'a' || temp == 'A' || temp == 75) {
            return LEFT;
        }
        else if (temp == 's' || temp == 'S' || temp == 80) {
            return DOWN;
        }
        else if (temp == 'd' || temp == 'D' || temp == 77) {
            return RIGHT;
        }
        else if (temp == '\r' || GetAsyncKeyState(VK_RETURN) & 0x8000) {
            return SUBMIT;
        }
        else if (temp == 'e' || temp == 'E') {
            return EXIT;
        }
        else if (temp == 'r' || temp == 'R') {
            return RETURN;
        }
        else {
            continue;
        }
    }
}
