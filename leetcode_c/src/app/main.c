#include "../../include/my_struct/yzr_dl_list.h"

int main(int argc, char* argv[]) {
    YzrDLList* tmpList = YzrDLListCreate();
    YzrDLListInsertFirst(tmpList, 1, 1);
    YzrDLListInsertFirst(tmpList, 2, 2);
    YzrDLListInsertFirst(tmpList, 3, 3);

    YzrDLListInsertLast(tmpList, 4, 4);
    YzrDLListInsertAfterKey(tmpList, 3, 5, 5);

    YzrDLListNode* curNode = tmpList->headNode;
    while (curNode != NULL) {
        printf("curNode: %d\n", curNode->key);
        curNode = curNode->nextNode;
    }

    YzrDLListNode* findNode = YzrDLListFindKey(tmpList, 2);
    YzrDLListDeleteWithPtr(tmpList, findNode);

    printf("--------------------------\n");

    curNode = tmpList->headNode;
    while (curNode != NULL) {
        printf("curNode: %d\n", curNode->key);
        curNode = curNode->nextNode;
    }

    YzrDLListFree(tmpList);

    return 0;
}