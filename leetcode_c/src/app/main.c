#include "../../include/str/zigzag_conversion.h"

int main(int argc, char* argv[]) {
    char input[] = "AB";

    char* retStr = convert(input, 1);

    free(retStr);

    return 0;
}