/* 헤더 선언 */
#include <stdio.h>
#include <windows.h>
#include <stralign.h>
#include <stdlib.h>
#include <string.h>

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
void setcolor(int, int);
void titleDraw();
void gotoxy(int, int);
int menuDraw();
void signup();
int login();
int isUsernameExists(const char* username);
int mainDraw();
int keyControl();

/* 구조체 선언 */
struct Member{
    char username[20];
};

int main() {
    while (1) {
        titleDraw();
        int menuCode = menuDraw();
        if (menuCode == 0) {
            //ID 입력
            int n = mainDraw();

            if (n == 0) {
                //시사
                cls;
                gotoxy(95, 25);
                printf("시사");
                Sleep(1000);
            }
            else if (n == 25) {
                //국가
                cls;
                gotoxy(95, 25);
                printf("국가");
                Sleep(1000);
            }
            else if (n == 50) {
                //인물
                cls;
                gotoxy(95, 25);
                printf("인물");
                Sleep(1000);
            }
            else if (n == 75) {
                //과학
                cls;
                gotoxy(95, 25);
                printf("과학");
                Sleep(1000);
            }
            else if (n == 100) {
                //역사
                cls;
                gotoxy(95, 25);
                printf("역사");
                Sleep(1000);
            }
            else if (n == 125) {
                //영어
                cls;
                gotoxy(95, 25);
                printf("영어");
                Sleep(1000);
            }
        }
        else if (menuCode == 1) {
            //ID가 없을 경우
        }
        else if (menuCode == 2) {
            return 0;
            //종료
        }
        cls;
    }
    int keyCode = keyControl();

    return 0;
}

void init() {
    system("mode con cols=190 lines=50 | title ComeOn Sense Quiz");
}
void setcolor(int text, int back)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}
void titleDraw() {
    printf("\n\n\n\n\n\n");
    setcolor(3, 0);
    printf("                                                                                         ComeOn Sense Quiz\n");
    setcolor(7, 0);
}
void gotoxy(int x, int y) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(consoleHandle, pos);
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
int menuDraw() {
    int x = 90;
    int y = 35;
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
            if (y > 35) {
                gotoxy(x - 2, y);
                printf(" ");
                gotoxy(x - 2, --y);
                printf(">");
            }
            break;
        }
        case DOWN: {
            if (y < 37) {
                gotoxy(x - 2, y);
                printf(" ");
                gotoxy(x - 2, ++y);
                printf(">");
            }
            break;
        }
        case SUBMIT: {
            return y - 35;
        }
        }
    }
}
int mainDraw() {
    int x = 30;
    int y = 35;
    cls;
    printf("\n\n\n");
    printf("                                                                                         ComeOn Sense Quiz\n");

    gotoxy(x - 2, y);
    printf("> 시사");
    gotoxy(x + 25, y);
    printf("국가");
    gotoxy(x + 50, y);
    printf("인물");
    gotoxy(x + 75, y);
    printf("과학");
    gotoxy(x + 100, y);
    printf("역사");
    gotoxy(x + 125, y);
    printf("영어");

    while (1) {
        int n = keyControl();
        switch (n) {
        case RIGHT: {
            if (x > 28 && x < 155) {
                gotoxy(x - 2, y);
                printf(" ");
                x = x + 25;
                gotoxy(x - 2, y);
                printf(">");
            }
            break;
        }
        case LEFT: {
            if (x < 157 && x > 30) {
                gotoxy(x - 2, y);
                printf(" ");
                x = x - 25;
                gotoxy(x - 2, y);
                printf(">");
            }
            break;
        }
        case SUBMIT: {
            return x - 30;
        }
        }
   }
}




/* #define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Member {
    char username[50];
};

void signup();
void login();
int isUsernameExists(const char* username);

int main() {
    int choice;

    do {
        printf("\n1. 회원 가입\n");
        printf("2. 로그인\n");
        printf("3. 종료\n");
        printf("선택: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            signup();
            break;
        case 2:
            login();
            break;
        case 3:
            printf("프로그램을 종료합니다.\n");
            break;
        default:
            printf("올바른 선택이 아닙니다. 다시 선택해주세요.\n");
        }
    } while (choice != 3);

    return 0;
}

void signup() {
    struct Member member;
    FILE* file;

    printf("아이디: ");
    scanf("%s", member.username);

    // 아이디 중복 확인
    if (isUsernameExists(member.username)) {
        printf("이미 존재하는 아이디입니다. 다른 아이디를 선택해주세요.\n");
        return;
    }

    file = fopen("members.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s\n", member.username);
        fclose(file);
        printf("회원 가입이 완료되었습니다.\n");
    }
    else {
        printf("파일을 열 수 없습니다.\n");
    }
}

void login() {
    struct Member member;
    char inputUsername[50];
    FILE* file;

    printf("아이디: ");
    scanf("%s", inputUsername);

    file = fopen("members.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%s", member.username) == 1) {
            if (strcmp(member.username, inputUsername) == 0) {
                fclose(file);
                printf("로그인 성공!\n");
                return;
            }
        }
        fclose(file);
    }

    printf("로그인 실패. 아이디가 올바르지 않습니다.\n");
}

int isUsernameExists(const char* username) {
    FILE* file = fopen("members.txt", "r");
    if (file != NULL) {
        char existingUsername[50];
        while (fscanf(file, "%s", existingUsername) == 1) {
            if (strcmp(existingUsername, username) == 0) {
                fclose(file);
                return 1; // 아이디가 이미 존재함
            }
        }
        fclose(file);
    }
    return 0; // 아이디가 존재하지 않음
}*/

/* 파일에 저장된 문제를 랜덤으로 출력 후 엔터를 누르면 다음 문제로 넘어감
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 100

void shuffleArray(int arr[], int n) {
    // Fisher-Yates shuffle algorithm
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

int main() {
    FILE* file;
    char line[MAX_LINE_LENGTH];
    int* questionOrder;
    int numQuestions = 0;

    // Count the number of questions in the file
    file = fopen("questions.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        numQuestions++;
    }

    fclose(file);

    // Create an array to store the order in which questions will be asked
    questionOrder = (int*)malloc(numQuestions * sizeof(int));
    if (questionOrder == NULL) {
        perror("Error allocating memory");
        return 1;
    }

    for (int i = 0; i < numQuestions; i++) {
        questionOrder[i] = i;
    }

    // Shuffle the array to randomize the order of questions
    srand((unsigned int)time(NULL));
    shuffleArray(questionOrder, numQuestions);

    // Read and print the questions in the randomized order
    file = fopen("questions.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    for (int i = 0; i < numQuestions; i++) {
        int questionIndex = questionOrder[i];

        fseek(file, 0, SEEK_SET);  // Move the file pointer to the beginning

        for (int j = 0; j <= questionIndex; j++) {
            if (fgets(line, MAX_LINE_LENGTH, file) == NULL) {
                perror("Error reading file");
                return 1;
            }
        }

        printf("Question %d: %s\n", i + 1, line);

        // Wait for the user to press Enter before showing the next question
        printf("Press Enter for the next question...\n");
        getchar();
    }

    fclose(file);
    free(questionOrder);

    return 0;
} */