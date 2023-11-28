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




/* 회원가입과 로그인 기능 

#define _CRT_SECURE_NO_WARNINGS

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
/*qustion.txt 문제를 랜덤으로 출력 후 answer.txt 답과 비교해 일치하면 정답 그렇지 않다면 오답을 출력함
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_QUESTION_LENGTH 256
#define MAX_ANSWER_LENGTH 64
#define MAX_QUESTIONS 100

void readQuestionAndAnswer(char* questionFilename, char* answerFilename, char questions[][MAX_QUESTION_LENGTH], char answers[][MAX_ANSWER_LENGTH], int* numQuestions);
int checkAnswer(int questionIndex, char userAnswer[MAX_ANSWER_LENGTH], char answers[][MAX_ANSWER_LENGTH]);

int main() {
    char questionFilename[] = "question.txt";
    char answerFilename[] = "answer.txt";

    char questions[MAX_QUESTIONS][MAX_QUESTION_LENGTH];
    char answers[MAX_QUESTIONS][MAX_ANSWER_LENGTH];
    int numQuestions = 0;

    readQuestionAndAnswer(questionFilename, answerFilename, questions, answers, &numQuestions);

    if (numQuestions == 0) {
        printf("문제 파일 또는 정답 파일을 읽을 수 없습니다.\n");
        return 1;
    }

    srand(time(NULL)); // 시간을 기반으로 난수 생성기 초기화

    char userAnswer[MAX_ANSWER_LENGTH];
    char exitInput[MAX_ANSWER_LENGTH] = "q";

    int* questionOrder = (int*)malloc(numQuestions * sizeof(int));
    if (questionOrder == NULL) {
        printf("메모리 할당 오류\n");
        return 1;
    }

    // 문제 순서 초기화
    for (int i = 0; i < numQuestions; i++) {
        questionOrder[i] = i;
    }

    for (int i = 0; i < numQuestions; i++) {
        // 현재 남은 문제 중 랜덤으로 문제 선택
        int randomIndex = i + rand() % (numQuestions - i);

        // 선택한 문제와 현재 위치의 문제 교환
        int temp = questionOrder[i];
        questionOrder[i] = questionOrder[randomIndex];
        questionOrder[randomIndex] = temp;

        int currentQuestionIndex = questionOrder[i];

        printf("문제: %s\n", questions[currentQuestionIndex]);

        printf("답을 입력하세요 (종료하려면 'q' 입력): ");
        scanf("%s", userAnswer);

        if (strcmp(userAnswer, exitInput) == 0) {
            printf("프로그램을 종료합니다.\n");
            break;
        }

        if (checkAnswer(currentQuestionIndex, userAnswer, answers)) {
            printf("정답!\n");
        }
        else {
            printf("오답! 정답은 %s 입니다.\n", answers[currentQuestionIndex]);
        }

        // 사용자 입력 버퍼 비우기
        while (getchar() != '\n');
    }

    free(questionOrder); // 동적 할당된 메모리 해제

    return 0;
}

void readQuestionAndAnswer(char* questionFilename, char* answerFilename, char questions[][MAX_QUESTION_LENGTH], char answers[][MAX_ANSWER_LENGTH], int* numQuestions) {
    FILE* questionFile = fopen(questionFilename, "r");
    FILE* answerFile = fopen(answerFilename, "r");

    if (questionFile == NULL || answerFile == NULL) {
        *numQuestions = 0;
        return;
    }

    *numQuestions = 0;
    while (fgets(questions[*numQuestions], MAX_QUESTION_LENGTH, questionFile) != NULL && fgets(answers[*numQuestions], MAX_ANSWER_LENGTH, answerFile) != NULL) {
        // 개행 문자 제거
        questions[*numQuestions][strcspn(questions[*numQuestions], "\n")] = 0;
        answers[*numQuestions][strcspn(answers[*numQuestions], "\n")] = 0;

        (*numQuestions)++;
    }

    fclose(questionFile);
    fclose(answerFile);
}

int checkAnswer(int questionIndex, char userAnswer[MAX_ANSWER_LENGTH], char answers[][MAX_ANSWER_LENGTH]) {
    return strcmp(userAnswer, answers[questionIndex]) == 0;
}
*/