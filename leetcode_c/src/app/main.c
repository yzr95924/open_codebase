#include "../../include/my_hash_type.h"

int main(int argc, char* argv[]) {
    HashTblItem_T* hashTable = NULL;
    int key1 = 1;
    int val2 = 2;

    InsertHashTable(&hashTable, key1, val2);

    int outputVal;
    if (GetHashTable(hashTable, key1, &outputVal)) {
        printf("find the item: %d\n", outputVal);
    } else {
        printf("cannot find the item.\n");
    }

    FreeHashTable(hashTable);

    return 0;
}