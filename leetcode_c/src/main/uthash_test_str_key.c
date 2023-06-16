/**
 * @file uthash_test_str_key.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://troydhanson.github.io/uthash/userguide.html#_string_keys
 * @version 0.1
 * @date 2023-03-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/const.h"
#include "../../include/third/uthash.h"

typedef struct {
    char name[10];
    int id;
    UT_hash_handle hh;
} HashTableItem;

int main(int argc, char* argv[])
{
    const char *names[] = { "joe", "bob", "betty", NULL };
    HashTableItem* s = NULL;
    HashTableItem* tmp = NULL;
    HashTableItem* users = NULL;

    for (int i = 0; names[i]; i++) {
        s = (HashTableItem*)malloc(sizeof(HashTableItem));
        strcpy(s->name, names[i]);
        s->id = i;
        HASH_ADD_STR(users, name, s);
    }

    HASH_FIND_STR(users, "betty", s);
    if (s) printf("betty's id is %d\n", s->id);

    /* free the hash table contents */
    HASH_ITER(hh, users, s, tmp) {
      HASH_DEL(users, s);
      free(s);
    }
    return 0;
}
