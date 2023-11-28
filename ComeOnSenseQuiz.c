/* 헤더 선언 */
#include <stdio.h>
#include <windows.h>
#include <stralign.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* define 선언 */
#define pause system("pause > nul")
#define cls system("cls")
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4
#define MAX_LINE_LENGTH 100

/* 함수 선언 */
void init();
void setcolor(int, int);
void titleDraw();
void gotoxy(int, int);
int keyControl();
int menuDraw();
void signup();
struct Member login();
int isUsernameExists(const char* username);
void loadUserInfo(struct Member loginUser);
int mainDraw(struct Member loginUser);
int level();
void shuffleArray(int, int);
int questions(const char* fileName);

/* 구조체 선언 */
struct Member{
    char username[20];
};

int main() {
    init();
    struct Member data;
    while (1) {
        titleDraw();
        int menuCode = menuDraw();
        if (menuCode == 0) {
            //ID 입력
            struct Member loginUser = login();
            Sleep(1000);
            cls;
            if (strcmp(loginUser.username, "") != 0) {
                data = loginUser;
                int n = mainDraw(data);

                if (n == 0) {
                    //시사
                    cls;
                    gotoxy(95, 25);
                    printf("시사");
                    Sleep(1000);
                    int i = level();
                    if (i == 0) {
                        questions();
                    }
                    else if (i == 3) {

                    }
                    else if (i == 6) {

                    }
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
            else {
                continue;
            }
        }
        else if (menuCode == 1) {
            //ID가 없을 경우
            signup();
            Sleep(1000);
            cls;
            continue;
        }
        else if (menuCode == 2) {
            //종료
            return 0;
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
    while (1) {
        char temp = getch();
        if (temp == 'w' || temp == 'W' || GetAsyncKeyState(VK_UP)) {
            return UP;
        }
        else if (temp == 'a' || temp == 'A' || GetAsyncKeyState(VK_LEFT)) {
            return LEFT;
        }
        else if (temp == 's' || temp == 'S' || GetAsyncKeyState(VK_DOWN)) {
            return DOWN;
        }
        else if (temp == 'd' || temp == 'D' || GetAsyncKeyState(VK_RIGHT)) {
            return RIGHT;
        }
        else if (temp == '\r' || GetAsyncKeyState(VK_RETURN) & 0x8000) {
            return SUBMIT;
        }
        else {
            continue;
        }
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
void signup() {
    int x = 90;
    int y = 35;
    gotoxy(x, y);
    printf("                ");
    gotoxy(x, y + 1);
    printf("                ");
    gotoxy(x, y + 2);
    printf("                ");
    gotoxy(x, y+1);
    printf("사용할 아이디 입력 : ");

    struct Member member;
    FILE* file;

    fgets(member.username, sizeof(member.username), stdin);
    member.username[strcspn(member.username, "\n")] = '\0';

    if (strlen(member.username) == 0) {
        gotoxy(x, y + 1);
        printf("사용할 아이디를 입력해주세요.");
        return;
    }

    if (isUsernameExists(member.username)) {
            gotoxy(x, y + 1);
            printf("이미 존재하는 아이디입니다. 다른 아이디를 선택해주세요.");
            return;
        }

    file = fopen("ID.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s\n", member.username);
        fclose(file);
        gotoxy(x, y + 1);
        printf("회원 가입이 완료되었습니다. ID : %s", member.username);
    }
    else {
        gotoxy(x, y + 1);
        printf("아이디를 불러올 수 없습니다.");
    }
}
struct Member login() {
    int x = 90;
    int y = 35;
    struct Member member;
    char inputUsername[20];
    FILE* file;

    gotoxy(x, y);
    printf("                ");
    gotoxy(x, y+1);
    printf("                ");
    gotoxy(x, y+2);
    printf("                ");
    gotoxy(x, y);
    printf("ID : ");
    
    fgets(inputUsername, sizeof(inputUsername), stdin);
    inputUsername[strcspn(inputUsername, "\n")] = '\0';

    if (strlen(inputUsername) == 0) {
        gotoxy(x, y);
        printf("아이디를 입력해주세요.");
        strcpy(member.username, "");
        return member;
    }

    file = fopen("ID.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%s", member.username) == 1) {
            if (strcmp(member.username, inputUsername) == 0) {
                fclose(file);
                gotoxy(x, y);
                printf("로그인 성공");
                return member;
            }
        }
        fclose(file);
    }
    strcpy(member.username, "");
    gotoxy(x, y);
    printf("로그인 실패. 아이디가 존재하지 않거나 올바르지 않습니다.");
    return member;
}
int isUsernameExists(const char* username) {
    FILE* file = fopen("ID.txt", "r");
    if (file != NULL) {
        char existingUsername[20];
        while (fscanf(file, "%s", existingUsername) == 1) {
            if (strcmp(existingUsername, username) == 0) {
                fclose(file);
                return 1; // 아이디 존재
            }
        }
        fclose(file);
    }
    return 0; // 아이디 존재하지 않음
}
void loadUserInfo(struct Member loginUser) {
        gotoxy(10, 10);
        printf("사용자 정보");
        gotoxy(10, 11);
        printf("ID : %s", loginUser.username);
}
int mainDraw(struct Member loginUser) {
    int x = 30;
    int y = 35;
    cls;
    printf("\n\n\n");
    printf("                                                                                         ComeOn Sense Quiz\n");

    loadUserInfo(loginUser);

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
int level() {
    cls;
    int x = 90;
    int y = 20;
    gotoxy(x - 2, y);
    printf("> Easy");
    gotoxy(x, y+3);
    printf("Normal");
    gotoxy(x, y + 6);
    printf("Hard");
    while (1) {
        int n = keyControl();
        switch (n) {
        case UP: {
            if (y > 20) {
                gotoxy(x - 2, y);
                printf(" ");
                y = y - 3;
                gotoxy(x - 2, y);
                printf(">");
            }
            break;
        }
        case DOWN: {
            if (y < 26) {
                gotoxy(x - 2, y);
                printf(" ");
                y = y + 3;
                gotoxy(x - 2, y);
                printf(">");
            }
            break;
        }
        case SUBMIT: {
            return y - 20;
        }
        }
    }
}
void shuffleArray(int arr[], int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}
int questions(const char* fileName) {
    cls;
    FILE* file;
    char line[MAX_LINE_LENGTH];
    int* questionOrder;
    int numQuestions = 0;

    // Count the number of questions in the file
    file = fopen(fileName, "r");
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
    file = fopen(fileName, "r");
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
}