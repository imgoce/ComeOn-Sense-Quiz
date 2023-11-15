/* 헤더 선언 */
#include <stdio.h>
#include <windows.h>
#include <stralign.h>
#include <stdlib.h>

/* define 선언 */
#define pause system("pause > nul")
#define cls system("cls")
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4

/* 함수 선언 */
void init();
void titleDraw();
void gotoxy(int, int);
int menuDraw();
int keyControl();

int main() {
    init();
    titleDraw();
    menuDraw();
    int keyCode = keyControl();

    return 0;
}

void init() {
    system("mode con cols=56 lines=20 | title ComeOn Sense Quiz");
}
void titleDraw() {
    printf("\n\n\n\n");
    printf("                    ComeOn Sense Quiz\n");
}
void gotoxy(int x, int y) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(consoleHandle, pos);
}
int menuDraw() {
    int x = 24;
    int y = 12;
    gotoxy(x - 2, y);
    printf("> ID 입력");
    gotoxy(x, y+1);
    printf("ID가 없을 경우");
    gotoxy(x, y+2);
    printf("종료");
    while (1) {
        int n = keyControl();
        switch (n) {
        case UP: {
            if (y > 12) {
                gotoxy(x - 2, y);
                printf(" ");
                gotoxy(x - 2, --y);
                printf(">");
            }
            break;
        }
        case DOWN: {
            if (y < 14) {
                gotoxy(x - 2, y);
                printf(" ");
                gotoxy(x - 2, ++y);
                printf(">");
            }
            break;
        }
        case SUBMIT: {
            return y - 12;
        }
        }
    }
}
int keyControl() {
    char temp = getch();
    if (temp == 'w' || temp == "W") {
        return UP;
    }
    else if (temp == 'a' || temp == "A") {
        return LEFT;
    }
    else if (temp == 's' || temp == "S") {
        return DOWN;
    }
    else if (temp == 'd' || temp == "D") {
        return RIGHT;
    }
    else if (temp == ' ') { //엔터키로 변경
        return SUBMIT;
    }
}