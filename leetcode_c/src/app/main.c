#include "../../include/str/compare_version.h"

int main(int argc, char* argv[]) {
    /* code */
    char version1[] = "1.0.1";
    char version2[] = "1";

    int ret = compareVersion(version1, version2);
    printf("ret: %d\n", ret);
    // int posArray[] = {10,8,0,5,3};
    // int speedArray[] = {2,4,1,1,3};
    // int posSize = sizeof(posArray) / sizeof(int);
    // int speedSize = sizeof(speedArray) / sizeof(int);
    // int ret = carFleet(12, posArray, posSize, speedArray, speedSize);
    // printf("ret: %d\n", ret);
    return 0;
}

// #include <string.h>
// #include <stdio.h>

// int main()
// {
//     char str[80] = "This is - www.runoob.com - website";
//     const char s[2] = "-";
//     char *token;

//     /* 获取第一个子字符串 */
//     token = strtok(str, s);

//     /* 继续获取其他的子字符串 */
//     while (token != NULL)
//     {
//         printf("%s\n", token);

//         token = strtok(NULL, s);
//     }
//     printf("\n");
//     for (int i = 0; i < 34;i++)
//         printf("%c", str[i]);

//     return (0);
// }