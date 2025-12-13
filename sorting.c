#include <stdlib.h>
#include <stdio.h>

#include "sorting.h"
#include "processing_arguments.h"

void sort(void *p_container, int (*compare_func)(void *, void *))
{
    if (p_container == NULL || compare_func == NULL)
    {
        return;
    }

    int control = get_size_stack(p_container) - 1;
    int left = 0;
    int right = get_size_stack(p_container) - 1;
    do
    {
        for (int i = left; i < right; i++)
        {
            if (comparator_stack(p_container, i, i + 1, compare_func) > 0)
            {
                swap_items_in_stack(p_container, i, i + 1);
                control = i;
            }
        }
        right = control;
        for (int i = right; i > left; i--)
        {
            if (comparator_stack(p_container, i, i - 1, compare_func) < 0)
            {
                swap_items_in_stack(p_container, i, i - 1);
                control = i;
            }
        }
        left = control;
    } while (left < right);
}