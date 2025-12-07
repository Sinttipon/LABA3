#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "stack.h"

Node *create_node(void *element)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->prev = NULL;
    node->p_work = malloc(sizeof(ScientificWork));
    copy_work(node->p_work, element);

    return node;
}

void free_node(Node *node)
{
    free_work(node->p_work);
    free(node);
}

void *create_stack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));

    if (stack == NULL)
        return NULL;

    stack->size = 0;
    stack->top = NULL;

    return (void *)stack;
}

void free_stack(void *p_container)
{
    Stack *stack = (Stack *)p_container;
    clear_stack(p_container);
    free(stack);
}

bool is_empty_stack(Stack *stack)
{
    return stack->size == 0;
}

void clear_stack(void *p_container)
{
    Stack *stack = (Stack *)p_container;

    while (!is_empty_stack(stack))
        pop_back_stack((void *)stack);
}

int get_size_stack(void *p_container)
{
    Stack *stack = (Stack *)p_container;
    return stack->size;
}

void *end_stack(void *p_container)
{
    Stack *stack = (Stack *)p_container;

    return (void *)stack->top;
}

void move(Stack *destination, Stack *source, int quantity)
{
    Node *node = source->top;
    for (int i = 0; i < quantity; i++)
    {
        ScientificWork *item = (ScientificWork *)malloc(sizeof(ScientificWork));
        copy_work(item, (void *)source->top->p_work);
        pop_back_stack((void *)source);
        push_back_stack((void *)destination, item);
        free(item);
    }
}

void **get_item_stack(void *p_container, int index)
{
    Stack *stack = (Stack *)p_container;
    int size = stack->size;

    if (index < 0 || index >= size)
    {
        return NULL;
    }

    Stack *tmp = (Stack *)create_stack();

    move(tmp, stack, size - index - 1);

    void **p_p_work = (void **)&stack->top->p_work;

    move(stack, tmp, size - index - 1);

    free_stack(tmp);

    return p_p_work;
}

void push_back_stack(void *p_container, void *element)
{
    Stack *stack = (Stack *)p_container;
    Node *old_top = stack->top;
    stack->top = create_node(element);
    stack->top->prev = old_top;
    stack->size++;
}

void pop_back_stack(void *p_container)
{
    Stack *stack = (Stack *)p_container;

    if (is_empty_stack(stack))
        return;

    Node *old_top = stack->top;
    stack->top = old_top->prev;

    free_node(old_top);
    stack->size--;
}

void swap_items_in_stack(void *p_container, int i1, int i2)
{

    if (i1 == i2)
        return;

    if (i1 > i2)
    {
        int tmp = i1;
        i1 = i2;
        i2 = tmp;
    }

    Stack *stack = (Stack *)p_container;
    Stack *tmp = (Stack *)create_stack();

    int size = stack->size;

    move(tmp, stack, size - i2 - 1);

    ScientificWork *item2 = (ScientificWork *)malloc(sizeof(ScientificWork));
    copy_work(item2, (void *)stack->top->p_work);
    pop_back_stack((void *)stack);

    move(tmp, stack, i2 - i1 - 1);

    ScientificWork *item1 = (ScientificWork *)malloc(sizeof(ScientificWork));

    copy_work(item1, (void *)stack->top->p_work);

    pop_back_stack((void *)stack);

    push_back_stack(stack, item2);

    move(stack, tmp, i2 - i1 - 1);

    push_back_stack(stack, item1);

    move(stack, tmp, size - i2 - 1);

    free(item2);
    free(item1);

    free_stack(tmp);
}

int comparator_stack(void *p_container, int i1, int i2, int (*comparator)(void *, void *))
{
    Stack *stack = (Stack *)p_container;

    ScientificWork *p_work_1 = (ScientificWork *)malloc(sizeof(ScientificWork));
    copy_work(p_work_1, *(ScientificWork **)get_item_stack(stack, i1));

    void **address_p_work_2 = get_item_stack(stack, i2);

    return comparator(p_work_1, *(ScientificWork **)address_p_work_2);
}

char *get_string_stack_line(void *p_container, int index)
{
    Stack *stack = (Stack *)p_container;
    ScientificWork *p_work = (ScientificWork *)*get_item_stack(stack, index);

    return get_string(p_work);
}

void *begin_stack(void *p_container)
{
    Stack *stack = (Stack *)p_container;

    if (is_empty_stack(stack))
        return NULL;

    Stack *tmp = (Stack *)create_stack();

    int size = stack->size;

    move(tmp, stack, size - 1);

    void *node = (void *)stack->top;

    move(stack, tmp, size - 1);

    free_stack(tmp);

    return node;
}

void *prev_stack(void *p_node)
{
    Node *node = (Node *)p_node;

    if (node == NULL)
        return NULL;

    return (void *)node->prev;
}

void *next_stack(void *p_container, void *p_node)
{
    Stack *stack = (Stack *)p_container;
    Node *node = (Node *)p_node;

    if (node == NULL)
        return NULL;

    Stack *tmp = (Stack *)create_stack();

    int size = stack->size;

    while (stack->top != NULL && stack->top != p_node)
    {
        move(tmp, stack, 1);
    }

    if (stack->top == NULL)
    {
        move(stack, tmp, tmp->size);
        free_stack(tmp);
        return NULL;
    }

    move(stack, tmp, 1);

    void *next_node = (void *)stack->top;

    move(stack, tmp, tmp->size);

    free_stack(tmp);

    return next_node;
}

void push_front_stack(void *p_container, void *element)
{
    Stack *stack = (Stack *)p_container;

    if (is_empty_stack(stack))
    {
        push_back_stack(p_container, element);
        return;
    }

    Stack *tmp = (Stack *)create_stack();

    int size = stack->size;

    move(tmp, stack, size);

    push_back_stack(p_container, element);

    move(stack, tmp, size);
}

void insert_stack(void *p_container, void *element, void *p_node)
{
    Stack *stack = (Stack *)p_container;
    Node *node = (Node *)p_node;

    if (node == NULL)
        return;

    Stack *tmp = (Stack *)create_stack();

    while (stack->top != NULL && stack->top != p_node)
    {
        move(tmp, stack, 1);
    }

    if (stack->top == NULL)
    {
        move(stack, tmp, tmp->size);
        free_stack(tmp);
        return;
    }

    push_back_stack(p_container, element);

    move(stack, tmp, tmp->size);

    free_stack(tmp);
}

void pop_front_stack(void *p_container)
{
    Stack *stack = (Stack *)p_container;

    if (is_empty_stack(stack))
        return;

    Stack *tmp = (Stack *)create_stack();

    int size = stack->size;

    move(tmp, stack, size);
    pop_back_stack(tmp);
    move(stack, tmp, size - 1);

    free_stack(tmp);
}

void erase_stack(void *p_container, void *p_node)
{
    Stack *stack = (Stack *)p_container;
    Node *node = (Node *)p_node;

    if (node == NULL)
        return;

    Stack *tmp = (Stack *)create_stack();

    while (stack->top != NULL && stack->top != p_node)
    {
        move(tmp, stack, 1);
    }

    if (stack->top == NULL)
    {
        move(stack, tmp, tmp->size);
        free_stack(tmp);
        return;
    }

    pop_back_stack(p_container);

    move(stack, tmp, tmp->size);

    free_stack(tmp);
}

void *transform_array_to_stack(void *p_array, int size)
{
    Stack *stack = (Stack *)create_stack();
    ScientificWork *works = (ScientificWork *)p_array;

    for (int i = 0; i < size; i++)
    {
        push_back_stack(stack, (void *)(works + i));
    }

    return (void *)stack;
}

void *transform_stack_to_array(void *p_container, int *p_size)
{
    Stack *stack = (Stack *)create_stack();

    int n = get_size_stack(stack);
    ScientificWork *works = (ScientificWork *)malloc(sizeof(ScientificWork) * n);
    *p_size = n;

    Node *node = stack->top;

    for (int i = n - 1; i >= 0; i--)
    {
        copy_work(&works[i], node->p_work);
        node = node->prev;
    }

    return (void *)works;
}

char *get_string_stack(void *p_container)
{
    Stack *stack = (Stack *)p_container;

    int full_len = 0;
    for (int i = 0; i < stack->size; i++)
    {
        char *line = get_string_stack_line(p_container, i);

        full_len += strlen(line) + 1;

        free(line);
    }

    char *buffer = (char *)malloc(sizeof(char) * (full_len + 1));
    buffer[0] = '\0';

    for (int i = 0; i < stack->size; i++)
    {
        char *line = get_string_stack_line(p_container, i);

        strcat(buffer, line);
        strcat(buffer, "\n");

        free(line);
    }

    return buffer;
}

void *get_stack_from_string(char *s)
{
    Stack *stack = (Stack *)create_stack();

    int index = 0;
    for (int i = 0; s[i] != EOF; i++)
    {
        if (s[i] == '\n')
        {
            ScientificWork *p_work = get_work_from_string(s + index);
            push_back_stack((void *)stack, (void *)p_work);
            index = i + 1;
            free_work(p_work);
        }
    }

    return (void *)stack;
}