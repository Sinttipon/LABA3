#pragma once
#include <stdbool.h>
#include <cstdio>
struct SetOfFunctions
{
    void *(*create)();
    int (*get_size)(void *);
    void *(*get_object_from_str)(char *);
    void (*push_back)(void *, void *);
    void (*swap_items)(void *, int, int);
    int (*comparator)(void *, int, int, int (*)(void *, void *));
    int (*compare)(void *, void *);

    char *(*get_str)(void *);
    char *(*get_format_string)(void *);

    void (*sort)(void *, SetOfFunctions);
    void (*print)(FILE *, void *);

    void (*free_container)(void *);
};

typedef struct SetOfFunctions SetOfFunctions;

int processing(int, char *[], SetOfFunctions);

int try_to_generate(int, char *[], SetOfFunctions);

int try_to_print(int, char *[], SetOfFunctions);

int try_to_sort(int, char *[], SetOfFunctions);

const char *find_string_argument(int, char *[], const char *, const char *);

int find_int_argument(int, char *[], const char *, const char *);

bool find_argument(int, char *[], const char *, const char *);