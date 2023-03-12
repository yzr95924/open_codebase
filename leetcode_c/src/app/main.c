#include "../../include/prefix_sum/make_sum_divisible_by_p.h"

int main(int argc, char* argv[]) {
    int key_1 = 1;
    int val_1 = 2;
    int key_2 = 1;
    int val_2 = 3;

    int nums[] = {3,1,4,2};
    int p = 6;

    int ret = minSubarray(nums, sizeof(nums) / sizeof(int), p);
    printf("ret: %d\n", ret);

    return 0;
}