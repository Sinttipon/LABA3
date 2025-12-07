#pragma once

#include "scientific_work.h"

struct Node
{
	void *p_work;
	Node *prev;
};

typedef struct Node Node;

struct Stack
{
	int size;
	Node *top;
};

typedef struct Stack Stack;

Node *create_node(void *);

void free_node(Node *);

void free_stack(void *);

void *create_stack();

void clear_stack(void *);

int get_size_stack(void *);

void **get_item_stack(void *, int);

void push_back_stack(void *, void *);

void pop_back_stack(void *);

void swap_items_in_stack(void *, int, int);

int comparator_stack(void *, int, int, int (*)(void *, void *));

char *get_string_stack_line(void *, int);

void *begin_stack(void *);

void *end_stack(void *);

void *prev_stack(void *);

void *next_stack(void *, void *);

void push_front_stack(void *, void *);

void insert_stack(void *, void *, void *);

void pop_front_stack(void *);

void erase_stack(void *, void *);

void *transform_array_to_stack(void *, int);

void *transform_stack_to_array(void *, int *);

char *get_string_stack(void *);

void *get_stack_from_string(char *);

void print_stack(FILE *, void *);