#include "../../include/bfs/shortest_bridge.h"

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

    int realRoutes[][5] = {{1,1,1,1,1},{1,0,0,0,1},{1,0,1,0,1},{1,0,0,0,1},{1,1,1,1,1}};
    uint32_t rowSize = 5;
    uint32_t colSize = 5;

    int** routes = (int**)ConvertFixedTwoArrayToPtr((uint8_t*)&realRoutes[0][0],
        rowSize, colSize, sizeof(int));

    int ret = shortestBridge(routes, rowSize, NULL);

    printf("ret: %d\n", ret);

    FreeFixedTwoArray((uint8_t**)routes, rowSize);

    return 0;
}