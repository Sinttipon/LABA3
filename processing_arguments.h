#pragma once
#include <stdbool.h>
#include <stdio.h>


int processing(int, char *[]);

int try_to_generate(int, char *[]);

int try_to_print(int, char *[]);

int try_to_sort(int, char *[]);

const char *find_string_argument(int, char *[], const char *, const char *);

int find_int_argument(int, char *[], const char *, const char *);

bool find_argument(int, char *[], const char *, const char *);

int try_to_benchmark(int, char *[]);