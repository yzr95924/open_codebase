/**
 * @file uthash_test_ptr_key.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief https://troydhanson.github.io/uthash/userguide.html#_pointer_keys
 * @version 0.1
 * @date 2023-03-10
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../../include/const.h"
#include "../../include/third/uthash.h"

typedef struct {
  void *key;
  int i;
  UT_hash_handle hh;
} HashTableItem;

HashTableItem* hash = NULL;
char* someaddr = NULL;

int main() {
  HashTableItem* d;
  HashTableItem* e = (HashTableItem*)malloc(sizeof(HashTableItem));
  if (e == NULL) {
    return -1;
  }

  e->key = (void*)someaddr;
  e->i = 1;
  HASH_ADD_PTR(hash, key, e);
  HASH_FIND_PTR(hash, &someaddr, d);
  if (d != NULL) {
    printf("found\n");
  }

  /* release memory */
  HASH_DEL(hash, e);
  free(e);
  return 0;
}