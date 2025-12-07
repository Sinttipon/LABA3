#include <stdlib.h>
#include <stdio.h>

#include "sorting.h"
#include "processing_arguments.h"

void sort(void *p_container, SetOfFunctions funcs)
{

    int control = funcs.get_size(p_container) - 1;
    int left = 0;
    int right = funcs.get_size(p_container) - 1;
    do
    {
        for (int i = left; i < right; i++)
        {
            if (funcs.comparator(p_container, i, i + 1, funcs.compare) > 0)
            {
                funcs.swap_items(p_container, i, i + 1);
                control = i;
            }
        }
        right = control;
        for (int i = right; i > left; i--)
        {
            if (funcs.comparator(p_container, i, i - 1, funcs.compare) < 0)
            {
                funcs.swap_items(p_container, i, i - 1);
                control = i;
            }
        }
        left = control;
    } while (left < right);
}