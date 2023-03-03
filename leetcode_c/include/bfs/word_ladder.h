/**
 * @file word_ladder.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/word-ladder/
 * @version 0.1
 * @date 2023-03-01
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEETCODE_WORD_LADDER_H
#define LEETCODE_WORD_LADDER_H

#include "../const.h"
#include "../third/uthash.h"

#define EMPTY_POS -1

#define MAX_WORD_LEN (10 + 1)
#define MAX_WORD_LIST_SIZE 5000

typedef struct {
    char word[MAX_WORD_LEN];
    int distance;
} WordWrapper_T;

typedef struct {
    WordWrapper_T* data;
    int head;
    int rear;
    int capacity;
    int curSize;
} MyQueue_T;

MyQueue_T* InitMyQueue(int capacity) {
    MyQueue_T* queuePtr = (MyQueue_T*)calloc(1, sizeof(MyQueue_T));
    queuePtr->data = (WordWrapper_T*)calloc(capacity, sizeof(WordWrapper_T));
    queuePtr->head = EMPTY_POS;
    queuePtr->rear = EMPTY_POS;
    queuePtr->capacity = capacity;
    queuePtr->curSize = 0;

    return queuePtr;
}

void EnMyQueue(MyQueue_T* queuePtr, WordWrapper_T* inVal) {
    if (queuePtr->head == EMPTY_POS) {
        queuePtr->head = 0;
    }
    queuePtr->rear = (queuePtr->rear + 1) % queuePtr->capacity;
    memcpy(&queuePtr->data[queuePtr->rear], inVal, sizeof(WordWrapper_T));

    queuePtr->curSize++;
    return ;
}

void DeMyQueue(MyQueue_T* queuePtr, WordWrapper_T* outVal) {
    memcpy(outVal, &queuePtr->data[queuePtr->head], sizeof(WordWrapper_T));
    if (queuePtr->head == queuePtr->rear) {
        queuePtr->rear = EMPTY_POS;
        queuePtr->head = EMPTY_POS;
    }
    queuePtr->head = (queuePtr->head + 1) % queuePtr->capacity;

    queuePtr->curSize--;
    return ;
}

bool IsFullMyQueue(MyQueue_T* queuePtr) {
    if (queuePtr->curSize == queuePtr->capacity) {
        return true;
    }
    return false;
}

bool IsEmptyMyQueue(MyQueue_T* queuePtr) {
    if (queuePtr->curSize == 0) {
        return true;
    }
    return false;
}

void FreeMyQueue(MyQueue_T* queuePtr) {
    free(queuePtr->data);
    free(queuePtr);
    return ;
}

int CheckDiffWord(char* input1, char* input2) {
    int count = 0;
    for (size_t i = 0; i < strlen(input1); i++) {
        if (input1[i] != input2[i]) {
            count++;
        }
    }

    return count;
}

int BFS(char* beginWord, char* endWord, char** wordList,
    int wordListSize, MyQueue_T* queuePtr) {
    int curDistance = 0;
    WordWrapper_T curWord;
    WordWrapper_T inputWord;

    bool* flagArray = (bool*)calloc(wordListSize, sizeof(bool));

    inputWord.distance = 0;
    memcpy(inputWord.word, beginWord, strlen(beginWord) + 1);
    EnMyQueue(queuePtr, &inputWord);

    while (!IsEmptyMyQueue(queuePtr)) {
        DeMyQueue(queuePtr, &curWord);
        curDistance = curWord.distance;

        if (CheckDiffWord(curWord.word, endWord) == 0) {
            free(flagArray);
            return curDistance + 1;
        }

        for (size_t i = 0; i < wordListSize; i++) {
            if ((flagArray[i] == false) &&
                (CheckDiffWord(curWord.word, wordList[i]) == 1)) {
                flagArray[i] = true;
                inputWord.distance = curDistance + 1;
                memcpy(inputWord.word, wordList[i], strlen(wordList[i]) + 1);
                EnMyQueue(queuePtr, &inputWord);
            }
        }

    }

    free(flagArray);

    return 0;
}

int ladderLength(char * beginWord, char * endWord, char ** wordList, int wordListSize){
    if (beginWord == NULL || endWord == NULL || wordList == NULL || wordListSize == 0) {
        return 0;
    }

    MyQueue_T* queuePtr = InitMyQueue(MAX_WORD_LIST_SIZE);

    int retAns = BFS(beginWord, endWord, wordList, wordListSize, queuePtr);

    FreeMyQueue(queuePtr);

    return retAns;
}

#endif