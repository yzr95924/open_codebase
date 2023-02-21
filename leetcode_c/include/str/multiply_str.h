/**
 * @file multiply_str.h
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://leetcode.cn/problems/multiply-strings/
 * @version 0.1
 * @date 2023-02-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef LEETCODE_MULTIPLY_STR_H
#define LEETCODE_MULTIPLY_STR_H

#include "../const.h"

char * multiply(char* num1, char* num2){
    int num1Size = strlen(num1);
    int num2Size = strlen(num2);

    int* ans = (int*)calloc(num1Size + num2Size, sizeof(int));

    for (int idx1 = num1Size - 1; idx1 >= 0; idx1--) {
        for (int idx2 = num2Size - 1; idx2 >= 0; idx2--) {
            int curRes = (num1[idx1] - '0') * (num2[idx2] - '0');

            int targetIdx1 = idx1 + idx2;
            int targetIdx2 = targetIdx1 + 1;

            int sum = ans[targetIdx2] + curRes;
            ans[targetIdx2] = sum % 10;
            ans[targetIdx1] += sum / 10;
        }
    }

    // count the digit num
    int cnt = 0;
    for (int i = 0; i < num1Size + num2Size; i++) {
        if (ans[i] == 0) {
            cnt++;
        } else {
            break;
        }
    }
    int remainCnt = num1Size + num2Size - cnt;

    // is zero?
    bool isZero = false;
    if (remainCnt == 0) {
        remainCnt = 1;
        isZero = true;
    }

    char* retStr = (char*)calloc(remainCnt + 1, sizeof(char));

    for (int i = cnt; i < num1Size + num2Size; i++) {
        retStr[i - cnt] = '0' + ans[i];
    }
    if (isZero) {
        retStr[0] = '0' + ans[0];
    }

    retStr[remainCnt] = '\0';

    free(ans);

    return retStr;
}

#endif