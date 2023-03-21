#include "../../include/backtrack/letter_combine_of_phone_num.h"

int main(int argc, char* argv[]) {
    char input[] = "";

    int returnSize = 0;
    char** retStr = letterCombinations(input, &returnSize);

    for (int i = 0; i < returnSize; i++) {
        printf("%s\n", retStr[i]);
        free(retStr[i]);
    }
    free(retStr);

    return 0;
}