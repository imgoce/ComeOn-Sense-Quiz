#include "main.h"
#include "util.h"
#include "function.h"
#include "screen.h"

int main() {
    init();
    struct Member data;
    const char* fileName = NULL;
    const char* fileName2 = NULL;
    const char* fileName3 = NULL;
    const char* fileName4 = NULL;
    const char* fileName5 = NULL;
    struct Member loginUser;
    int i;

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
                    int n = mainDraw(data, &data);
                    if (n == 1) {
                        cls;
                        gotoxy(85, 25);
                        printf("프로그램 종료");
                        exit(0);
                    }
                    if (n == 2)
                        break;
                    if (n == 3) {
                        cls;
                        displayWrongAnswers(loginUser);
                    }
                    if (n == 4) {
                        cls;
                        solution();
                    }

                    char fileCategory[10];
                    char fileDifficulty[30];
                    char filename[100];

                    if (n == 0) {
                        //시사
                        cls;
                        gotoxy(95, 25);
                        printf("시사");
                        strcpy(fileCategory, "시사");
                        Sleep(1000);
                        i = level();
                        if (i == 0) {
                            fileName = "preview_easy.txt";
                            fileName2 = "preview_easy_answer.txt";
                            fileName3 = "preview_easy_hint.txt";
                            fileName5 = "preview_easy_ian.txt";
                            strcpy(fileDifficulty, "easy");
                            sprintf(filename, "%s_%s_%s.txt", loginUser.username, fileCategory, fileDifficulty);

                            struct Result result = questions(loginUser, fileName, fileName2, fileName3, fileName5, data.username);
                            if (result.isError) {
                                gotoxy(80, 25);
                                printf("Error executing questions function.\n");
                                return 1;
                            }
                            int r = printResult(result, loginUser);
                            float totalQuestions = (float)(result.correctCount + result.wrongCount);
                            float correctPercentage = (result.correctCount / totalQuestions) * 100;
                            char grade2 = '\0';
                            if (result.correctCount == totalQuestions)
                                grade2 = 'S';
                            else if (correctPercentage >= 80)
                                grade2 = 'A';
                            else if (correctPercentage >= 60)
                                grade2 = 'B';
                            else if (correctPercentage >= 40)
                                grade2 = 'C';
                            else if (correctPercentage >= 20)
                                grade2 = 'D';
                            else
                                grade2 = 'E';

                            FILE* file = fopen(filename, "w");

                            fprintf(file, "%s(%s) : %c(정답 : %d, 오답 : %d)", fileCategory, fileDifficulty, grade2, result.correctCount, result.wrongCount);
                            fclose(file);
                            if (r == 3) {
                                cls;
                                displayWrongAnswers(loginUser);
                            }
                            cls;
                        }
                        else if (i == 3) {
                            fileName = "preview_normal.txt";
                            fileName2 = "preview_normal_answer.txt";
                            fileName3 = "preview_normal_hint.txt";
                            fileName4 = "preview_normal_number.txt";
                            fileName5 = "preview_normal_ian.txt";
                            strcpy(fileDifficulty, "normal");
                            sprintf(filename, "%s_%s_%s.txt", loginUser.username, fileCategory, fileDifficulty);

                            struct Result result = questions2(loginUser, fileName, fileName2, fileName3, fileName4, fileName5, data.username);
                            if (result.isError) {
                                gotoxy(80, 25);
                                printf("Error executing questions function.\n");
                                return 1;
                            }
                            int r = printResult(result, loginUser);
                            float totalQuestions = (float)(result.correctCount + result.wrongCount);
                            float correctPercentage = (result.correctCount / totalQuestions) * 100;
                            char grade2 = '\0';
                            if (result.correctCount == totalQuestions)
                                grade2 = 'S';
                            else if (correctPercentage >= 80)
                                grade2 = 'A';
                            else if (correctPercentage >= 60)
                                grade2 = 'B';
                            else if (correctPercentage >= 40)
                                grade2 = 'C';
                            else if (correctPercentage >= 20)
                                grade2 = 'D';
                            else
                                grade2 = 'E';

                            FILE* file = fopen(filename, "w");

                            fprintf(file, "%s(%s) : %c(정답 : %d, 오답 : %d)", fileCategory, fileDifficulty, grade2, result.correctCount, result.wrongCount);
                            fclose(file);
                            if (r == 3) {
                                cls;
                                displayWrongAnswers(loginUser);
                            }
                            cls;
                        }
                        else if (i == 6) {
                            fileName = "preview_hard.txt";
                            fileName2 = "preview_hard_answer.txt";
                            fileName3 = "preview_hard_hint.txt";
                            fileName5 = "preview_hard_ian.txt";
                            strcpy(fileDifficulty, "hard");
                            sprintf(filename, "%s_%s_%s.txt", loginUser.username, fileCategory, fileDifficulty);

                            struct Result result = questions3(loginUser, fileName, fileName2, fileName3, fileName5, data.username);
                            if (result.isError) {
                                gotoxy(80, 25);
                                printf("Error executing questions function.\n");
                                return 1;
                            }
                            int r = printResult(result, loginUser);
                            float totalQuestions = (float)(result.correctCount + result.wrongCount);
                            float correctPercentage = (result.correctCount / totalQuestions) * 100;
                            char grade2 = '\0';
                            if (result.correctCount == totalQuestions)
                                grade2 = 'S';
                            else if (correctPercentage >= 80)
                                grade2 = 'A';
                            else if (correctPercentage >= 60)
                                grade2 = 'B';
                            else if (correctPercentage >= 40)
                                grade2 = 'C';
                            else if (correctPercentage >= 20)
                                grade2 = 'D';
                            else
                                grade2 = 'E';

                            FILE* file = fopen(filename, "w");

                            fprintf(file, "%s(%s) : %c(정답 : %d, 오답 : %d)", fileCategory, fileDifficulty, grade2, result.correctCount, result.wrongCount);
                            fclose(file);
                            if (r == 3) {
                                cls;
                                displayWrongAnswers(loginUser);
                            }
                            cls;
                        }
                        else if (i == 10)
                            continue;
                    }
                    else if (n == 25) {
                        //국가
                        cls;
                        gotoxy(95, 25);
                        printf("국가");
                        strcpy(fileCategory, "국가");
                        Sleep(1000);
                        i = level();
                        if (i == 0) {
                            fileName = "country_easy.txt";
                            fileName2 = "country_easy_answer.txt";
                            fileName3 = "country_easy_hint.txt";
                            fileName5 = "country_easy_ian.txt";
                            strcpy(fileDifficulty, "easy");
                            sprintf(filename, "%s_%s_%s.txt", loginUser.username, fileCategory, fileDifficulty);

                            struct Result result = questions(loginUser, fileName, fileName2, fileName3, fileName5, data.username);
                            if (result.isError) {
                                gotoxy(80, 25);
                                printf("Error executing questions function.\n");
                                return 1;
                            }
                            int r = printResult(result, loginUser);
                            float totalQuestions = (float)(result.correctCount + result.wrongCount);
                            float correctPercentage = (result.correctCount / totalQuestions) * 100;
                            char grade2 = '\0';
                            if (result.correctCount == totalQuestions)
                                grade2 = 'S';
                            else if (correctPercentage >= 80)
                                grade2 = 'A';
                            else if (correctPercentage >= 60)
                                grade2 = 'B';
                            else if (correctPercentage >= 40)
                                grade2 = 'C';
                            else if (correctPercentage >= 20)
                                grade2 = 'D';
                            else
                                grade2 = 'E';

                            FILE* file = fopen(filename, "w");

                            fprintf(file, "%s(%s) : %c(정답 : %d, 오답 : %d)", fileCategory, fileDifficulty, grade2, result.correctCount, result.wrongCount);
                            fclose(file);
                            if (r == 3) {
                                cls;
                                displayWrongAnswers(loginUser);
                            }
                            cls;
                        }
                        else if (i == 3) {
                            fileName = "country_normal.txt";
                            fileName2 = "country_normal_answer.txt";
                            fileName3 = "country_normal_hint.txt";
                            fileName4 = "country_normal_number.txt";
                            fileName5 = "country_normal_ian.txt";
                            strcpy(fileDifficulty, "normal");
                            sprintf(filename, "%s_%s_%s.txt", loginUser.username, fileCategory, fileDifficulty);

                            struct Result result = questions2(loginUser, fileName, fileName2, fileName3, fileName4, fileName5, data.username);
                            if (result.isError) {
                                gotoxy(80, 25);
                                printf("Error executing questions function.\n");
                                return 1;
                            }
                            int r = printResult(result, loginUser);
                            float totalQuestions = (float)(result.correctCount + result.wrongCount);
                            float correctPercentage = (result.correctCount / totalQuestions) * 100;
                            char grade2 = '\0';
                            if (result.correctCount == totalQuestions)
                                grade2 = 'S';
                            else if (correctPercentage >= 80)
                                grade2 = 'A';
                            else if (correctPercentage >= 60)
                                grade2 = 'B';
                            else if (correctPercentage >= 40)
                                grade2 = 'C';
                            else if (correctPercentage >= 20)
                                grade2 = 'D';
                            else
                                grade2 = 'E';

                            FILE* file = fopen(filename, "w");

                            fprintf(file, "%s(%s) : %c(정답 : %d, 오답 : %d)", fileCategory, fileDifficulty, grade2, result.correctCount, result.wrongCount);
                            fclose(file);
                            if (r == 3) {
                                cls;
                                displayWrongAnswers(loginUser);
                            }
                            cls;
                        }
                        else if (i == 6) {
                            fileName = "country_hard.txt";
                            fileName2 = "country_hard_answer.txt";
                            fileName3 = "country_hard_hint.txt";
                            fileName5 = "country_hard_ian.txt";
                            strcpy(fileDifficulty, "hard");
                            sprintf(filename, "%s_%s_%s.txt", loginUser.username, fileCategory, fileDifficulty);

                            struct Result result = questions3(loginUser, fileName, fileName2, fileName3, fileName5, data.username);
                            if (result.isError) {
                                gotoxy(80, 25);
                                printf("Error executing questions function.\n");
                                return 1;
                            }
                            int r = printResult(result, loginUser);
                            float totalQuestions = (float)(result.correctCount + result.wrongCount);
                            float correctPercentage = (result.correctCount / totalQuestions) * 100;
                            char grade2 = '\0';
                            if (result.correctCount == totalQuestions)
                                grade2 = 'S';
                            else if (correctPercentage >= 80)
                                grade2 = 'A';
                            else if (correctPercentage >= 60)
                                grade2 = 'B';
                            else if (correctPercentage >= 40)
                                grade2 = 'C';
                            else if (correctPercentage >= 20)
                                grade2 = 'D';
                            else
                                grade2 = 'E';

                            FILE* file = fopen(filename, "w");

                            fprintf(file, "%s(%s) : %c(정답 : %d, 오답 : %d)", fileCategory, fileDifficulty, grade2, result.correctCount, result.wrongCount);
                            fclose(file);
                            if (r == 3) {
                                cls;
                                displayWrongAnswers(loginUser);
                            }
                            cls;
                        }
                        else if (i == 10)
                            continue;
                    }
                    else if (n == 50) {
                        //인물
                        cls;
                        gotoxy(95, 25);
                        printf("인물");
                        strcpy(fileCategory, "인물");
                        Sleep(1000);
                        i = level();
                        if (i == 0) {
                            fileName = "character_easy.txt";
                            fileName2 = "character_easy_answer.txt";
                            fileName3 = "character_easy_hint.txt";
                            fileName5 = "character_easy_ian.txt";
                            strcpy(fileDifficulty, "easy");
                            sprintf(filename, "%s_%s_%s.txt", loginUser.username, fileCategory, fileDifficulty);

                            struct Result result = questions(loginUser, fileName, fileName2, fileName3, fileName5, data.username);
                            if (result.isError) {
                                gotoxy(80, 25);
                                printf("Error executing questions function.\n");
                                return 1;
                            }
                            int r = printResult(result, loginUser);
                            float totalQuestions = (float)(result.correctCount + result.wrongCount);
                            float correctPercentage = (result.correctCount / totalQuestions) * 100;
                            char grade2 = '\0';
                            if (result.correctCount == totalQuestions)
                                grade2 = 'S';
                            else if (correctPercentage >= 80)
                                grade2 = 'A';
                            else if (correctPercentage >= 60)
                                grade2 = 'B';
                            else if (correctPercentage >= 40)
                                grade2 = 'C';
                            else if (correctPercentage >= 20)
                                grade2 = 'D';
                            else
                                grade2 = 'E';

                            FILE* file = fopen(filename, "w");
                       
                            fprintf(file, "%s(%s) : %c(정답 : %d, 오답 : %d)", fileCategory, fileDifficulty, grade2, result.correctCount, result.wrongCount);
                            fclose(file);
                            if (r == 3) {
                                cls;
                                displayWrongAnswers(loginUser);
                            }
                            cls;
                        }
                        else if (i == 3) {
                            fileName = "character_normal.txt";
                            fileName2 = "character_normal_answer.txt";
                            fileName3 = "character_normal_hint.txt";
                            fileName4 = "character_normal_number.txt";
                            fileName5 = "character_normal_ian.txt";
                            strcpy(fileDifficulty, "normal");
                            sprintf(filename, "%s_%s_%s.txt", loginUser.username, fileCategory, fileDifficulty);

                            struct Result result = questions2(loginUser, fileName, fileName2, fileName3, fileName4, fileName5, data.username);
                            if (result.isError) {
                                gotoxy(80, 25);
                                printf("Error executing questions function.\n");
                                return 1;
                            }
                            int r = printResult(result, loginUser);
                            float totalQuestions = (float)(result.correctCount + result.wrongCount);
                            float correctPercentage = (result.correctCount / totalQuestions) * 100;
                            char grade2 = '\0';
                            if (result.correctCount == totalQuestions)
                                grade2 = 'S';
                            else if (correctPercentage >= 80)
                                grade2 = 'A';
                            else if (correctPercentage >= 60)
                                grade2 = 'B';
                            else if (correctPercentage >= 40)
                                grade2 = 'C';
                            else if (correctPercentage >= 20)
                                grade2 = 'D';
                            else
                                grade2 = 'E';

                            FILE* file = fopen(filename, "w");

                            fprintf(file, "%s(%s) : %c(정답 : %d, 오답 : %d)", fileCategory, fileDifficulty, grade2, result.correctCount, result.wrongCount);
                            fclose(file);
                            if (r == 3) {
                                cls;
                                displayWrongAnswers(loginUser);
                            }
                            cls;
                        }
                        else if (i == 6) {
                            fileName = "character_hard.txt";
                            fileName2 = "character_hard_answer.txt";
                            fileName3 = "character_hard_hint.txt";
                            fileName5 = "character_hard_ian.txt";
                            strcpy(fileDifficulty, "hard");
                            sprintf(filename, "%s_%s_%s.txt", loginUser.username, fileCategory, fileDifficulty);

                            struct Result result = questions3(loginUser, fileName, fileName2, fileName3, fileName5, data.username);
                            if (result.isError) {
                                gotoxy(80, 25);
                                printf("Error executing questions function.\n");
                                return 1;
                            }
                            int r = printResult(result, loginUser);
                            float totalQuestions = (float)(result.correctCount + result.wrongCount);
                            float correctPercentage = (result.correctCount / totalQuestions) * 100;
                            char grade2 = '\0';
                            if (result.correctCount == totalQuestions)
                                grade2 = 'S';
                            else if (correctPercentage >= 80)
                                grade2 = 'A';
                            else if (correctPercentage >= 60)
                                grade2 = 'B';
                            else if (correctPercentage >= 40)
                                grade2 = 'C';
                            else if (correctPercentage >= 20)
                                grade2 = 'D';
                            else
                                grade2 = 'E';

                            FILE* file = fopen(filename, "w");

                            fprintf(file, "%s(%s) : %c(정답 : %d, 오답 : %d)", fileCategory, fileDifficulty, grade2, result.correctCount, result.wrongCount);
                            fclose(file);
                            if (r == 3) {
                                cls;
                                displayWrongAnswers(loginUser);
                            }
                            cls;
                        }
                        else if (i == 10)
                            continue;
                    }
                    else if (n == 75) {
                        //과학
                        cls;
                        gotoxy(95, 25);
                        printf("과학");
                        strcpy(fileCategory, "과학");
                        Sleep(1000);
                        i = level();
                        if (i == 0) {
                            fileName = "science_easy.txt";
                            fileName2 = "science_easy_answer.txt";
                            fileName3 = "science_easy_hint.txt";
                            fileName5 = "science_easy_ian.txt";
                            strcpy(fileDifficulty, "easy");
                            sprintf(filename, "%s_%s_%s.txt", loginUser.username, fileCategory, fileDifficulty);

                            struct Result result = questions(loginUser, fileName, fileName2, fileName3, fileName5, data.username);
                            if (result.isError) {
                                gotoxy(80, 25);
                                printf("Error executing questions function.\n");
                                return 1;
                            }
                            int r = printResult(result, loginUser);
                            float totalQuestions = (float)(result.correctCount + result.wrongCount);
                            float correctPercentage = (result.correctCount / totalQuestions) * 100;
                            char grade2 = '\0';
                            if (result.correctCount == totalQuestions)
                                grade2 = 'S';
                            else if (correctPercentage >= 80)
                                grade2 = 'A';
                            else if (correctPercentage >= 60)
                                grade2 = 'B';
                            else if (correctPercentage >= 40)
                                grade2 = 'C';
                            else if (correctPercentage >= 20)
                                grade2 = 'D';
                            else
                                grade2 = 'E';

                            FILE* file = fopen(filename, "w");

                            fprintf(file, "%s(%s) : %c(정답 : %d, 오답 : %d)", fileCategory, fileDifficulty, grade2, result.correctCount, result.wrongCount);
                            fclose(file);
                            if (r == 3) {
                                cls;
                                displayWrongAnswers(loginUser);
                            }
                            cls;
                        }
                        else if (i == 3) {
                            fileName = "science_normal.txt";
                            fileName2 = "science_normal_answer.txt";
                            fileName3 = "science_normal_hint.txt";
                            fileName4 = "science_normal_number.txt";
                            fileName5 = "science_normal_ian.txt";
                            strcpy(fileDifficulty, "normal");
                            sprintf(filename, "%s_%s_%s.txt", loginUser.username, fileCategory, fileDifficulty);

                            struct Result result = questions2(loginUser, fileName, fileName2, fileName3, fileName4, fileName5, data.username);
                            if (result.isError) {
                                gotoxy(80, 25);
                                printf("Error executing questions function.\n");
                                return 1;
                            }
                            int r = printResult(result, loginUser);
                            float totalQuestions = (float)(result.correctCount + result.wrongCount);
                            float correctPercentage = (result.correctCount / totalQuestions) * 100;
                            char grade2 = '\0';
                            if (result.correctCount == totalQuestions)
                                grade2 = 'S';
                            else if (correctPercentage >= 80)
                                grade2 = 'A';
                            else if (correctPercentage >= 60)
                                grade2 = 'B';
                            else if (correctPercentage >= 40)
                                grade2 = 'C';
                            else if (correctPercentage >= 20)
                                grade2 = 'D';
                            else
                                grade2 = 'E';

                            FILE* file = fopen(filename, "w");

                            fprintf(file, "%s(%s) : %c(정답 : %d, 오답 : %d)", fileCategory, fileDifficulty, grade2, result.correctCount, result.wrongCount);
                            fclose(file);
                            if (r == 3) {
                                cls;
                                displayWrongAnswers(loginUser);
                            }
                            cls;
                        }
                        else if (i == 6) {
                            fileName = "science_hard.txt";
                            fileName2 = "science_hard_answer.txt";
                            fileName3 = "science_hard_hint.txt";
                            fileName5 = "science_hard_ian.txt";
                            strcpy(fileDifficulty, "hard");
                            sprintf(filename, "%s_%s_%s.txt", loginUser.username, fileCategory, fileDifficulty);

                            struct Result result = questions3(loginUser, fileName, fileName2, fileName3, fileName5, data.username);
                            if (result.isError) {
                                gotoxy(80, 25);
                                printf("Error executing questions function.\n");
                                return 1;
                            }
                            int r = printResult(result, loginUser);
                            float totalQuestions = (float)(result.correctCount + result.wrongCount);
                            float correctPercentage = (result.correctCount / totalQuestions) * 100;
                            char grade2 = '\0';
                            if (result.correctCount == totalQuestions)
                                grade2 = 'S';
                            else if (correctPercentage >= 80)
                                grade2 = 'A';
                            else if (correctPercentage >= 60)
                                grade2 = 'B';
                            else if (correctPercentage >= 40)
                                grade2 = 'C';
                            else if (correctPercentage >= 20)
                                grade2 = 'D';
                            else
                                grade2 = 'E';

                            FILE* file = fopen(filename, "w");

                            fprintf(file, "%s(%s) : %c(정답 : %d, 오답 : %d)", fileCategory, fileDifficulty, grade2, result.correctCount, result.wrongCount);
                            fclose(file);
                            if (r == 3) {
                                cls;
                                displayWrongAnswers(loginUser);
                            }
                            cls;
                        }
                        else if (i == 10)
                            continue;
                    }
                    else if (n == 100) {
                        //역사
                        cls;
                        gotoxy(95, 25);
                        printf("역사");
                        strcpy(fileCategory, "역사");
                        Sleep(1000);
                        i = level();
                        if (i == 0) {
                            fileName = "history_easy.txt";
                            fileName2 = "history_easy_answer.txt";
                            fileName3 = "history_easy_hint.txt";
                            fileName5 = "history_easy_ian.txt";
                            strcpy(fileDifficulty, "easy");
                            sprintf(filename, "%s_%s_%s.txt", loginUser.username, fileCategory, fileDifficulty);

                            struct Result result = questions(loginUser, fileName, fileName2, fileName3, fileName5, data.username);
                            if (result.isError) {
                                gotoxy(80, 25);
                                printf("Error executing questions function.\n");
                                return 1;
                            }
                            int r = printResult(result, loginUser);
                            float totalQuestions = (float)(result.correctCount + result.wrongCount);
                            float correctPercentage = (result.correctCount / totalQuestions) * 100;
                            char grade2 = '\0';
                            if (result.correctCount == totalQuestions)
                                grade2 = 'S';
                            else if (correctPercentage >= 80)
                                grade2 = 'A';
                            else if (correctPercentage >= 60)
                                grade2 = 'B';
                            else if (correctPercentage >= 40)
                                grade2 = 'C';
                            else if (correctPercentage >= 20)
                                grade2 = 'D';
                            else
                                grade2 = 'E';

                            FILE* file = fopen(filename, "w");

                            fprintf(file, "%s(%s) : %c(정답 : %d, 오답 : %d)", fileCategory, fileDifficulty, grade2, result.correctCount, result.wrongCount);
                            fclose(file);
                            if (r == 3) {
                                cls;
                                displayWrongAnswers(loginUser);
                            }
                            cls;
                        }
                        else if (i == 3) {
                            fileName = "history_normal.txt";
                            fileName2 = "history_normal_answer.txt";
                            fileName3 = "history_normal_hint.txt";
                            fileName4 = "history_normal_number.txt";
                            fileName5 = "history_normal_ian.txt";
                            strcpy(fileDifficulty, "noraml");
                            sprintf(filename, "%s_%s_%s.txt", loginUser.username, fileCategory, fileDifficulty);

                            struct Result result = questions2(loginUser, fileName, fileName2, fileName3, fileName4, fileName5, data.username);
                            if (result.isError) {
                                gotoxy(80, 25);
                                printf("Error executing questions function.\n");
                                return 1;
                            }
                            int r = printResult(result, loginUser);
                            float totalQuestions = (float)(result.correctCount + result.wrongCount);
                            float correctPercentage = (result.correctCount / totalQuestions) * 100;
                            char grade2 = '\0';
                            if (result.correctCount == totalQuestions)
                                grade2 = 'S';
                            else if (correctPercentage >= 80)
                                grade2 = 'A';
                            else if (correctPercentage >= 60)
                                grade2 = 'B';
                            else if (correctPercentage >= 40)
                                grade2 = 'C';
                            else if (correctPercentage >= 20)
                                grade2 = 'D';
                            else
                                grade2 = 'E';

                            FILE* file = fopen(filename, "w");

                            fprintf(file, "%s(%s) : %c(정답 : %d, 오답 : %d)", fileCategory, fileDifficulty, grade2, result.correctCount, result.wrongCount);
                            fclose(file);
                            if (r == 3) {
                                cls;
                                displayWrongAnswers(loginUser);
                            }
                            cls;
                        }
                        else if (i == 6) {
                            fileName = "history_hard.txt";
                            fileName2 = "history_hard_answer.txt";
                            fileName3 = "history_hard_hint.txt";
                            fileName5 = "history_hard_ian.txt";
                            strcpy(fileDifficulty, "hard");
                            sprintf(filename, "%s_%s_%s.txt", loginUser.username, fileCategory, fileDifficulty);

                            struct Result result = questions3(loginUser, fileName, fileName2, fileName3, fileName5, data.username);
                            if (result.isError) {
                                gotoxy(80, 25);
                                printf("Error executing questions function.\n");
                                return 1;
                            }
                            int r = printResult(result, loginUser);
                            float totalQuestions = (float)(result.correctCount + result.wrongCount);
                            float correctPercentage = (result.correctCount / totalQuestions) * 100;
                            char grade2 = '\0';
                            if (result.correctCount == totalQuestions)
                                grade2 = 'S';
                            else if (correctPercentage >= 80)
                                grade2 = 'A';
                            else if (correctPercentage >= 60)
                                grade2 = 'B';
                            else if (correctPercentage >= 40)
                                grade2 = 'C';
                            else if (correctPercentage >= 20)
                                grade2 = 'D';
                            else
                                grade2 = 'E';

                            FILE* file = fopen(filename, "w");

                            fprintf(file, "%s(%s) : %c(정답 : %d, 오답 : %d)", fileCategory, fileDifficulty, grade2, result.correctCount, result.wrongCount);
                            fclose(file);
                            if (r == 3) {
                                cls;
                                displayWrongAnswers(loginUser);
                            }
                            cls;
                        }
                        else if (i == 10)
                            continue;
                    }
                    else if (n == 125) {
                        //영어
                        cls;
                        gotoxy(95, 25);
                        printf("영어");
                        strcpy(fileCategory, "영어");
                        Sleep(1000);
                        i = level();
                        if (i == 0) {
                            fileName = "english_easy.txt";
                            fileName2 = "english_easy_answer.txt";
                            fileName3 = "english_easy_hint.txt";
                            fileName5 = "english_easy_ian.txt";
                            strcpy(fileDifficulty, "easy");
                            sprintf(filename, "%s_%s_%s.txt", loginUser.username, fileCategory, fileDifficulty);

                            struct Result result = questions(loginUser, fileName, fileName2, fileName3, fileName5, data.username);
                            if (result.isError) {
                                gotoxy(80, 25);
                                printf("Error executing questions function.\n");
                                return 1;
                            }
                            int r = printResult(result, loginUser);
                            float totalQuestions = (float)(result.correctCount + result.wrongCount);
                            float correctPercentage = (result.correctCount / totalQuestions) * 100;
                            char grade2 = '\0';
                            if (result.correctCount == totalQuestions)
                                grade2 = 'S';
                            else if (correctPercentage >= 80)
                                grade2 = 'A';
                            else if (correctPercentage >= 60)
                                grade2 = 'B';
                            else if (correctPercentage >= 40)
                                grade2 = 'C';
                            else if (correctPercentage >= 20)
                                grade2 = 'D';
                            else
                                grade2 = 'E';

                            FILE* file = fopen(filename, "w");

                            fprintf(file, "%s(%s) : %c(정답 : %d, 오답 : %d)", fileCategory, fileDifficulty, grade2, result.correctCount, result.wrongCount);
                            fclose(file);
                            if (r == 3) {
                                cls;
                                displayWrongAnswers(loginUser);
                            }
                            cls;
                        }
                        else if (i == 3) {
                            fileName = "english_normal.txt";
                            fileName2 = "english_normal_answer.txt";
                            fileName3 = "english_normal_hint.txt";
                            fileName4 = "english_normal_number.txt";
                            fileName5 = "english_normal_ian.txt";
                            strcpy(fileDifficulty, "normal");
                            sprintf(filename, "%s_%s_%s.txt", loginUser.username, fileCategory, fileDifficulty);

                            struct Result result = questions2(loginUser, fileName, fileName2, fileName3, fileName4, fileName5, data.username);
                            if (result.isError) {
                                gotoxy(80, 25);
                                printf("Error executing questions function.\n");
                                return 1;
                            }
                            int r = printResult(result, loginUser);
                            float totalQuestions = (float)(result.correctCount + result.wrongCount);
                            float correctPercentage = (result.correctCount / totalQuestions) * 100;
                            char grade2 = '\0';
                            if (result.correctCount == totalQuestions)
                                grade2 = 'S';
                            else if (correctPercentage >= 80)
                                grade2 = 'A';
                            else if (correctPercentage >= 60)
                                grade2 = 'B';
                            else if (correctPercentage >= 40)
                                grade2 = 'C';
                            else if (correctPercentage >= 20)
                                grade2 = 'D';
                            else
                                grade2 = 'E';

                            FILE* file = fopen(filename, "w");

                            fprintf(file, "%s(%s) : %c(정답 : %d, 오답 : %d)", fileCategory, fileDifficulty, grade2, result.correctCount, result.wrongCount);
                            fclose(file);
                            if (r == 3) {
                                cls;
                                displayWrongAnswers(loginUser);
                            }
                            cls;
                        }
                        else if (i == 6) {
                            fileName = "english_hard.txt";
                            fileName2 = "english_hard_answer.txt";
                            fileName3 = "english_hard_hint.txt";
                            fileName5 = "english_hard_ian.txt";
                            strcpy(fileDifficulty, "hard");
                            sprintf(filename, "%s_%s_%s.txt", loginUser.username, fileCategory, fileDifficulty);

                            struct Result result = questions3(loginUser, fileName, fileName2, fileName3, fileName5, data.username);
                            if (result.isError) {
                                gotoxy(80, 25);
                                printf("Error executing questions function.\n");
                                return 1;
                            }
                            int r = printResult(result, loginUser);
                            float totalQuestions = (float)(result.correctCount + result.wrongCount);
                            float correctPercentage = (result.correctCount / totalQuestions) * 100;
                            char grade2 = '\0';
                            if (result.correctCount == totalQuestions)
                                grade2 = 'S';
                            else if (correctPercentage >= 80)
                                grade2 = 'A';
                            else if (correctPercentage >= 60)
                                grade2 = 'B';
                            else if (correctPercentage >= 40)
                                grade2 = 'C';
                            else if (correctPercentage >= 20)
                                grade2 = 'D';
                            else
                                grade2 = 'E';

                            FILE* file = fopen(filename, "w");

                            fprintf(file, "%s(%s) : %c(정답 : %d, 오답 : %d)", fileCategory, fileDifficulty, grade2, result.correctCount, result.wrongCount);
                            fclose(file);
                            if (r == 3) {
                                cls;
                                displayWrongAnswers(loginUser);
                            }
                            cls;
                        }
                        else if (i == 10)
                            continue;
                    }
                }
                else {
                    break;
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
            cls;
            gotoxy(85, 25);
            printf("프로그램 종료");
            return 0;
        }
        cls;
    }
    int keyCode = keyControl();

    return 0;
}