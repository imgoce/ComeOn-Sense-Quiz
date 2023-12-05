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
#define MAX_FILE_NAME_LENGTH 100
#define MAX_LINE_LENGTH 100
#define MAX_QUESTION_LENGTH 256
#define MAX_ANSWER_LENGTH 64
#define MAX_QUESTIONS 100
#define MAX_WRONG_ANSWERS 100
#define MAX_HINT_LENGTH 256
#define MAX_GRADE_LENGTH 2

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
int checkAnswer(int questionIndex, char userAnswer[MAX_ANSWER_LENGTH], char answers[][MAX_ANSWER_LENGTH]); //정답인지 확인
void saveWrongAnswer(char* filename, char question[MAX_QUESTION_LENGTH], char correctAnswer[MAX_ANSWER_LENGTH], char userAnswer[MAX_ANSWER_LENGTH]); //오답노트 저장
void displayHint(char hints[][MAX_HINT_LENGTH], int currentQuestionIndex); //힌트
struct Result questions(struct Member loginUser, const char* fileName, const char* fileName2, const char* fileName3, const char* username); //문제 출력
char* generateWrongAnswersFilename(const char* username); //오답노트 파일 이름 생성
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
    struct Result field[18];
};

int main() {
    init();
    struct Member data;
    const char* fileName = NULL;
    const char* fileName2 = NULL;
    const char* fileName3 = NULL;
    struct Member loginUser;
    
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
                        strcpy(loginUser.field, "시사");
                        loginUser.difficulty = i / 3;
                        if (i == 0) {
                            fileName = "current easy.txt";
                            fileName2 = "current easy answers.txt";
                            fileName3 = "current easy hint";
                        }
                        else if (i == 3) {
                            fileName = "Current Normal Level.txt";
                            fileName2 = "Current Normal Level Answers.txt";
                        }
                        else if (i == 6) {
                            fileName = "Current Hard Level.txt";
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
                            fileName = "Person Easy Level.txt";
                        }
                        else if (i == 3) {
                            fileName = "Person Normal Level.txt";
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
                    struct Result result = questions(loginUser, fileName, fileName2, fileName3, data.username);
                    if (result.isError) {
                        gotoxy(80, 25);
                        printf("Error executing questions function.\n");
                        return 1;
                    }
                    int r = printResult(result, loginUser);
                    cls;
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
void setcolor(int text, int back){
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
    gotoxy(x, y + 1);
    printf("ID가 없을 경우");
    gotoxy(x, y + 2);
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
    int x = 90;
    int y = 35;
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
    printf("시사(Easy) : %c(정답 : %d, 오답 : %d)", loginUser.field[0].grade, loginUser.field[0].correctCount, loginUser.field[0].wrongCount);
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
    printf("\n\n\n");
    printf("                                                                                         ComeOn Sense Quiz\n");

    loadUserInfo(loginUser);

    gotoxy(90, 10);
    printf("오답 노트");

    gotoxy(150, 10);
    printf("리더 보드");

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

            gotoxy(175, 10);
            printf("Hint (h 입력)");

            gotoxy(50, 15);
            printf("문제: %s\n", questions[currentQuestionIndex]);

            gotoxy(80, 35);
            printf("답 (종료하려면 'q' 입력): ");
            scanf("%s", userAnswer);

            if (strcmp(userAnswer, exitInput) == 0) {
                gotoxy(80, 36);
                printf("프로그램을 종료합니다.\n");
                Sleep(1000);
                cls;
                break;
            }

            if (checkAnswer(currentQuestionIndex, userAnswer, answers)) {
                CorrectAnswers();
                result.correctCount++;
                Sleep(1000);
                cls;
            }
            else {
                WrongAnswers();
                result.wrongCount++;
                saveWrongAnswer(wrongAnswersFilename, questions[currentQuestionIndex], answers[currentQuestionIndex], userAnswer);
                Sleep(1000);
                cls;
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

*/