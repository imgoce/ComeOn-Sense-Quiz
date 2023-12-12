/* 헤더 선언 */
#include "main.h"
#include "function.h"

/* 함수 */
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
struct Result questions(struct Member loginUser, const char* fileName, const char* fileName2, const char* fileName3, const char* fileName5, const char* username) {
    cls;
    struct Result result = { 0 };
    char questionFilename[MAX_FILE_NAME_LENGTH];
    char answerFilename[MAX_FILE_NAME_LENGTH];
    char hintFilename[MAX_FILE_NAME_LENGTH];
    char ianFilename[MAX_FILE_NAME_LENGTH];
    strcpy(questionFilename, fileName);
    strcpy(answerFilename, fileName2);
    strcpy(hintFilename, fileName3);
    strcpy(ianFilename, fileName5);
    struct Member loggedInUser;
    loggedInUser = loginUser;
    char* wrongAnswersFilename = generateWrongAnswersFilename(loggedInUser.username);

    char formattedWrongAnswersFilename[MAX_FILE_NAME_LENGTH];
    snprintf(formattedWrongAnswersFilename, MAX_FILE_NAME_LENGTH, "%s_wrong_answers.txt", username);

    char questions[MAX_QUESTIONS][MAX_QUESTION_LENGTH];
    char answers[MAX_QUESTIONS][MAX_ANSWER_LENGTH];
    char hints[MAX_QUESTIONS][MAX_HINT_LENGTH];
    char ian[MAX_QUESTIONS][MAX_EXPLANATION_LENGTH];
    int numQuestions = 0;
    int numExplanations = 0;
    int hintcount = 5;
    int problemnumber = 1;

    while (1) {
        readQuestionAndAnswer(questionFilename, answerFilename, hintFilename, questions, answers, hints, &numQuestions);
        readExplanations(ianFilename, ian, &numExplanations);

        if (numQuestions == 0 || numExplanations == 0) {
            gotoxy(80, 25);
            printf("문제 파일 또는 정답 파일을 읽을 수 없습니다.\n");
            result.isError = 1;
            return result;
        }

        srand(time(NULL));

        char userAnswer[MAX_ANSWER_LENGTH];
        char exitInput[MAX_ANSWER_LENGTH] = "q";
        char exitInput2[MAX_ANSWER_LENGTH] = "Q";
        char hintInput[MAX_ANSWER_LENGTH] = "h";
        char hintInput2[MAX_ANSWER_LENGTH] = "H";

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

            gotoxy(165, 5);
            printf("Hint (h) 남은 힌트 수 : %d", hintcount);

            gotoxy(50, 15);
            printf("문제: %s\n", questions[currentQuestionIndex]);
            gotoxy(85, 10);
            printf("문제 번호 : %d", problemnumber);
            problemnumber++;

            while (1) {
                gotoxy(80, 35);
                printf("답(종료 'q', 힌트 'h'): ");

                scanf("%s", userAnswer);

                if (strcmp(userAnswer, exitInput) == 0 || strcmp(userAnswer, exitInput2) == 0) {
                    gotoxy(80, 36);
                    printf("문제 종료\n");
                    Sleep(1000);
                    cls;
                    return result;
                }
                else if (strcmp(userAnswer, hintInput) == 0 || strcmp(userAnswer, hintInput2) == 0) {
                    if (hintcount > 0) {
                        displayHint(hints, currentQuestionIndex);
                        hintcount--;
                        gotoxy(165, 5);
                        printf("Hint (h) 남은 힌트 수 : %d", hintcount);
                        gotoxy(80, 35);
                    }
                    else {
                        gotoxy(80, 37);
                        printf("남은 힌트 수가 없습니다.");
                        Sleep(1000);
                        gotoxy(80, 37);
                        printf("                        ");
                    }
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
                            int a = WrongAnswers(currentQuestionIndex, answers, ian);
                            result.wrongCount++;
                            saveWrongAnswer(wrongAnswersFilename, questions[currentQuestionIndex], answers[currentQuestionIndex], userAnswer, ian[currentQuestionIndex]);
                            if (a == 3) {
                                cls;
                                return result;
                            }
                            Sleep(1000);
                            cls;
                        }
                        else {
                            int a = WrongAnswers(currentQuestionIndex, answers, ian);
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
struct Result questions2(struct Member loginUser, const char* fileName, const char* fileName2, const char* fileName3, const char* fileName4, const char* fileName5, const char* username) {
    cls;
    struct Result result = { 0 };
    char questionFilename[MAX_FILE_NAME_LENGTH];
    char answerFilename[MAX_FILE_NAME_LENGTH];
    char hintFilename[MAX_FILE_NAME_LENGTH];
    char numberFilename[MAX_FILE_NAME_LENGTH];
    char ianFilename[MAX_FILE_NAME_LENGTH];
    strcpy(questionFilename, fileName);
    strcpy(answerFilename, fileName2);
    strcpy(hintFilename, fileName3);
    strcpy(numberFilename, fileName4);
    strcpy(ianFilename, fileName5);
    struct Member loggedInUser;
    loggedInUser = loginUser;
    char* wrongAnswersFilename = generateWrongAnswersFilename(loggedInUser.username);

    char formattedWrongAnswersFilename[MAX_FILE_NAME_LENGTH];
    snprintf(formattedWrongAnswersFilename, MAX_FILE_NAME_LENGTH, "%s_wrong_answers.txt", username);

    char questions[MAX_QUESTIONS][MAX_QUESTION_LENGTH];
    char answers[MAX_QUESTIONS][MAX_ANSWER_LENGTH];
    char hints[MAX_QUESTIONS][MAX_HINT_LENGTH];
    char numbers[MAX_NUMBERS][MAX_QUESTION_LENGTH];
    char ian[MAX_QUESTIONS][MAX_EXPLANATION_LENGTH];
    int numQuestions = 0;
    int numNumbers = 0;
    int numExplanations = 0;
    int hintcount = 3;
    int problemnumber = 1;

    while (1) {
        readQuestionAndAnswer(questionFilename, answerFilename, hintFilename, questions, answers, hints, &numQuestions);
        readNumbers(numberFilename, numbers, &numNumbers);
        readExplanations(ianFilename, ian, &numExplanations);

        if (numQuestions == 0 || numNumbers == 0) {
            gotoxy(80, 25);
            printf("문제 파일 또는 정답 파일을 읽을 수 없습니다.\n");
            result.isError = 1;
            return result;
        }

        srand(time(NULL));

        char userAnswer[MAX_ANSWER_LENGTH];
        char exitInput[MAX_ANSWER_LENGTH] = "q";
        char exitInput2[MAX_ANSWER_LENGTH] = "Q";
        char hintInput[MAX_ANSWER_LENGTH] = "h";
        char hintInput2[MAX_ANSWER_LENGTH] = "H";

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

            gotoxy(165, 5);
            printf("Hint (h) 남은 힌트 수 : %d", hintcount);

            gotoxy(50, 15);
            printf("문제: %s\n", questions[currentQuestionIndex]);
            gotoxy(85, 10);
            printf("문제 번호 : %d", problemnumber);
            problemnumber++;

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
                printf("답(종료 'q', 힌트 'h'): ");

                scanf("%s", userAnswer);

                if (strcmp(userAnswer, exitInput) == 0 || strcmp(userAnswer, exitInput2) == 0) {
                    gotoxy(80, 36);
                    printf("문제 종료\n");
                    Sleep(1000);
                    cls;
                    return result;
                }
                else if (strcmp(userAnswer, hintInput) == 0 || strcmp(userAnswer, hintInput2) == 0) {
                    if (hintcount > 0) {
                        displayHint(hints, currentQuestionIndex);
                        hintcount--;
                        gotoxy(165, 5);
                        printf("Hint (h) 남은 힌트 수 : %d", hintcount);
                        gotoxy(80, 35);
                    }
                    else {
                        gotoxy(80, 37);
                        printf("남은 힌트 수가 없습니다.");
                        Sleep(1000);
                        gotoxy(80, 37);
                        printf("                        ");
                    }
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
                            int a = WrongAnswers(currentQuestionIndex, answers, ian);
                            result.wrongCount++;
                            saveWrongAnswer(wrongAnswersFilename, questions[currentQuestionIndex], answers[currentQuestionIndex], userAnswer, ian[currentQuestionIndex]);
                            if (a == 3) {
                                cls;
                                return result;
                            }
                            Sleep(1000);
                            cls;
                        }
                        else {
                            int a = WrongAnswers(currentQuestionIndex, answers, ian);
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
struct Result questions3(struct Member loginUser, const char* fileName, const char* fileName2, const char* fileName3, const char* fileName5, const char* username) {
    cls;
    struct Result result = { 0 };
    char questionFilename[MAX_FILE_NAME_LENGTH];
    char answerFilename[MAX_FILE_NAME_LENGTH];
    char hintFilename[MAX_FILE_NAME_LENGTH];
    char ianFilename[MAX_FILE_NAME_LENGTH];
    strcpy(questionFilename, fileName);
    strcpy(answerFilename, fileName2);
    strcpy(hintFilename, fileName3);
    strcpy(ianFilename, fileName5);
    struct Member loggedInUser;
    loggedInUser = loginUser;
    char* wrongAnswersFilename = generateWrongAnswersFilename(loggedInUser.username);

    char formattedWrongAnswersFilename[MAX_FILE_NAME_LENGTH];
    snprintf(formattedWrongAnswersFilename, MAX_FILE_NAME_LENGTH, "%s_wrong_answers.txt", username);

    char questions[MAX_QUESTIONS][MAX_QUESTION_LENGTH];
    char answers[MAX_QUESTIONS][MAX_ANSWER_LENGTH];
    char hints[MAX_QUESTIONS][MAX_HINT_LENGTH];
    char ian[MAX_QUESTIONS][MAX_EXPLANATION_LENGTH];
    int numQuestions = 0;
    int numExplanations = 0;
    int hintcount = 1;
    int problemnumber = 1;

    while (1) {
        readQuestionAndAnswer(questionFilename, answerFilename, hintFilename, questions, answers, hints, &numQuestions);
        readExplanations(ianFilename, ian, &numExplanations);

        if (numQuestions == 0 || numExplanations == 0) {
            gotoxy(80, 25);
            printf("문제 파일 또는 정답 파일을 읽을 수 없습니다.\n");
            result.isError = 1;
            return result;
        }

        srand(time(NULL));

        char userAnswer[MAX_ANSWER_LENGTH];
        char exitInput[MAX_ANSWER_LENGTH] = "q";
        char exitInput2[MAX_ANSWER_LENGTH] = "Q";
        char hintInput[MAX_ANSWER_LENGTH] = "h";
        char hintInput2[MAX_ANSWER_LENGTH] = "H";

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

            gotoxy(165, 5);
            printf("Hint (h) 남은 힌트 수 : %d", hintcount);

            gotoxy(50, 15);
            printf("문제: %s\n", questions[currentQuestionIndex]);
            gotoxy(85, 10);
            printf("문제 번호 : %d", problemnumber);
            problemnumber++;

            while (1) {
                gotoxy(80, 35);
                printf("답(종료 'q', 힌트 'h'): ");

                scanf("%s", userAnswer);

                if (strcmp(userAnswer, exitInput) == 0 || strcmp(userAnswer, exitInput2) == 0) {
                    gotoxy(80, 36);
                    printf("문제 종료\n");
                    Sleep(1000);
                    cls;
                    return result;
                }
                else if (strcmp(userAnswer, hintInput) == 0 || strcmp(userAnswer, hintInput2) == 0) {
                    if (hintcount > 0) {
                        displayHint(hints, currentQuestionIndex);
                        hintcount--;
                        gotoxy(165, 5);
                        printf("Hint (h) 남은 힌트 수 : %d", hintcount);
                        gotoxy(80, 35);
                    }
                    else {
                        gotoxy(80, 37);
                        printf("남은 힌트 수가 없습니다.");
                        Sleep(1000);
                        gotoxy(80, 37);
                        printf("                        ");
                    }
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
                            int a = WrongAnswers(currentQuestionIndex, answers, ian);
                            result.wrongCount++;
                            saveWrongAnswer(wrongAnswersFilename, questions[currentQuestionIndex], answers[currentQuestionIndex], userAnswer, ian[currentQuestionIndex]);
                            if (a == 3) {
                                cls;
                                return result;
                            }
                            Sleep(1000);
                            cls;
                        }
                        else {
                            int a = WrongAnswers(currentQuestionIndex, answers, ian);
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
void saveWrongAnswer(char* filename, char question[MAX_QUESTION_LENGTH], char correctAnswer[MAX_ANSWER_LENGTH], char userAnswer[MAX_ANSWER_LENGTH], char ian[MAX_EXPLANATION_LENGTH]) {
    FILE* file = fopen(filename, "a");

    if (file != NULL) {
        fprintf(file, "문제: %s\n", question);
        fprintf(file, "정답: %s\n", correctAnswer);
        fprintf(file, "오답: %s\n", userAnswer);
        fprintf(file, "설명: %s\n", ian);
        fprintf(file, "------------------------\n");

        fclose(file);
    }
    else {
        printf("오답 노트 파일에 기록할 수 없습니다.\n");
    }
}
int isAlreadyRecorded(char* filename, char question[MAX_QUESTION_LENGTH]) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return 0;
    }

    char line[MAX_QUESTION_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = 0;
        if (strstr(line, question) != NULL) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}
int compare(const void* a, const void* b) {
    struct Member* memberA = (struct Member*)a;
    struct Member* memberB = (struct Member*)b;

    if (memberA->result.percentage > memberB->result.percentage) {
        return -1;
    }
    else if (memberA->result.percentage < memberB->result.percentage) {
        return 1;
    }
    else {
        if (memberA->result.correctCount > memberB->result.correctCount) {
            return -1;
        }
        else if (memberA->result.correctCount < memberB->result.correctCount) {
            return 1;
        }
        else {
            return 0;
        }
    }
}