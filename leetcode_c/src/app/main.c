#include "../../include/bfs/bus_routes.h"

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

    int realRoutes[][3] = {{1,2,7},{3,6,7}};
    int source = 1;
    int target = 6;

    int** routes = (int**)ConvertFixedTwoArrayToPtr((uint8_t*)&realRoutes[0][0],
        2, 3, sizeof(int));
    int routeCol[] = {3, 3};

    numBusesToDestination(routes, 2, routeCol, source, target);

    FreeFixedTwoArray((uint8_t**)routes, 2);

    return 0;
}