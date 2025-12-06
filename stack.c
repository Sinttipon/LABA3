#include "stack.h"

void *create_stack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->size = 0;
    stack->top = NULL;

    return (void *)stack;
}

void clear_stack(void *p_container)
{
    Stack *stack = (Stack *)p_container;

    while (stack->size > 0)
        pop_back((void *)stack);
}

int get_size_stack(void *p_container)
{
    Stack *stack = (Stack *)p_container;
    return stack->size;
}

void **get_item_stack(void *p_container, int index)
{
    Stack *stack = (Stack *)p_container;
    int size = stack->size;

    if (index < 0 || index >= size)
        return NULL;

    Node *node = stack->top;
    for (int i = 0; i < size - index - 1; i++)
    {
        node = node->prev;
    }
    return &node->p_work;
}

void push_back_stack(void *p_container, void *element)
{
    Stack *stack = (Stack *)p_container;
    Node *old_top = stack->top;
    stack->top = create_node(element);
    stack->top->prev = old_top;
    if (old_top != NULL)
    old_top->next = stack->top;
    stack->size++;
}

void swap_items_in_stack(void *p_container, int i1, int i2)
{
    Stack *stack = (Stack *)p_container;
    void **address_p_work_1 = get_item_stack(stack, i1);
    void **address_p_work_2 = get_item_stack(stack, i2);

    if (address_p_work_1 == NULL || address_p_work_2 == NULL)
        return;

    void *pointer = *address_p_work_1;
    *address_p_work_1 = *address_p_work_2;
    *address_p_work_2 = pointer;
}