/**
 * @file uthash_test.c
 * @author Zuoru YANG (zryang@cse.cuhk.edu.hk)
 * @brief check: https://troydhanson.github.io/uthash/userguide.html
 * @version 0.1
 * @date 2023-01-29
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/third/uthash.h"

typedef struct {
    int id;
    char name[21];
    UT_hash_handle hh;
} my_struct_t;

my_struct_t *users = NULL; // a global hash table

void AddUser(int user_id, const char *name) {
    my_struct_t *s = NULL;
    HASH_FIND_INT(users, &user_id, s); // id already in the hash?
    if (s == NULL) {
        // not exist
        s = (my_struct_t*)malloc(sizeof(my_struct_t));
        s->id = user_id;
        HASH_ADD_INT(users, id, s); // id is the key field
    }
    strcpy(s->name, name);
    return;
}

my_struct_t *FindUser(int user_id) {
    my_struct_t *s = NULL;
    HASH_FIND_INT(users, &user_id, s);
    return s;
}

void DeleteUser(my_struct_t *user) {
    HASH_DEL(users, user); // user is the pointer to delete
    free(user);
    return;
}

void DeleteAll() {
    my_struct_t *cur_user;
    my_struct_t *tmp;
    HASH_ITER(hh, users, cur_user, tmp) {
        HASH_DEL(users, cur_user);
        free(cur_user);
    }
    return;
}

void PrintUsers() {
    my_struct_t *s;
    for (s = users; s != NULL; s = (my_struct_t*)(s->hh.next)) {
        printf("user id %d: name %s\n", s->id, s->name);
    }
    return;
}

int ByName(const my_struct_t *a, const my_struct_t *b) {
    return strcmp(a->name, b->name);
}

int ById(const my_struct_t* a, const my_struct_t *b) {
    return (a->id - b->id);
}

const char *GetL(const char *prompt) {
    static char buf[21];
    char *p;
    printf("%s? ", prompt); fflush(stdout);
    p = fgets(buf, sizeof(buf), stdin);
    if (p == NULL || (p = strchr(buf, '\n')) == NULL) {
        puts("Invalid input!");
        exit(EXIT_FAILURE);
    }
    *p = '\0';
    return buf;
}

int main()
{
    int id = 1;
    int running = 1;
    my_struct_t *s;
    int temp;

    while (running) {
        printf(" 1. add user\n");
        printf(" 2. add or rename user by id\n");
        printf(" 3. find user\n");
        printf(" 4. delete user\n");
        printf(" 5. delete all users\n");
        printf(" 6. sort items by name\n");
        printf(" 7. sort items by id\n");
        printf(" 8. print users\n");
        printf(" 9. count users\n");
        printf("10. quit\n");
        switch (atoi(GetL("Command"))) {
            case 1:
                AddUser(id++, GetL("Name (20 char max)"));
                break;
            case 2:
                temp = atoi(GetL("ID"));
                AddUser(temp, GetL("Name (20 char max)"));
                break;
            case 3:
                s = FindUser(atoi(GetL("ID to find")));
                printf("user: %s\n", s ? s->name : "unknown");
                break;
            case 4:
                s = FindUser(atoi(GetL("ID to delete")));
                if (s) {
                    DeleteUser(s);
                } else {
                    printf("id unknown\n");
                }
                break;
            case 5:
                DeleteAll();
                break;
            case 6:
                HASH_SORT(users, ByName);
                break;
            case 7:
                HASH_SORT(users, ById);
                break;
            case 8:
                PrintUsers();
                break;
            case 9:
                temp = HASH_COUNT(users);
                printf("there are %d users\n", temp);
                break;
            case 10:
                running = 0;
                break;
        }
    }

    DeleteAll();  /* free any structures */
    return 0;
}