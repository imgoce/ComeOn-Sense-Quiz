/* 헤더 선언 */
#pragma once
#include "main.h"

/* 함수 선언 */
void signup(); //회원가입
struct Member login(); //로그인
int isUsernameExists(const char* username); //사용자가 존재하는 지 판단
struct Result questions(struct Member loginUser, const char* fileName, const char* fileName2, const char* fileName3, const char* fileName5, const char* username); //OX문제
struct Result questions2(struct Member loginUser, const char* fileName, const char* fileName2, const char* fileName3, const char* fileName4, const char* fileName5, const char* username); //주관식 문제
struct Result questions3(struct Member loginUser, const char* fileName, const char* fileName2, const char* fileName3, const char* fileName5, const char* username); //주관식 문제
void readQuestionAndAnswer(char* questionFilename, char* answerFilename, char* hintFilename, char questions[][MAX_QUESTION_LENGTH], char answers[][MAX_ANSWER_LENGTH], char hints[][MAX_HINT_LENGTH], int* numQuestions); //문제를 파일에서 불러옴
void readNumbers(char* filename, char numbers[][MAX_QUESTION_LENGTH], int* numNumbers); //객관식 문제 읽어옴
void printNumbers(char numbers[][MAX_QUESTION_LENGTH], int start, int end); //객관식 문제 출력
void readExplanations(char* filename, char explanations[][MAX_EXPLANATION_LENGTH], int* numExplanations); //설명을 읽어옴
bool checkAnswer(int questionIndex, char userAnswer[MAX_ANSWER_LENGTH], char answers[][MAX_ANSWER_LENGTH]); //정답인지 확인
char* generateWrongAnswersFilename(const char* username); //오답노트 파일 이름 생성
void saveWrongAnswer(char* filename, char question[MAX_QUESTION_LENGTH], char correctAnswer[MAX_ANSWER_LENGTH], char userAnswer[MAX_ANSWER_LENGTH]); //오답노트 저장
int isAlreadyRecorded(char* filename, char question[MAX_QUESTION_LENGTH]); //오답노트에 이미 존재하는 문제인가?
int compare(const void* a, const void* b); //비교
