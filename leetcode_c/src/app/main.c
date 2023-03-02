#include "../../include/bfs/word_ladder.h"

int main(int argc, char* argv[]) {

    // int nums[] = {1, 2};
    // int numsSize = sizeof(nums) / sizeof(int);

    // int retSize;
    // int* retColumnSize;
    // int** retAns;

    // retAns = combine(3, 2, &retSize, &retColumnSize);

    // int retSize = 0;
    // char** retAns = generateParenthesis(1, &retSize);

    // printf("retSize: %d\n", retSize);
    // for (int i = 0; i < retSize; i++) {
    //     printf("%s\n", retAns[i]);
    //     free(retAns[i]);
    // }

    char beginWord[] = "hit";
    char endWord[] = "cog";

    int realWordList[][2] = {{1, 2},{3, 4}};

    int** worldListPtr = (int**)ConvertFixedTwoArrayToPtr((uint8_t*)&realWordList[0][0],
        2, 2, sizeof(int));

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d\n", worldListPtr[i][j]);
        }
    }

    FreeFixedTwoArray((uint8_t**)worldListPtr, 2);

    return 0;
}