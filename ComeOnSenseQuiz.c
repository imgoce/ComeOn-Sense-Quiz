#define _CRT_SECURE_NO_WARNINGS
/* 헤더 선언 */
#include <stdio.h>
#include <windows.h>
#include <stralign.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

/* define 선언 */
#define pause system("pause > nul")
#define cls system("cls")
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define SUBMIT 4
#define MAX_FILE_NAME_LENGTH 100
#define MAX_LINE_LENGTH 100
#define MAX_QUESTION_LENGTH 256
#define MAX_ANSWER_LENGTH 64
#define MAX_QUESTIONS 100
#define MAX_WRONG_ANSWERS 100
#define MAX_HINT_LENGTH 256
#define MAX_GRADE_LENGTH 2
#define MAX_SECTIONS 6
#define MAX_NUMBERS 400 // 100 questions * 4 numbers

/* 함수 선언 */
void init(); //크기 설정
void setcolor(int, int); //색상 설정
void titleDraw(); //제목 설정
void gotoxy(int, int); //좌표 이동
int keyControl(); //키 조작 설정
int menuDraw(); //초기 화면
void signup(); //회원가입
struct Member login(); //로그인
int isUsernameExists(const char* username); //사용자가 존재하는 지 판단
void loadUserInfo(struct Member loginUser); //사용자 정보
int mainDraw(struct Member loginUser); //메인 화면
int level(); //난이도 선택
void readQuestionAndAnswer(char* questionFilename, char* answerFilename, char questions[][MAX_QUESTION_LENGTH], char answers[][MAX_ANSWER_LENGTH], int* numQuestions); //문제를 파일에서 불러옴
void readNumbers(char* filename, char numbers[][MAX_QUESTION_LENGTH], int* numNumbers); //객관식 문제 읽어옴
void printNumbers(char numbers[][MAX_QUESTION_LENGTH], int start, int end); //객관식 문제 출력
bool checkAnswer(int questionIndex, char userAnswer[MAX_ANSWER_LENGTH], char answers[][MAX_ANSWER_LENGTH]); //정답인지 확인
void saveWrongAnswer(char* filename, char question[MAX_QUESTION_LENGTH], char correctAnswer[MAX_ANSWER_LENGTH], char userAnswer[MAX_ANSWER_LENGTH]); //오답노트 저장
void displayHint(char hints[][MAX_HINT_LENGTH], int currentQuestionIndex); //힌트
struct Result questions(struct Member loginUser, const char* fileName, const char* fileName2, const char* fileName3, const char* username); //OX문제, 주관식 문제
struct Result questions2(struct Member loginUser, const char* fileName, const char* fileName2, const char* fileName3, const char* fileName4, const char* username); //주관식 문제
char* generateWrongAnswersFilename(const char* username); //오답노트 파일 이름 생성
int isAlreadyRecorded(char* filename, char question[MAX_QUESTION_LENGTH]); //오답노트에 이미 존재하는 문제인가?
int CorrectAnswers(); //정답
int WrongAnswers(); //오답
int printResult(struct Result result, struct Member loginUser); //결과 출력

/* 구조체 선언 */
struct Result {
    int correctCount;
    int wrongCount;
    int isError;
    char grade[MAX_GRADE_LENGTH + 1];
};
struct Member {
    char username[20];
    char wrongAnswersFilename[MAX_FILE_NAME_LENGTH];
    int difficulty;
    struct Result quizOptions[MAX_SECTIONS];
};

/* 열거형 선언 */
enum Section {
    SISA,
    GUKGA,
    INMUL,
    GWAHAK,
    YEOKSA,
    YEONGEO
};

int main() {
    init();
    struct Member data;
    const char* fileName = NULL;
    const char* fileName2 = NULL;
    const char* fileName3 = NULL;
    const char* fileName4 = NULL;
    struct Member loginUser;
    int selectedSection;

    while (1) {
        titleDraw();
        int menuCode = menuDraw();
        if (menuCode == 0) {
            //ID 입력
            loginUser = login();
            Sleep(1000);
            cls;
            while (1) {
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
                        loginUser.difficulty = i / 3;
                        if (i == 0) {
                            fileName = "current_easy.txt";
                            fileName2 = "current_easy_answers.txt";
                            fileName3 = "current_easy_hint";
                            selectedSection = SISA;
                        }
                        else if (i == 3) {
                            fileName = "current_normal.txt";
                            fileName2 = "current_normal_answers.txt";
                            fileName3 = "current_normal_hint.txt";
                            fileName4 = "current_normal_number.txt";
                            selectedSection = SISA;
                        }
                        else if (i == 6) {
                            fileName = "current_hard.txt";
                            fileName2 = "current_hard_answers.txt";
                            fileName3 = "current_hard_hint.txt";
                            selectedSection = SISA;
                        }
                    }
                    else if (n == 25) {
                        //국가
                        cls;
                        gotoxy(95, 25);
                        printf("국가");
                        Sleep(1000);
                        int i = level();
                        if (i == 0) {
                            fileName = "Country Easy Level.txt";
                        }
                        else if (i == 3) {
                            fileName = "Country Normal Level.txt";
                        }
                        else if (i == 6) {
                            fileName = "Country Hard Level.txt";
                        }
                    }
                    else if (n == 50) {
                        //인물
                        cls;
                        gotoxy(95, 25);
                        printf("인물");
                        Sleep(1000);
                        int i = level();
                        if (i == 0) {
                            fileName = "character_easy.txt";
                            fileName2 = "character_easy_answer.txt";
                            fileName3 = "character_easy_hint.txt";
                            selectedSection = INMUL;

                            struct Result result = questions(loginUser, fileName, fileName2, fileName3, data.username);
                            if (result.isError) {
                                gotoxy(80, 25);
                                printf("Error executing questions function.\n");
                                return 1;
                            }
                            int r = printResult(result, loginUser, selectedSection);
                            cls;
                        }
                        else if (i == 3) {
                            fileName = "character_normal.txt";
                            fileName2 = "character_normal_answer.txt";
                            fileName3 = "character_normal_hint.txt";
                            fileName4 = "character_normal_number.txt";
                            selectedSection = INMUL;

                            struct Result result = questions2(loginUser, fileName, fileName2, fileName3, fileName4, data.username);
                            if (result.isError) {
                                gotoxy(80, 25);
                                printf("Error executing questions function.\n");
                                return 1;
                            }
                            int r = printResult(result, loginUser, selectedSection);
                            cls;
                        }
                        else if (i == 6) {
                            fileName = "Person Hard Level.txt";
                        }
                    }
                    else if (n == 75) {
                        //과학
                        cls;
                        gotoxy(95, 25);
                        printf("과학");
                        Sleep(1000);
                        int i = level();
                        if (i == 0) {
                            fileName = "Science Easy Level.txt";
                        }
                        else if (i == 3) {
                            fileName = "Science Normal Level.txt";
                        }
                        else if (i == 6) {
                            fileName = "Science Hard Level.txt";
                        }
                    }
                    else if (n == 100) {
                        //역사
                        cls;
                        gotoxy(95, 25);
                        printf("역사");
                        Sleep(1000);
                        int i = level();
                        if (i == 0) {
                            fileName = "History Easy Level.txt";
                        }
                        else if (i == 3) {
                            fileName = "History Normal Level.txt";
                        }
                        else if (i == 6) {
                            fileName = "History Hard Level.txt";
                        }
                    }
                    else if (n == 125) {
                        //영어
                        cls;
                        gotoxy(95, 25);
                        printf("영어");
                        Sleep(1000);
                        int i = level();
                        if (i == 0) {
                            fileName = "English Easy Level.txt";
                        }
                        else if (i == 3) {
                            fileName = "English Normal Level.txt";
                        }
                        else if (i == 6) {
                            fileName = "English Hard Level.txt";
                        }
                    }
                }
                else {
                    continue;
                }
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
void setcolor(int text, int back) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text | (back << 4));
}
void titleDraw() {
    printf("\n\n\n\n");
    setcolor(3, 0);
<<<<<<< HEAD
    gotoxy(50, 4);
=======

>>>>>>> dd655b457e76608b888b0b669c9d24564fad334f
    printf("     ____       _____       ____              _____                               	\n");
    gotoxy(50, 5);
    printf("    /\\  _`\\    /\\  __`\\    /\\  _`\\           /\\  __`\\              __             	\n");
    gotoxy(50, 6);
    printf("    \\ \\ \\/\\_\\  \\ \\ \\/\\ \\   \\ \\,\\L\\_\\         \\ \\ \\/\\ \\    __  __  /\\_\\    ____    	\n");
    gotoxy(50, 7);
    printf("     \\ \\ \\/_/_  \\ \\ \\ \\ \\   \\/_\\__ \\          \\ \\ \\ \\ \\  /\\ \\/\\ \\ \\/\\ \\  /\\_ ,`\\  	\n");
    gotoxy(50, 8);
    printf("      \\ \\ \\L\\ \\  \\ \\ \\_\\ \\    /\\ \\L\\ \\         \\ \\ \\\\'\\\\ \\ \\ \\_\\ \\ \\ \\ \\ \\/_/  /_ 	\n");
    gotoxy(50, 9);
    printf("       \\ \\____/   \\ \\_____\\   \\ `\\____\\         \\ \\___\\_\\ \\ \\____/  \\ \\_\\  /\\____\\	\n");
    gotoxy(50, 10);
    printf("        \\/___/     \\/_____/    \\/_____/          \\/__//_/  \\/___/    \\/_/  \\/____/	\n");

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
    int x = 35;
    int y = 15;
    gotoxy(x - 2, y);

    setcolor(3, 0);
    printf("★ ");
    gotoxy(x, y);
    setcolor(7, 0);

    printf("ID 입력");
    gotoxy(x, y + 1);
    printf("ID가 없을 경우");
    gotoxy(x, y + 2);
    printf("종료");
    while (1) {
        int n = keyControl();
        switch (n) {
        case UP: {
            if (y > 15) {
                gotoxy(x - 2, y);
                printf(" ");
                gotoxy(x - 2, --y);

                setcolor(3, 0);
                printf("★");
                setcolor(7, 0);

            }
            break;
        }
        case DOWN: {
            if (y < 17) {
                gotoxy(x - 2, y);
                printf(" ");
                gotoxy(x - 2, ++y);

                setcolor(3, 0);
                printf("★");
                setcolor(7, 0);

            }
            break;
        }
        case SUBMIT: {
            return y - 15;
        }
        }
    }
}
void signup() {
    int x = 35;
    int y = 15;
    gotoxy(x, y);
    printf("                ");
    gotoxy(x, y + 1);
    printf("                ");
    gotoxy(x, y + 2);
    printf("                ");
    gotoxy(x, y + 1);
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
    int x = 35;
    int y = 15;
    struct Member member;
    char inputUsername[20];
    FILE* file;

    gotoxy(x, y);
    printf("                ");
    gotoxy(x, y + 1);
    printf("                ");
    gotoxy(x, y + 2);
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
                strcpy(member.wrongAnswersFilename, generateWrongAnswersFilename(inputUsername));
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
    gotoxy(10, 12);
    printf("시사(Easy) : %c(정답 : %d, 오답 : %d)", loginUser.quizOptions[SISA].grade, loginUser.quizOptions[SISA].correctCount, loginUser.quizOptions[SISA].wrongCount);
    gotoxy(10, 13);
    printf("시사(Normal) : ");
    gotoxy(10, 14);
    printf("시사(Hard) : ");
    gotoxy(10, 15);
    printf("국가(Easy) : ");
    gotoxy(10, 16);
    printf("국가(Normal) : ");
    gotoxy(10, 17);
    printf("국가(Hard) : ");
    gotoxy(10, 18);
    printf("인물(Easy) : ");
    gotoxy(10, 19);
    printf("인물(Normal) : ");
    gotoxy(10, 20);
    printf("인물(Hard) : ");
    gotoxy(10, 21);
    printf("과학(Easy) : ");
    gotoxy(10, 22);
    printf("과학(Normal) : ");
    gotoxy(10, 23);
    printf("과학(Hard) : ");
    gotoxy(10, 24);
    printf("역사(Easy) : ");
    gotoxy(10, 25);
    printf("역사(Normal) : ");
    gotoxy(10, 26);
    printf("역사(Hard) : ");
    gotoxy(10, 27);
    printf("영어(Easy) : ");
    gotoxy(10, 28);
    printf("영어(Normal) : ");
    gotoxy(10, 29);
    printf("영어(Hard) : ");
}
int mainDraw(struct Member loginUser) {
    int x = 30;
    int y = 35;
    cls;
    printf("\n\n\n\n");
    setcolor(3, 0);

    printf("     ____       _____       ____              _____                               	\n");
    printf("    /\\  _`\\    /\\  __`\\    /\\  _`\\           /\\  __`\\              __             	\n");
    printf("    \\ \\ \\/\\_\\  \\ \\ \\/\\ \\   \\ \\,\\L\\_\\         \\ \\ \\/\\ \\    __  __  /\\_\\    ____    	\n");
    printf("     \\ \\ \\/_/_  \\ \\ \\ \\ \\   \\/_\\__ \\          \\ \\ \\ \\ \\  /\\ \\/\\ \\ \\/\\ \\  /\\_ ,`\\  	\n");
    printf("      \\ \\ \\L\\ \\  \\ \\ \\_\\ \\    /\\ \\L\\ \\         \\ \\ \\\\'\\\\ \\ \\ \\_\\ \\ \\ \\ \\ \\/_/  /_ 	\n");
    printf("       \\ \\____/   \\ \\_____\\   \\ `\\____\\         \\ \\___\\_\\ \\ \\____/  \\ \\_\\  /\\____\\	\n");
    printf("        \\/___/     \\/_____/    \\/_____/          \\/__//_/  \\/___/    \\/_/  \\/____/	\n");

    setcolor(7, 0);
    loadUserInfo(loginUser);

    gotoxy(90, 10);
    printf("오답 노트");

    gotoxy(150, 10);
    printf("리더 보드");

    gotoxy(x - 2, y);

    setcolor(3, 0);
    printf("★ ");
    gotoxy(x, y);
    setcolor(7, 0);

    printf("시사");
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

                setcolor(3, 0);
                printf("★");
                setcolor(7, 0);
            }
            break;
        }
        case LEFT: {
            if (x < 157 && x > 30) {
                gotoxy(x - 2, y);
                printf(" ");
                x = x - 25;
                gotoxy(x - 2, y);

                setcolor(3, 0);
                printf("★");
                setcolor(7, 0);

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

    setcolor(3, 0);
    printf("★ ");
    gotoxy(x, y);
    setcolor(7, 0);

    printf("Easy");
    gotoxy(x, y + 3);
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

                setcolor(3, 0);
                printf("★");
                setcolor(7, 0);


            }
            break;
        }
        case DOWN: {
            if (y < 26) {
                gotoxy(x - 2, y);
                printf(" ");
                y = y + 3;
                gotoxy(x - 2, y);

                setcolor(3, 0);
                printf("★");
                setcolor(7, 0);

            }
            break;
        }
        case SUBMIT: {
            return y - 20;
        }
        }
    }
}
struct Result questions(struct Member loginUser, const char* fileName, const char* fileName2, const char* fileName3, const char* username) {
    cls;
    struct Result result = { 0 };
    char questionFilename[MAX_FILE_NAME_LENGTH];
    char answerFilename[MAX_FILE_NAME_LENGTH];
    char hintFilename[MAX_FILE_NAME_LENGTH];
    strcpy(questionFilename, fileName);
    strcpy(answerFilename, fileName2);
    strcpy(hintFilename, fileName3);
    struct Member loggedInUser;
    loggedInUser = loginUser;
    char* wrongAnswersFilename = generateWrongAnswersFilename(loggedInUser.username);

    char formattedWrongAnswersFilename[MAX_FILE_NAME_LENGTH];
    snprintf(formattedWrongAnswersFilename, MAX_FILE_NAME_LENGTH, "%s_wrong_answers.txt", username);

    char questions[MAX_QUESTIONS][MAX_QUESTION_LENGTH];
    char answers[MAX_QUESTIONS][MAX_ANSWER_LENGTH];
    char hints[MAX_QUESTIONS][MAX_HINT_LENGTH];
    int numQuestions = 0;

    while (1) {
        readQuestionAndAnswer(questionFilename, answerFilename, questions, answers, &numQuestions);

        if (numQuestions == 0) {
            gotoxy(80, 25);
            printf("문제 파일 또는 정답 파일을 읽을 수 없습니다.\n");
            result.isError = 1;
            return result;
        }

        srand(time(NULL));

        char userAnswer[MAX_ANSWER_LENGTH];
        char exitInput[MAX_ANSWER_LENGTH] = "q";
        char HintInput[MAX_ANSWER_LENGTH] = "h";

        int* questionOrder = (int*)malloc(numQuestions * sizeof(int));
        if (questionOrder == NULL) {
            gotoxy(80, 25);
            printf("메모리 할당 오류\n");
            result.isError = 1;
            return result;
        }

        for (int i = 0; i < numQuestions; i++) {
            questionOrder[i] = i;
        }

        FILE* wrongAnswersFile = fopen(wrongAnswersFilename, "a");
        if (wrongAnswersFile == NULL) {
            gotoxy(80, 25);
            printf("오답 노트 파일을 열 수 없습니다.\n");
            result.isError = 1;
            return result;
        }

        for (int i = 0; i < numQuestions; i++) {
            int randomIndex = i + rand() % (numQuestions - i);

            int temp = questionOrder[i];
            questionOrder[i] = questionOrder[randomIndex];
            questionOrder[randomIndex] = temp;

            int currentQuestionIndex = questionOrder[i];

            gotoxy(175, 5);
            printf("Hint (h 입력)");

            gotoxy(50, 15);
            printf("문제: %s\n", questions[currentQuestionIndex]);

            while (1) {
                gotoxy(80, 35);
                printf("답 (종료하려면 'q' 입력): ");
                scanf("%s", userAnswer);

                if (strcmp(userAnswer, exitInput) == 0) {
                    gotoxy(80, 36);
                    printf("프로그램을 종료합니다.\n");
                    Sleep(1000);
                    cls;
                    return result;
                }
                else {
                    if (checkAnswer(currentQuestionIndex, userAnswer, answers)) {
                        int a = CorrectAnswers();
                        result.correctCount++;
                        if (a == 3) {
                            cls;
                            return result;
                        }
                        Sleep(1000);
                        cls;
                        break;
                    }
                    else {
                        if (!isAlreadyRecorded(wrongAnswersFilename, questions[currentQuestionIndex])) {
                            int a = WrongAnswers();
                            result.wrongCount++;
                            if (a == 3) {
                                cls;
                                return result;
                            }
                            saveWrongAnswer(wrongAnswersFilename, questions[currentQuestionIndex], answers[currentQuestionIndex], userAnswer);
                            Sleep(1000);
                            cls;
                        }
                        else {
                            int a = WrongAnswers();
                            result.wrongCount++;
                            if (a == 3) {
                                cls;
                                return result;
                            }
                            Sleep(1000);
                            cls;
                        }
                        break;
                    }
                }
            }

            while (getchar() != '\n');
        }
        fclose(wrongAnswersFile);
        free(questionOrder);
        break;
    }

    free(wrongAnswersFilename);
    return result;
}
struct Result questions2(struct Member loginUser, const char* fileName, const char* fileName2, const char* fileName3, const char* fileName4, const char* username) {
    cls;
    struct Result result = { 0 };
    char questionFilename[MAX_FILE_NAME_LENGTH];
    char answerFilename[MAX_FILE_NAME_LENGTH];
    char hintFilename[MAX_FILE_NAME_LENGTH];
    char numberFilename[MAX_FILE_NAME_LENGTH];
    strcpy(questionFilename, fileName);
    strcpy(answerFilename, fileName2);
    strcpy(hintFilename, fileName3);
    strcpy(numberFilename, fileName4);
    struct Member loggedInUser;
    loggedInUser = loginUser;
    char* wrongAnswersFilename = generateWrongAnswersFilename(loggedInUser.username);

    char formattedWrongAnswersFilename[MAX_FILE_NAME_LENGTH];
    snprintf(formattedWrongAnswersFilename, MAX_FILE_NAME_LENGTH, "%s_wrong_answers.txt", username);

    char questions[MAX_QUESTIONS][MAX_QUESTION_LENGTH];
    char answers[MAX_QUESTIONS][MAX_ANSWER_LENGTH];
    char hints[MAX_QUESTIONS][MAX_HINT_LENGTH];
    char numbers[MAX_NUMBERS][MAX_QUESTION_LENGTH];
    int numQuestions = 0;
    int numNumbers = 0;

    while (1) {
        readQuestionAndAnswer(questionFilename, answerFilename, questions, answers, &numQuestions);
        readNumbers(numberFilename, numbers, &numNumbers);

        if (numQuestions == 0 || numNumbers == 0) {
            gotoxy(80, 25);
            printf("문제 파일 또는 정답 파일을 읽을 수 없습니다.\n");
            result.isError = 1;
            return result;
        }

        srand(time(NULL));

        char userAnswer[MAX_ANSWER_LENGTH];
        char exitInput[MAX_ANSWER_LENGTH] = "q";
        char HintInput[MAX_ANSWER_LENGTH] = "h";

        int* questionOrder = (int*)malloc(numQuestions * sizeof(int));
        if (questionOrder == NULL) {
            gotoxy(80, 25);
            printf("메모리 할당 오류\n");
            result.isError = 1;
            return result;
        }

        for (int i = 0; i < numQuestions; i++) {
            questionOrder[i] = i;
        }

        FILE* wrongAnswersFile = fopen(wrongAnswersFilename, "a");
        if (wrongAnswersFile == NULL) {
            gotoxy(80, 25);
            printf("오답 노트 파일을 열 수 없습니다.\n");
            result.isError = 1;
            return result;
        }

        for (int i = 0; i < numQuestions; i++) {
            questionOrder[i] = i;
        }

        for (int i = 0; i < numQuestions; i++) {
            int randomIndex = i + rand() % (numQuestions - i);

            int temp = questionOrder[i];
            questionOrder[i] = questionOrder[randomIndex];
            questionOrder[randomIndex] = temp;

            int currentQuestionIndex = questionOrder[i];

            gotoxy(175, 5);
            printf("Hint (h 입력)");

            gotoxy(50, 15);
            printf("문제: %s\n", questions[currentQuestionIndex]);

            int start = 0;
            int end = 0;

            if (currentQuestionIndex == 0) {
                start = 0;
                end = 4;
            }
            else if (currentQuestionIndex == 1) {
                start = 4;
                end = 8;
            }
            else if (currentQuestionIndex == 2) {
                start = 8;
                end = 12;
            }
            else if (currentQuestionIndex == 3) {
                start = 12;
                end = 16;
            }
            else if (currentQuestionIndex == 4) {
                start = 16;
                end = 20;
            }
            else if (currentQuestionIndex == 5) {
                start = 20;
                end = 24;
            }
            else if (currentQuestionIndex == 6) {
                start = 24;
                end = 28;
            }
            else if (currentQuestionIndex == 7) {
                start = 28;
                end = 32;
            }
            else if (currentQuestionIndex == 8) {
                start = 32;
                end = 36;
            }
            else if (currentQuestionIndex == 9) {
                start = 36;
                end = 40;
            }
            else if (currentQuestionIndex == 10) {
                start = 40;
                end = 44;
            }

            printNumbers(numbers, start, end);

            while (1) {
                gotoxy(80, 35);
                printf("답 (종료하려면 'q' 입력): ");
                scanf("%s", userAnswer);

                if (strcmp(userAnswer, exitInput) == 0) {
                    gotoxy(80, 36);
                    printf("문제 종료\n");
                    Sleep(1000);
                    cls;
                    return result;
                }
                else {
                    if (checkAnswer(currentQuestionIndex, userAnswer, answers)) {
                        int a = CorrectAnswers();
                        result.correctCount++;
                        if (a == 3) {
                            cls;
                            return result;
                        }
                        Sleep(1000);
                        cls;
                        break;
                    }
                    else {
                        if (!isAlreadyRecorded(wrongAnswersFilename, questions[currentQuestionIndex])) {
                            int a = WrongAnswers();
                            result.wrongCount++;
                            if (a == 3) {
                                cls;
                                return result;
                            }
                            saveWrongAnswer(wrongAnswersFilename, questions[currentQuestionIndex], answers[currentQuestionIndex], userAnswer);
                            Sleep(1000);
                            cls;
                        }
                        else {
                            int a = WrongAnswers();
                            result.wrongCount++;
                            if (a == 3) {
                                cls;
                                return result;
                            }
                            Sleep(1000);
                            cls;
                        }
                        break;
                    }
                }
            }

            while (getchar() != '\n');
        }
        fclose(wrongAnswersFile);
        free(questionOrder);
        break;
    }

    free(wrongAnswersFilename);
    return result;
}
void readQuestionAndAnswer(char* questionFilename, char* answerFilename, char questions[][MAX_QUESTION_LENGTH], char answers[][MAX_ANSWER_LENGTH], int* numQuestions) {
    FILE* questionFile = fopen(questionFilename, "r");
    FILE* answerFile = fopen(answerFilename, "r");

    if (questionFile == NULL || answerFile == NULL) {
        *numQuestions = 0;
        return;
    }

    *numQuestions = 0;
    while (fgets(questions[*numQuestions], MAX_QUESTION_LENGTH, questionFile) != NULL &&
        fgets(answers[*numQuestions], MAX_ANSWER_LENGTH, answerFile) != NULL) {
        questions[*numQuestions][strcspn(questions[*numQuestions], "\n")] = 0;
        answers[*numQuestions][strcspn(answers[*numQuestions], "\n")] = 0;

        (*numQuestions)++;
    }

    fclose(questionFile);
    fclose(answerFile);
}
void readNumbers(char* filename, char numbers[][MAX_QUESTION_LENGTH], int* numNumbers) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        *numNumbers = 0;
        return;
    }

    *numNumbers = 0;
    while (*numNumbers < MAX_NUMBERS && fgets(numbers[*numNumbers], MAX_QUESTION_LENGTH, file) != NULL) {
        numbers[*numNumbers][strcspn(numbers[*numNumbers], "\n")] = 0;
        (*numNumbers)++;
    }

    fclose(file);
}
void printNumbers(char numbers[][MAX_QUESTION_LENGTH], int start, int end) {
    int j = 0;
    for (int i = start; i < end; i++) {
        gotoxy(60, 17 + j);
        printf("%s\n", numbers[i]);
        j++;
    }
}
bool checkAnswer(int questionIndex, char userAnswer[MAX_ANSWER_LENGTH], char answers[][MAX_ANSWER_LENGTH]) {
    return strcmp(userAnswer, answers[questionIndex]) == 0;
}
char* generateWrongAnswersFilename(const char* username) {
    char* filename = (char*)malloc(MAX_FILE_NAME_LENGTH * sizeof(char));
    if (filename == NULL) {
        printf("메모리 할당 오류\n");
        return NULL;
    }
    snprintf(filename, MAX_FILE_NAME_LENGTH, "%s_wrong_answers.txt", username);

    return filename;
}
void saveWrongAnswer(char* filename, char question[MAX_QUESTION_LENGTH], char correctAnswer[MAX_ANSWER_LENGTH], char userAnswer[MAX_ANSWER_LENGTH]) {
    FILE* file = fopen(filename, "r");
    int alreadySaved = 0;

    if (file != NULL) {
        char allLines[MAX_QUESTIONS][MAX_QUESTION_LENGTH + MAX_ANSWER_LENGTH + MAX_ANSWER_LENGTH + 30]; // 모든 줄을 저장할 배열
        int numLines = 0;

        char line[MAX_QUESTION_LENGTH + MAX_ANSWER_LENGTH + MAX_ANSWER_LENGTH + 30];
        while (fgets(line, sizeof(line), file)) {
            strcpy(allLines[numLines], line);
            numLines++;
            for (int i = 0; i < 3; i++) {
                fgets(line, sizeof(line), file);
            }
        }

        fclose(file);

        char correctAns[MAX_ANSWER_LENGTH];
        snprintf(correctAns, MAX_ANSWER_LENGTH, "정답: %s", correctAnswer);

        for (int i = 0; i < numLines; i += 4) {
            if (strstr(allLines[i], question) != NULL &&
                strstr(allLines[i + 1], correctAns) != NULL &&
                strstr(allLines[i + 2], userAnswer) != NULL) {
                alreadySaved = 1;
                break;
            }
        }

        if (alreadySaved) {
            return;
        }
        else {
            file = fopen(filename, "a");
            if (file != NULL) {
                fprintf(file, "문제: %s\n", question);
                fprintf(file, "정답: %s\n", correctAnswer);
                fprintf(file, "오답: %s\n", userAnswer);
                fprintf(file, "------------------------\n");

                fclose(file);
            }
            else {
                printf("오답 노트 파일에 기록할 수 없습니다.\n");
            }
        }
    }
    else {
        printf("파일을 열 수 없습니다.\n");
    }
}
int CorrectAnswers() {
    cls;
    gotoxy(80, 10);
    puts("@@@@@,,,....,,,@@@@@");
    gotoxy(80, 11);
    puts("@@@@............@@@@");
    gotoxy(80, 12);
    puts("@@@..............@@@");
    gotoxy(80, 13);
    puts("@@......,,,,......@@");
    gotoxy(80, 14);
    puts("@.....@@@@@@@@.....@");
    gotoxy(80, 15);
    puts(",....@@@@@@@@@@....,");
    gotoxy(80, 16);
    puts(",...@@@@@@@@@@@@...,");
    gotoxy(80, 17);
    puts(",...@@@@@@@@@@@@...,");
    gotoxy(80, 18);
    puts("...,@@@@@@@@@@@@,...");
    gotoxy(80, 19);
    puts("...,@@@@@@@@@@@@,...");
    gotoxy(80, 20);
    puts("...,@@@@@@@@@@@@,...");
    gotoxy(80, 21);
    puts("...,@@@@@@@@@@@@,...");
    gotoxy(80, 22);
    puts(",...@@@@@@@@@@@@...,");
    gotoxy(80, 23);
    puts(",...@@@@@@@@@@@@...,");
    gotoxy(80, 24);
    puts(",....@@@@@@@@@@....,");
    gotoxy(80, 25);
    puts("@.....@@@@@@@@.....@");
    gotoxy(80, 26);
    puts("@@......,,,,......@@");
    gotoxy(80, 27);
    puts("@@@..............@@@");
    gotoxy(80, 28);
    puts("@@@@............@@@@");
    gotoxy(80, 29);
    puts("@@@@@,,,....,,,@@@@@");

    int x = 10;
    int y = 45;
    setcolor(3, 0);
    gotoxy(x - 2, y);
    printf("> ");
    setcolor(7, 0);
    printf("EXIT");
    gotoxy(180, y);
    printf("->");
    while (1) {
        int n = keyControl();
        switch (n) {
        case RIGHT: {
            if (x > 8 && x < 180) {
                gotoxy(x - 2, y);
                printf(" ");
                x = x + 170;
                gotoxy(x - 2, y);
                setcolor(3, 0);
                printf(">");
                setcolor(7, 0);
            }
            break;
        }
        case LEFT: {
            if (x < 182 && x > 10) {
                gotoxy(x - 2, y);
                printf(" ");
                x = x - 170;
                gotoxy(x - 2, y);
                setcolor(3, 0);
                printf(">");
                setcolor(7, 0);
            }
            break;
        }
        case SUBMIT: {
            return x - 7;
        }
        }
    }
}
int WrongAnswers() {
    cls;
    gotoxy(80, 10);
    puts("@@@@@@@@@@@@@@@@@@@@");
    gotoxy(80, 11);
    puts("@@@@@@@@@@@@@@@@@@@@");
    gotoxy(80, 12);
    puts("@     @@@@@@@@     @");
    gotoxy(80, 13);
    puts("@      @@@@@@      @");
    gotoxy(80, 14);
    puts("@       @@@@       @");
    gotoxy(80, 15);
    puts("@@       @@       @@");
    gotoxy(80, 16);
    puts("@@@              @@@");
    gotoxy(80, 17);
    puts("@@@@            @@@@");
    gotoxy(80, 18);
    puts("@@@@@          @@@@@");
    gotoxy(80, 19);
    puts("@@@@@@        @@@@@@");
    gotoxy(80, 20);
    puts("@@@@@@        @@@@@@");
    gotoxy(80, 21);
    puts("@@@@@          @@@@@");
    gotoxy(80, 22);
    puts("@@@@            @@@@");
    gotoxy(80, 23);
    puts("@@@              @@@");
    gotoxy(80, 24);
    puts("@@       @@       @@");
    gotoxy(80, 25);
    puts("@       @@@@       @");
    gotoxy(80, 26);
    puts("@      @@@@@@      @");
    gotoxy(80, 27);
    puts("@     @@@@@@@@     @");
    gotoxy(80, 28);
    puts("@    @@@@@@@@@@    @");
    gotoxy(80, 29);
    puts("@@@@@@@@@@@@@@@@@@@@");
    gotoxy(80, 30);

    int x = 10;
    int y = 45;
    setcolor(3, 0);
    gotoxy(x - 2, y);
    printf("> ");
    setcolor(7, 0);
    printf("EXIT");
    gotoxy(180, y);
    printf("->");
    while (1) {
        int n = keyControl();
        switch (n) {
        case RIGHT: {
            if (x > 8 && x < 180) {
                gotoxy(x - 2, y);
                printf(" ");
                x = x + 170;
                gotoxy(x - 2, y);
                setcolor(3, 0);
                printf(">");
                setcolor(7, 0);
            }
            break;
        }
        case LEFT: {
            if (x < 182 && x > 10) {
                gotoxy(x - 2, y);
                printf(" ");
                x = x - 170;
                gotoxy(x - 2, y);
                setcolor(3, 0);
                printf(">");
                setcolor(7, 0);
            }
            break;
        }
        case SUBMIT: {
            return x - 7;
        }
        }
    }
}
int printResult(struct Result result, struct Member loginUser) {
    float totalQuestions = result.correctCount + result.wrongCount;
    float wrongPercentage = (result.wrongCount / totalQuestions) * 100;

    gotoxy(90, 10);
    if (result.correctCount == totalQuestions) {
        printf("등급: S\n");
        strncpy(result.grade, "S", MAX_GRADE_LENGTH);
        result.grade[MAX_GRADE_LENGTH] = '\0';
    }
    else if (wrongPercentage <= 20) {
        printf("등급: A\n");
        strncpy(result.grade, "A", MAX_GRADE_LENGTH);
        result.grade[MAX_GRADE_LENGTH] = '\0';
    }
    else if (wrongPercentage <= 40) {
        printf("등급: B\n");
        strncpy(result.grade, "B", MAX_GRADE_LENGTH);
        result.grade[MAX_GRADE_LENGTH] = '\0';
    }
    else if (wrongPercentage <= 60) {
        printf("등급: C\n");
        strncpy(result.grade, "C", MAX_GRADE_LENGTH);
        result.grade[MAX_GRADE_LENGTH] = '\0';
    }
    else if (wrongPercentage <= 80) {
        printf("등급: D\n");
        strncpy(result.grade, "D", MAX_GRADE_LENGTH);
        result.grade[MAX_GRADE_LENGTH] = '\0';
    }
    else {
        printf("등급: E\n");
        strncpy(result.grade, "E", MAX_GRADE_LENGTH);
        result.grade[MAX_GRADE_LENGTH] = '\0';
    }

    int x = 10;
    int y = 45;
    gotoxy(88, 30);
    printf("정답 수: %d\n", result.correctCount);
    gotoxy(88, 31);
    printf("오답 수: %d\n", result.wrongCount);
    gotoxy(x - 2, y);

    setcolor(3, 0);
    printf("★ ");
    gotoxy(x, y);
    setcolor(7, 0);


    printf("오답노트");
    gotoxy(180, y);
    printf("->");
    while (1) {
        int n = keyControl();
        switch (n) {
        case RIGHT: {
            if (x > 8 && x < 180) {
                gotoxy(x - 2, y);
                printf(" ");
                x = x + 170;
                gotoxy(x - 2, y);

                setcolor(3, 0);
                printf("★");
                setcolor(7, 0);

            }
            break;
        }
        case LEFT: {
            if (x < 182 && x > 10) {
                gotoxy(x - 2, y);
                printf(" ");
                x = x - 170;
                gotoxy(x - 2, y);

                setcolor(3, 0);
                printf("★");
                setcolor(7, 0);
            }
            break;
        }
        case SUBMIT: {
            return x - 7;
        }
        }
    }
}

/* 힌트(h키) 기능 추가 후 전체 코드
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_QUESTION_LENGTH 256
#define MAX_ANSWER_LENGTH 64
#define MAX_HINT_LENGTH 256
#define MAX_QUESTIONS 100

void readQuestionAndAnswer(char* questionFilename, char* answerFilename, char* hintFilename, char questions[][MAX_QUESTION_LENGTH], char answers[][MAX_ANSWER_LENGTH], char hints[][MAX_HINT_LENGTH], int* numQuestions);
int checkAnswer(int questionIndex, char userAnswer[MAX_ANSWER_LENGTH], char answers[][MAX_ANSWER_LENGTH]);
void saveWrongAnswer(char* filename, char question[MAX_QUESTION_LENGTH], char correctAnswer[MAX_ANSWER_LENGTH], char userAnswer[MAX_ANSWER_LENGTH]);
void displayHint(char hints[][MAX_HINT_LENGTH], int currentQuestionIndex);

int main() {
    char questionFilename[] = "question.txt";
    char answerFilename[] = "answer.txt";
    char hintFilename[] = "hint.txt";
    char wrongAnswersFilename[] = "wrong_answers.txt";

    char questions[MAX_QUESTIONS][MAX_QUESTION_LENGTH];
    char answers[MAX_QUESTIONS][MAX_ANSWER_LENGTH];
    char hints[MAX_QUESTIONS][MAX_HINT_LENGTH];
    int numQuestions = 0;

    readQuestionAndAnswer(questionFilename, answerFilename, hintFilename, questions, answers, hints, &numQuestions);

    if (numQuestions == 0) {
        printf("문제 파일, 정답 파일 또는 힌트 파일을 읽을 수 없습니다.\n");
        return 1;
    }

    srand(time(NULL));

    char userAnswer[MAX_ANSWER_LENGTH];
    char exitInput[MAX_ANSWER_LENGTH] = "q";
    char hintInput[MAX_ANSWER_LENGTH] = "h";

    int* questionOrder = (int*)malloc(numQuestions * sizeof(int));
    if (questionOrder == NULL) {
        printf("메모리 할당 오류\n");
        return 1;
    }

    for (int i = 0; i < numQuestions; i++) {
        questionOrder[i] = i;
    }

    FILE* wrongAnswersFile = fopen(wrongAnswersFilename, "a");
    if (wrongAnswersFile == NULL) {
        printf("오답 노트 파일을 열 수 없습니다.\n");
        return 1;
    }

    for (int i = 0; i < numQuestions; i++) {
        int randomIndex = i + rand() % (numQuestions - i);
        int temp = questionOrder[i];
        questionOrder[i] = questionOrder[randomIndex];
        questionOrder[randomIndex] = temp;

        int currentQuestionIndex = questionOrder[i];

        printf("문제: %s\n", questions[currentQuestionIndex]);

        while (1) {
            printf("답을 입력하세요 (종료하려면 'q' 입력, 힌트 보려면 'h' 입력): ");
            scanf("%s", userAnswer);

            if (strcmp(userAnswer, exitInput) == 0) {
                printf("프로그램을 종료합니다.\n");
                break;
            }
            else if (strcmp(userAnswer, hintInput) == 0) {
                displayHint(hints, currentQuestionIndex);
            }
            else {
                if (checkAnswer(currentQuestionIndex, userAnswer, answers)) {
                    printf("정답!\n");
                    break;
                }
                else {
                    printf("오답! 정답은 %s 입니다.\n", answers[currentQuestionIndex]);
                    saveWrongAnswer(wrongAnswersFilename, questions[currentQuestionIndex], answers[currentQuestionIndex], userAnswer);
                    break;
                }
            }
        }

        while (getchar() != '\n');
    }

    fclose(wrongAnswersFile);
    free(questionOrder);

    return 0;
}

void readQuestionAndAnswer(char* questionFilename, char* answerFilename, char* hintFilename, char questions[][MAX_QUESTION_LENGTH], char answers[][MAX_ANSWER_LENGTH], char hints[][MAX_HINT_LENGTH], int* numQuestions) {
    FILE* questionFile = fopen(questionFilename, "r");
    FILE* answerFile = fopen(answerFilename, "r");
    FILE* hintFile = fopen(hintFilename, "r");

    if (questionFile == NULL || answerFile == NULL || hintFile == NULL) {
        *numQuestions = 0;
        return;
    }

    *numQuestions = 0;
    while (fgets(questions[*numQuestions], MAX_QUESTION_LENGTH, questionFile) != NULL &&
        fgets(answers[*numQuestions], MAX_ANSWER_LENGTH, answerFile) != NULL &&
        fgets(hints[*numQuestions], MAX_HINT_LENGTH, hintFile) != NULL) {
        questions[*numQuestions][strcspn(questions[*numQuestions], "\n")] = 0;
        answers[*numQuestions][strcspn(answers[*numQuestions], "\n")] = 0;
        hints[*numQuestions][strcspn(hints[*numQuestions], "\n")] = 0;

        (*numQuestions)++;
    }

    fclose(questionFile);
    fclose(answerFile);
    fclose(hintFile);
}

int checkAnswer(int questionIndex, char userAnswer[MAX_ANSWER_LENGTH], char answers[][MAX_ANSWER_LENGTH]) {
    return strcmp(userAnswer, answers[questionIndex]) == 0;
}

void saveWrongAnswer(char* filename, char question[MAX_QUESTION_LENGTH], char correctAnswer[MAX_ANSWER_LENGTH], char userAnswer[MAX_ANSWER_LENGTH]) {
    FILE* file = fopen(filename, "a");

    if (file != NULL) {
        fprintf(file, "문제: %s\n", question);
        fprintf(file, "정답: %s\n", correctAnswer);
        fprintf(file, "오답: %s\n", userAnswer);
        fprintf(file, "------------------------\n");

        fclose(file);
    }
    else {
        printf("오답 노트 파일에 기록할 수 없습니다.\n");
    }
}

void displayHint(char hints[][MAX_HINT_LENGTH], int currentQuestionIndex) {
    printf("힌트: %s\n", hints[currentQuestionIndex]);
}

<<<<<<< HEAD
=======
*/

/*오답노트 중복 기록 여부 체크 후 전체 코드
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_QUESTION_LENGTH 256
#define MAX_ANSWER_LENGTH 64
#define MAX_HINT_LENGTH 256
#define MAX_QUESTIONS 100

void readQuestionAndAnswer(char* questionFilename, char* answerFilename, char* hintFilename, char questions[][MAX_QUESTION_LENGTH], char answers[][MAX_ANSWER_LENGTH], char hints[][MAX_HINT_LENGTH], int* numQuestions);
int checkAnswer(int questionIndex, char userAnswer[MAX_ANSWER_LENGTH], char answers[][MAX_ANSWER_LENGTH]);
void saveWrongAnswer(char* filename, char question[MAX_QUESTION_LENGTH], char correctAnswer[MAX_ANSWER_LENGTH], char userAnswer[MAX_ANSWER_LENGTH]);
void displayHint(char hints[][MAX_HINT_LENGTH], int currentQuestionIndex);
int isAlreadyRecorded(char* filename, char question[MAX_QUESTION_LENGTH]);

int main() {
    char questionFilename[] = "question.txt";
    char answerFilename[] = "answer.txt";
    char hintFilename[] = "hint.txt";
    char wrongAnswersFilename[] = "wrong_answers.txt";

    char questions[MAX_QUESTIONS][MAX_QUESTION_LENGTH];
    char answers[MAX_QUESTIONS][MAX_ANSWER_LENGTH];
    char hints[MAX_QUESTIONS][MAX_HINT_LENGTH];
    int numQuestions = 0;

    readQuestionAndAnswer(questionFilename, answerFilename, hintFilename, questions, answers, hints, &numQuestions);

    if (numQuestions == 0) {
        printf("문제 파일, 정답 파일 또는 힌트 파일을 읽을 수 없습니다.\n");
        return 1;
    }

    srand(time(NULL));

    char userAnswer[MAX_ANSWER_LENGTH];
    char exitInput[MAX_ANSWER_LENGTH] = "q";
    char hintInput[MAX_ANSWER_LENGTH] = "h";

    int* questionOrder = (int*)malloc(numQuestions * sizeof(int));
    if (questionOrder == NULL) {
        printf("메모리 할당 오류\n");
        return 1;
    }

    FILE* wrongAnswersFile = fopen(wrongAnswersFilename, "a");
    if (wrongAnswersFile == NULL) {
        printf("오답 노트 파일을 열 수 없습니다.\n");
        free(questionOrder);
        return 1;
    }

    for (int i = 0; i < numQuestions; i++) {
        questionOrder[i] = i;
    }

    for (int i = 0; i < numQuestions; i++) {
        int randomIndex = i + rand() % (numQuestions - i);
        int temp = questionOrder[i];
        questionOrder[i] = questionOrder[randomIndex];
        questionOrder[randomIndex] = temp;

        int currentQuestionIndex = questionOrder[i];

        printf("문제: %s\n", questions[currentQuestionIndex]);

        while (1) {
            printf("답을 입력하세요 (종료하려면 'q' 입력, 힌트 보려면 'h' 입력): ");
            scanf("%s", userAnswer);

            if (strcmp(userAnswer, exitInput) == 0) {
                printf("프로그램을 종료합니다.\n");
                break;
            }
            else if (strcmp(userAnswer, hintInput) == 0) {
                displayHint(hints, currentQuestionIndex);
            }
            else {
                if (checkAnswer(currentQuestionIndex, userAnswer, answers)) {
                    printf("정답!\n");
                    break;
                }
                else {
                    if (!isAlreadyRecorded(wrongAnswersFilename, questions[currentQuestionIndex])) {
                        printf("오답! 정답은 %s 입니다.\n", answers[currentQuestionIndex]);
                        saveWrongAnswer(wrongAnswersFilename, questions[currentQuestionIndex], answers[currentQuestionIndex], userAnswer);
                    }
                    else {
                        printf("오답! 정답은 %s 입니다.\n", answers[currentQuestionIndex]);
                    }
                    break;
                }
            }
        }

        while (getchar() != '\n');
    }

    fclose(wrongAnswersFile);
    free(questionOrder);

    return 0;
}

void readQuestionAndAnswer(char* questionFilename, char* answerFilename, char* hintFilename, char questions[][MAX_QUESTION_LENGTH], char answers[][MAX_ANSWER_LENGTH], char hints[][MAX_HINT_LENGTH], int* numQuestions) {
    FILE* questionFile = fopen(questionFilename, "r");
    FILE* answerFile = fopen(answerFilename, "r");
    FILE* hintFile = fopen(hintFilename, "r");

    if (questionFile == NULL || answerFile == NULL || hintFile == NULL) {
        *numQuestions = 0;
        return;
    }

    *numQuestions = 0;
    while (fgets(questions[*numQuestions], MAX_QUESTION_LENGTH, questionFile) != NULL &&
        fgets(answers[*numQuestions], MAX_ANSWER_LENGTH, answerFile) != NULL &&
        fgets(hints[*numQuestions], MAX_HINT_LENGTH, hintFile) != NULL) {
        questions[*numQuestions][strcspn(questions[*numQuestions], "\n")] = 0;
        answers[*numQuestions][strcspn(answers[*numQuestions], "\n")] = 0;
        hints[*numQuestions][strcspn(hints[*numQuestions], "\n")] = 0;

        (*numQuestions)++;
    }

    fclose(questionFile);
    fclose(answerFile);
    fclose(hintFile);
}

int checkAnswer(int questionIndex, char userAnswer[MAX_ANSWER_LENGTH], char answers[][MAX_ANSWER_LENGTH]) {
    return strcmp(userAnswer, answers[questionIndex]) == 0;
}

void saveWrongAnswer(char* filename, char question[MAX_QUESTION_LENGTH], char correctAnswer[MAX_ANSWER_LENGTH], char userAnswer[MAX_ANSWER_LENGTH]) {
    FILE* file = fopen(filename, "a");

    if (file != NULL) {
        fprintf(file, "문제: %s\n", question);
        fprintf(file, "정답: %s\n", correctAnswer);
        fprintf(file, "오답: %s\n", userAnswer);
        fprintf(file, "------------------------\n");

        fclose(file);
    }
    else {
        printf("오답 노트 파일에 기록할 수 없습니다.\n");
    }
}

void displayHint(char hints[][MAX_HINT_LENGTH], int currentQuestionIndex) {
    printf("힌트: %s\n", hints[currentQuestionIndex]);
}

int isAlreadyRecorded(char* filename, char question[MAX_QUESTION_LENGTH]) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return 0; // 파일을 열 수 없으면 중복 여부를 확인할 수 없음
    }

    char line[MAX_QUESTION_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = 0; // 개행 문자 제거
        if (strstr(line, question) != NULL) {
            fclose(file);
            return 1; // 중복 기록이 발견됨
        }
    }

    fclose(file);
    return 0; // 중복 기록이 발견되지 않음
}

<<<<<<< HEAD
=======
*/

/*회원가입과 아이디 입력, 푼 문제의 정답 개수와 등급 출력
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUESTION_LENGTH 256
#define MAX_ANSWER_LENGTH 64
#define MAX_HINT_LENGTH 256
#define MAX_QUESTIONS 100

void readQuestionAndAnswer(char* questionFilename, char* answerFilename, char* hintFilename, char questions[][MAX_QUESTION_LENGTH], char answers[][MAX_ANSWER_LENGTH], char hints[][MAX_HINT_LENGTH], int* numQuestions);
int checkAnswer(int questionIndex, char userAnswer[MAX_ANSWER_LENGTH], char answers[][MAX_ANSWER_LENGTH]);
void saveWrongAnswer(char* filename, char question[MAX_QUESTION_LENGTH], char correctAnswer[MAX_ANSWER_LENGTH], char userAnswer[MAX_ANSWER_LENGTH]);
void displayHint(char hints[][MAX_HINT_LENGTH], int currentQuestionIndex);
int isAlreadyRecorded(char* filename, char question[MAX_QUESTION_LENGTH]);

struct Member {
    char username[50];
    int numQuestionsSolved; // 푼 문제 개수
    char grade;
};

void signup();
void login();
int isUsernameExists(const char* username);

int main() {
    struct Member member;
    int choice;

    do {
        printf("\n1. 회원 가입\n");
        printf("2. 로그인\n");
        printf("3. 문제로 넘어가기\n");
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
            break;
        default:
            printf("올바른 선택이 아닙니다. 다시 선택해주세요.\n");
        }
    } while (choice != 3);

    char questionFilename[] = "question.txt";
    char answerFilename[] = "answer.txt";
    char hintFilename[] = "hint.txt";
    char wrongAnswersFilename[] = "wrong_answers.txt";

    char questions[MAX_QUESTIONS][MAX_QUESTION_LENGTH];
    char answers[MAX_QUESTIONS][MAX_ANSWER_LENGTH];
    char hints[MAX_QUESTIONS][MAX_HINT_LENGTH];
    int numQuestions = 0;

    readQuestionAndAnswer(questionFilename, answerFilename, hintFilename, questions, answers, hints, &numQuestions);

    if (numQuestions == 0) {
        printf("문제 파일, 정답 파일 또는 힌트 파일을 읽을 수 없습니다.\n");
        return 1;
    }

    srand(time(NULL));

    char userAnswer[MAX_ANSWER_LENGTH];
    char exitInput[MAX_ANSWER_LENGTH] = "q";
    char hintInput[MAX_ANSWER_LENGTH] = "h";

    int* questionOrder = (int*)malloc(numQuestions * sizeof(int));
    if (questionOrder == NULL) {
        printf("메모리 할당 오류\n");
        return 1;
    }

    FILE* wrongAnswersFile = fopen(wrongAnswersFilename, "a");
    if (wrongAnswersFile == NULL) {
        printf("오답 노트 파일을 열 수 없습니다.\n");
        free(questionOrder);
        return 1;
    }

    int correctAnswers = 0; // 맞은 문제의 개수

    for (int i = 0; i < numQuestions; i++) {
        questionOrder[i] = i;
    }

    for (int i = 0; i < numQuestions; i++) {
        int randomIndex = i + rand() % (numQuestions - i);
        int temp = questionOrder[i];
        questionOrder[i] = questionOrder[randomIndex];
        questionOrder[randomIndex] = temp;

        int currentQuestionIndex = questionOrder[i];

        printf("문제: %s\n", questions[currentQuestionIndex]);

        while (1) {
            member.numQuestionsSolved = 0;
            printf("답을 입력하세요 (종료하려면 'q' 입력, 힌트 보려면 'h' 입력): ");
            scanf("%s", userAnswer);

            if (strcmp(userAnswer, hintInput) == 0) {
                displayHint(hints, currentQuestionIndex);
            }
            else if (strcmp(userAnswer, exitInput) == 0) {
                double accuracy = (double)correctAnswers / numQuestions * 100;

                printf("맞은 문제 개수: %d\n", correctAnswers);

                if (accuracy == 100) {
                    printf("등급: S\n");
                }
                else if (accuracy >= 80) {
                    printf("등급: A\n");
                }
                else if (accuracy >= 60) {
                    printf("등급: B\n");
                }
                else if (accuracy >= 40) {
                    printf("등급: C\n");
                }
                else if (accuracy >= 20) {
                    printf("등급: D\n");
                }
                else {
                    printf("등급: F\n");
                }
                break;
            }
            else {
                if (checkAnswer(currentQuestionIndex, userAnswer, answers)) {
                    printf("정답!\n");
                    member.numQuestionsSolved++;
                    correctAnswers++; // 맞은 문제 개수 증가
                    break;
                }
                else {
                    if (!isAlreadyRecorded(wrongAnswersFilename, questions[currentQuestionIndex])) {
                        printf("오답! 정답은 %s 입니다.\n", answers[currentQuestionIndex]);
                        saveWrongAnswer(wrongAnswersFilename, questions[currentQuestionIndex], answers[currentQuestionIndex], userAnswer);
                    }
                    else {
                        printf("오답! 정답은 %s 입니다.\n", answers[currentQuestionIndex]);
                    }
                    break;
                }
            }
        }

        while (getchar() != '\n');
    }

    // 성적 계산
    double accuracy = (double)correctAnswers / numQuestions * 100;

    printf("맞은 문제 개수: %d\n", correctAnswers);

    if (accuracy == 100) {
        printf("등급: S\n");
    }
    else if (accuracy >= 80) {
        printf("등급: A\n");
    }
    else if (accuracy >= 60) {
        printf("등급: B\n");
    }
    else if (accuracy >= 40) {
        printf("등급: C\n");
    }
    else if (accuracy >= 20) {
        printf("등급: D\n");
    }
    else {
        printf("등급: F\n");
    }

    fclose(wrongAnswersFile);
    free(questionOrder);

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
}

void readQuestionAndAnswer(char* questionFilename, char* answerFilename, char* hintFilename, char questions[][MAX_QUESTION_LENGTH], char answers[][MAX_ANSWER_LENGTH], char hints[][MAX_HINT_LENGTH], int* numQuestions) {
    FILE* questionFile = fopen(questionFilename, "r");
    FILE* answerFile = fopen(answerFilename, "r");
    FILE* hintFile = fopen(hintFilename, "r");

    if (questionFile == NULL || answerFile == NULL || hintFile == NULL) {
        *numQuestions = 0;
        return;
    }

    *numQuestions = 0;
    while (fgets(questions[*numQuestions], MAX_QUESTION_LENGTH, questionFile) != NULL &&
        fgets(answers[*numQuestions], MAX_ANSWER_LENGTH, answerFile) != NULL &&
        fgets(hints[*numQuestions], MAX_HINT_LENGTH, hintFile) != NULL) {
        questions[*numQuestions][strcspn(questions[*numQuestions], "\n")] = 0;
        answers[*numQuestions][strcspn(answers[*numQuestions], "\n")] = 0;
        hints[*numQuestions][strcspn(hints[*numQuestions], "\n")] = 0;

        (*numQuestions)++;
    }

    fclose(questionFile);
    fclose(answerFile);
    fclose(hintFile);
}

int checkAnswer(int questionIndex, char userAnswer[MAX_ANSWER_LENGTH], char answers[][MAX_ANSWER_LENGTH]) {
    return strcmp(userAnswer, answers[questionIndex]) == 0;
}

void saveWrongAnswer(char* filename, char question[MAX_QUESTION_LENGTH], char correctAnswer[MAX_ANSWER_LENGTH], char userAnswer[MAX_ANSWER_LENGTH]) {
    FILE* file = fopen(filename, "a");

    if (file != NULL) {
        fprintf(file, "문제: %s\n", question);
        fprintf(file, "정답: %s\n", correctAnswer);
        fprintf(file, "오답: %s\n", userAnswer);
        fprintf(file, "------------------------\n");

        fclose(file);
    }
    else {
        printf("오답 노트 파일에 기록할 수 없습니다.\n");
    }
}

void displayHint(char hints[][MAX_HINT_LENGTH], int currentQuestionIndex) {
    printf("힌트: %s\n", hints[currentQuestionIndex]);
}

int isAlreadyRecorded(char* filename, char question[MAX_QUESTION_LENGTH]) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return 0; // 파일을 열 수 없으면 중복 여부를 확인할 수 없음
    }

    char line[MAX_QUESTION_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = 0; // 개행 문자 제거
        if (strstr(line, question) != NULL) {
            fclose(file);
            return 1; // 중복 기록이 발견됨
        }
    }

    fclose(file);
    return 0; // 중복 기록이 발견되지 않음
}

*/

/* 다지선다(객관식) 문제 출력 코드
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_QUESTION_LENGTH 256
#define MAX_ANSWER_LENGTH 64
#define MAX_HINT_LENGTH 256
#define MAX_QUESTIONS 100
#define MAX_NUMBERS 400 // 100 questions * 4 numbers

void readQuestionAndAnswer(char* questionFilename, char* answerFilename, char* hintFilename, char questions[][MAX_QUESTION_LENGTH], char answers[][MAX_ANSWER_LENGTH], char hints[][MAX_HINT_LENGTH], int* numQuestions);
void checkAnswerAndPrintResult(int currentQuestionIndex, char userAnswer[MAX_ANSWER_LENGTH], char answers[][MAX_ANSWER_LENGTH], char wrongAnswersFilename[], char questions[][MAX_QUESTION_LENGTH]);
void displayHint(char hints[][MAX_HINT_LENGTH], int currentQuestionIndex);
void readNumbers(char* filename, char numbers[][MAX_QUESTION_LENGTH], int* numNumbers);
void printNumbers(char numbers[][MAX_QUESTION_LENGTH], int start, int end);
bool checkAnswer(int questionIndex, char userAnswer[MAX_ANSWER_LENGTH], char answers[][MAX_ANSWER_LENGTH]) {
    return strcmp(userAnswer, answers[questionIndex]) == 0;
}

int main() {
    char questionFilename[] = "question.txt";
    char answerFilename[] = "answer.txt";
    char hintFilename[] = "hint.txt";
    char wrongAnswersFilename[] = "wrong_answers.txt";
    char numberFilename[] = "number.txt";

    char questions[MAX_QUESTIONS][MAX_QUESTION_LENGTH];
    char answers[MAX_QUESTIONS][MAX_ANSWER_LENGTH];
    char hints[MAX_QUESTIONS][MAX_HINT_LENGTH];
    char numbers[MAX_NUMBERS][MAX_QUESTION_LENGTH];
    int numQuestions = 0;
    int numNumbers = 0;

    readQuestionAndAnswer(questionFilename, answerFilename, hintFilename, questions, answers, hints, &numQuestions);
    readNumbers(numberFilename, numbers, &numNumbers);

    if (numQuestions == 0 || numNumbers == 0) {
        printf("문제 파일, 정답 파일, 힌트 파일 또는 숫자 파일을 읽을 수 없습니다.\n");
        return 1;
    }

    srand(time(NULL));

    char userAnswer[MAX_ANSWER_LENGTH];
    char exitInput[MAX_ANSWER_LENGTH] = "q";
    char hintInput[MAX_ANSWER_LENGTH] = "h";

    int* questionOrder = (int*)malloc(numQuestions * sizeof(int));
    if (questionOrder == NULL) {
        printf("메모리 할당 오류\n");
        return 1;
    }

    FILE* wrongAnswersFile = fopen(wrongAnswersFilename, "a");
    if (wrongAnswersFile == NULL) {
        printf("오답 노트 파일을 열 수 없습니다.\n");
        free(questionOrder);
        return 1;
    }

    for (int i = 0; i < numQuestions; i++) {
        questionOrder[i] = i;
    }

    for (int i = 0; i < numQuestions; i++) {
        int randomIndex = i + rand() % (numQuestions - i);
        int temp = questionOrder[i];
        questionOrder[i] = questionOrder[randomIndex];
        questionOrder[randomIndex] = temp;

        int currentQuestionIndex = questionOrder[i];

        printf("문제: %s\n", questions[currentQuestionIndex]);

        int start = 0;
        int end = 0;

        // 조건문을 추가하여 number.txt의 범위 설정
        if (currentQuestionIndex == 0) {
            start = 0;
            end = 4;
        }
        else if (currentQuestionIndex == 1) {
            start = 4;
            end = 8;
        }
        else if (currentQuestionIndex == 2) {
            start = 8;
            end = 12;
        }
        else if (currentQuestionIndex == 3) {
            start = 12;
            end = 16;
        }
        else if (currentQuestionIndex == 4) {
            start = 16;
            end = 20;
        }
        else if (currentQuestionIndex == 5) {
            start = 20;
            end = 24;
        }
        else if (currentQuestionIndex == 6) {
            start = 24;
            end = 28;
        }
        else if (currentQuestionIndex == 7) {
            start = 28;
            end = 32;
        }
        else if (currentQuestionIndex == 8) {
            start = 32;
            end = 36;
        }
        else if (currentQuestionIndex == 9) {
            start = 36;
            end = 40;
        }
        else if (currentQuestionIndex == 10) {
            start = 40;
            end = 44;
        }

        printNumbers(numbers, start, end);

        while (1) {
            printf("답을 입력하세요 (종료하려면 'q' 입력, 힌트 보려면 'h' 입력): ");
            scanf("%s", userAnswer);

            if (strcmp(userAnswer, exitInput) == 0) {
                printf("프로그램을 종료합니다.\n");
                break;
            }
            else if (strcmp(userAnswer, hintInput) == 0) {
                displayHint(hints, currentQuestionIndex);
            }
            else {
                checkAnswerAndPrintResult(currentQuestionIndex, userAnswer, answers, wrongAnswersFilename, questions);
                break;
            }
        }

        while (getchar() != '\n');
    }

    fclose(wrongAnswersFile);
    free(questionOrder);

    return 0;
}



void readQuestionAndAnswer(char* questionFilename, char* answerFilename, char* hintFilename, char questions[][MAX_QUESTION_LENGTH], char answers[][MAX_ANSWER_LENGTH], char hints[][MAX_HINT_LENGTH], int* numQuestions) {
    FILE* questionFile = fopen(questionFilename, "r");
    FILE* answerFile = fopen(answerFilename, "r");
    FILE* hintFile = fopen(hintFilename, "r");

    if (questionFile == NULL || answerFile == NULL || hintFile == NULL) {
        *numQuestions = 0;
        return;
    }

    *numQuestions = 0;
    while (*numQuestions < MAX_QUESTIONS &&
        fgets(questions[*numQuestions], MAX_QUESTION_LENGTH, questionFile) != NULL &&
        fgets(answers[*numQuestions], MAX_ANSWER_LENGTH, answerFile) != NULL &&
        fgets(hints[*numQuestions], MAX_HINT_LENGTH, hintFile) != NULL) {
        questions[*numQuestions][strcspn(questions[*numQuestions], "\n")] = 0;
        answers[*numQuestions][strcspn(answers[*numQuestions], "\n")] = 0;
        hints[*numQuestions][strcspn(hints[*numQuestions], "\n")] = 0;

        (*numQuestions)++;
    }

    fclose(questionFile);
    fclose(answerFile);
    fclose(hintFile);
}

void saveWrongAnswer(char* filename, char question[MAX_QUESTION_LENGTH], char correctAnswer[MAX_ANSWER_LENGTH], char userAnswer[MAX_ANSWER_LENGTH]) {
    FILE* file = fopen(filename, "a");

    if (file != NULL) {
        fprintf(file, "문제: %s\n", question);
        fprintf(file, "정답: %s\n", correctAnswer);
        fprintf(file, "오답: %s\n", userAnswer);
        fprintf(file, "------------------------\n");

        fclose(file);
    }
    else {
        printf("오답 노트 파일에 기록할 수 없습니다.\n");
    }
}

void checkAnswerAndPrintResult(int currentQuestionIndex, char userAnswer[MAX_ANSWER_LENGTH], char answers[][MAX_ANSWER_LENGTH], char wrongAnswersFilename[], char questions[][MAX_QUESTION_LENGTH]) {
    if (checkAnswer(currentQuestionIndex, userAnswer, answers)) {
        printf("정답!\n");
    }
    else {
        printf("오답! 정답은 %s 입니다.\n", answers[currentQuestionIndex]);
        saveWrongAnswer(wrongAnswersFilename, questions[currentQuestionIndex], answers[currentQuestionIndex], userAnswer);
    }
}

void displayHint(char hints[][MAX_HINT_LENGTH], int currentQuestionIndex) {
    printf("힌트: %s\n", hints[currentQuestionIndex]);
}

void readNumbers(char* filename, char numbers[][MAX_QUESTION_LENGTH], int* numNumbers) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        *numNumbers = 0;
        return;
    }

    *numNumbers = 0;
    while (*numNumbers < MAX_NUMBERS && fgets(numbers[*numNumbers], MAX_QUESTION_LENGTH, file) != NULL) {
        numbers[*numNumbers][strcspn(numbers[*numNumbers], "\n")] = 0;
        (*numNumbers)++;
    }

    fclose(file);
}

void printNumbers(char numbers[][MAX_QUESTION_LENGTH], int start, int end) {
    for (int i = start; i < end; i++) {
        printf("%s\n", numbers[i]);
    }
}

*/

/* 객관식 문제 출력 코드 (+설명 기능 추가)
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_QUESTION_LENGTH 256
#define MAX_ANSWER_LENGTH 64
#define MAX_HINT_LENGTH 256
#define MAX_QUESTIONS 100
#define MAX_EXPLANATION_LENGTH 256
#define MAX_NUMBERS 400 // 100 questions * 4 numbers

void readQuestionAndAnswer(char* questionFilename, char* answerFilename, char* hintFilename, char* explanationFilename, char questions[][MAX_QUESTION_LENGTH], char answers[][MAX_ANSWER_LENGTH], char hints[][MAX_HINT_LENGTH], char explanations[][MAX_EXPLANATION_LENGTH], int* numQuestions);void checkAnswerAndPrintResult(int currentQuestionIndex, char userAnswer[MAX_ANSWER_LENGTH], char answers[][MAX_ANSWER_LENGTH], char wrongAnswersFilename[], char questions[][MAX_QUESTION_LENGTH], char explanations[][MAX_EXPLANATION_LENGTH]);
void checkAnswerAndPrintResult(int currentQuestionIndex, char userAnswer[MAX_ANSWER_LENGTH], char answers[][MAX_ANSWER_LENGTH], char wrongAnswersFilename[], char questions[][MAX_QUESTION_LENGTH], char explanations[][MAX_EXPLANATION_LENGTH]);
void displayHint(char hints[][MAX_HINT_LENGTH], int currentQuestionIndex);
void readNumbers(char* filename, char numbers[][MAX_QUESTION_LENGTH], int* numNumbers);
void readExplanations(char* filename, char explanations[][MAX_EXPLANATION_LENGTH], int* numExplanations);
void printNumbers(char numbers[][MAX_QUESTION_LENGTH], int start, int end);
bool checkAnswer(int questionIndex, char userAnswer[MAX_ANSWER_LENGTH], char answers[][MAX_ANSWER_LENGTH]) {
    return strcmp(userAnswer, answers[questionIndex]) == 0;
}

int main() {
    char questionFilename[] = "question.txt";
    char answerFilename[] = "answer.txt";
    char hintFilename[] = "hint.txt";
    char explanationFilename[] = "explanation.txt";
    char wrongAnswersFilename[] = "wrong_answers.txt";
    char numberFilename[] = "number.txt";

    char questions[MAX_QUESTIONS][MAX_QUESTION_LENGTH];
    char answers[MAX_QUESTIONS][MAX_ANSWER_LENGTH];
    char hints[MAX_QUESTIONS][MAX_HINT_LENGTH];
    char explanations[MAX_QUESTIONS][MAX_EXPLANATION_LENGTH];
    char numbers[MAX_NUMBERS][MAX_QUESTION_LENGTH];
    int numQuestions = 0;
    int numNumbers = 0;
    int numExplanations = 0;

    readQuestionAndAnswer(questionFilename, answerFilename, hintFilename, explanationFilename, questions, answers, hints, explanations, &numQuestions);
    readNumbers(numberFilename, numbers, &numNumbers);
    readExplanations(explanationFilename, explanations, &numExplanations);

    if (numQuestions == 0 || numNumbers == 0 || numExplanations == 0) {
        printf("문제 파일, 정답 파일, 힌트 파일, 설명 파일, 또는 숫자 파일을 읽을 수 없습니다.\n");
        return 1;
    }

    srand(time(NULL));

    char userAnswer[MAX_ANSWER_LENGTH];
    char exitInput[MAX_ANSWER_LENGTH] = "q";
    char hintInput[MAX_ANSWER_LENGTH] = "h";

    int* questionOrder = (int*)malloc(numQuestions * sizeof(int));
    if (questionOrder == NULL) {
        printf("메모리 할당 오류\n");
        return 1;
    }

    FILE* wrongAnswersFile = fopen(wrongAnswersFilename, "a");
    if (wrongAnswersFile == NULL) {
        printf("오답 노트 파일을 열 수 없습니다.\n");
        free(questionOrder);
        return 1;
    }

    for (int i = 0; i < numQuestions; i++) {
        questionOrder[i] = i;
    }

    for (int i = 0; i < numQuestions; i++) {
        int randomIndex = i + rand() % (numQuestions - i);
        int temp = questionOrder[i];
        questionOrder[i] = questionOrder[randomIndex];
        questionOrder[randomIndex] = temp;

        int currentQuestionIndex = questionOrder[i];

        printf("문제: %s\n", questions[currentQuestionIndex]);

        int start = 0;
        int end = 0;

        // 조건문을 추가하여 number.txt의 범위 설정
        if (currentQuestionIndex == 0) {
            start = 0;
            end = 4;
        }
        else if (currentQuestionIndex == 1) {
            start = 4;
            end = 8;
        }
        else if (currentQuestionIndex == 2) {
            start = 8;
            end = 12;
        }
        else if (currentQuestionIndex == 3) {
            start = 12;
            end = 16;
        }
        else if (currentQuestionIndex == 4) {
            start = 16;
            end = 20;
        }
        else if (currentQuestionIndex == 5) {
            start = 20;
            end = 24;
        }
        else if (currentQuestionIndex == 6) {
            start = 24;
            end = 28;
        }
        else if (currentQuestionIndex == 7) {
            start = 28;
            end = 32;
        }
        else if (currentQuestionIndex == 8) {
            start = 32;
            end = 36;
        }
        else if (currentQuestionIndex == 9) {
            start = 36;
            end = 40;
        }
        else if (currentQuestionIndex == 10) {
            start = 40;
            end = 44;
        }

        printNumbers(numbers, start, end);

        while (1) {
            printf("답을 입력하세요 (종료하려면 'q' 입력, 힌트 보려면 'h' 입력): ");
            scanf("%s", userAnswer);

            if (strcmp(userAnswer, exitInput) == 0) {
                printf("프로그램을 종료합니다.\n");
                break;
            }
            else if (strcmp(userAnswer, hintInput) == 0) {
                displayHint(hints, currentQuestionIndex);
            }
            else {
                checkAnswerAndPrintResult(currentQuestionIndex, userAnswer, answers, wrongAnswersFilename, questions, explanations);
                break;
            }
        }

        while (getchar() != '\n');
    }

    fclose(wrongAnswersFile);
    free(questionOrder);

    return 0;
}

void readQuestionAndAnswer(char* questionFilename, char* answerFilename, char* hintFilename, char* explanationFilename, char questions[][MAX_QUESTION_LENGTH], char answers[][MAX_ANSWER_LENGTH], char hints[][MAX_HINT_LENGTH], char explanations[][MAX_EXPLANATION_LENGTH], int* numQuestions) {
    FILE* questionFile = fopen(questionFilename, "r");
    FILE* answerFile = fopen(answerFilename, "r");
    FILE* hintFile = fopen(hintFilename, "r");
    FILE* explanationFile = fopen(explanationFilename, "r");

    if (questionFile == NULL || answerFile == NULL || hintFile == NULL || explanationFile == NULL) {
        *numQuestions = 0;
        return;
    }

    *numQuestions = 0;
    while (fgets(questions[*numQuestions], MAX_QUESTION_LENGTH, questionFile) != NULL &&
        fgets(answers[*numQuestions], MAX_ANSWER_LENGTH, answerFile) != NULL &&
        fgets(hints[*numQuestions], MAX_HINT_LENGTH, hintFile) != NULL &&
        fgets(explanations[*numQuestions], MAX_EXPLANATION_LENGTH, explanationFile) != NULL) {
        questions[*numQuestions][strcspn(questions[*numQuestions], "\n")] = 0;
        answers[*numQuestions][strcspn(answers[*numQuestions], "\n")] = 0;
        hints[*numQuestions][strcspn(hints[*numQuestions], "\n")] = 0;
        explanations[*numQuestions][strcspn(explanations[*numQuestions], "\n")] = 0;

        (*numQuestions)++;
    }

    fclose(questionFile);
    fclose(answerFile);
    fclose(hintFile);
    fclose(explanationFile);
}

void saveWrongAnswer(char* filename, char question[MAX_QUESTION_LENGTH], char correctAnswer[MAX_ANSWER_LENGTH], char userAnswer[MAX_ANSWER_LENGTH], char explanation[MAX_EXPLANATION_LENGTH]) {
    FILE* file = fopen(filename, "a");

    if (file != NULL) {
        fprintf(file, "문제: %s\n", question);
        fprintf(file, "정답: %s\n", correctAnswer);
        fprintf(file, "오답: %s\n", userAnswer);
        fprintf(file, "설명: %s\n", explanation);
        fprintf(file, "------------------------\n");

        fclose(file);
    }
    else {
        printf("오답 노트 파일에 기록할 수 없습니다.\n");
    }
}

void checkAnswerAndPrintResult(int currentQuestionIndex, char userAnswer[MAX_ANSWER_LENGTH], char answers[][MAX_ANSWER_LENGTH], char wrongAnswersFilename[], char questions[][MAX_QUESTION_LENGTH], char explanations[][MAX_EXPLANATION_LENGTH]) {
    if (checkAnswer(currentQuestionIndex, userAnswer, answers)) {
        printf("정답!\n\n");
    }
    else {
        printf("오답! 정답은 %s 입니다.\n", answers[currentQuestionIndex]);
        printf("설명: %s\n\n", explanations[currentQuestionIndex]);
        saveWrongAnswer(wrongAnswersFilename, questions[currentQuestionIndex], answers[currentQuestionIndex], userAnswer, explanations[currentQuestionIndex]);
    }
}

void displayHint(char hints[][MAX_HINT_LENGTH], int currentQuestionIndex) {
    printf("힌트: %s\n", hints[currentQuestionIndex]);
}

void readNumbers(char* filename, char numbers[][MAX_QUESTION_LENGTH], int* numNumbers) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        *numNumbers = 0;
        return;
    }

    *numNumbers = 0;
    while (*numNumbers < MAX_NUMBERS && fgets(numbers[*numNumbers], MAX_QUESTION_LENGTH, file) != NULL) {
        numbers[*numNumbers][strcspn(numbers[*numNumbers], "\n")] = 0;
        (*numNumbers)++;
    }

    fclose(file);
}

void readExplanations(char* filename, char explanations[][MAX_EXPLANATION_LENGTH], int* numExplanations) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        *numExplanations = 0;
        return;
    }

    *numExplanations = 0;
    while (*numExplanations < MAX_QUESTIONS && fgets(explanations[*numExplanations], MAX_EXPLANATION_LENGTH, file) != NULL) {
        explanations[*numExplanations][strcspn(explanations[*numExplanations], "\n")] = 0;
        (*numExplanations)++;
    }

    fclose(file);
}

void printNumbers(char numbers[][MAX_QUESTION_LENGTH], int start, int end) {
    for (int i = start; i < end; i++) {
        printf("%s\n", numbers[i]);
    }
}
    

>>>>>>> ebbbf32427323bb589356f8061f961665be264d0
>>>>>>> dd655b457e76608b888b0b669c9d24564fad334f
*/