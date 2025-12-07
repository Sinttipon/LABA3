#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "processing_arguments.h"
#include "scientific_work.h"

const char *find_string_argument(int argc, char *argv[], const char *long_name, const char *short_name)
{

    for (int i = 1; i < argc - 1; i++)
    {
        const char *s = argv[i];
        int len = strlen(s);
        int len_long = strlen(long_name);
        char *start = (char *)malloc(sizeof(char) * (len_long + 1));
        for (int i = 0; i < len_long; i++)
        {
            start[i] = s[i];
        }
        start[len_long] = '\0';

        if (len >= len_long && strcmp(long_name, start) == 0)
        {

            int new_len = len - len_long;
            char *result = (char *)malloc(sizeof(char) * (new_len + 1));

            for (int i = len_long; i < len; i++)
            {
                result[i - len_long] = s[i];
            }
            result[new_len] = '\0';

            return result;
        }

        free(start);

        int len_short = strlen(short_name);
        if (i != argc - 1 && len >= len_short && strcmp(short_name, s) == 0)
        {
            return argv[i + 1];
        }
    }

    return NULL;
}

int find_int_argument(int argc, char *argv[], const char *long_name, const char *short_name)
{
    for (int i = 1; i < argc - 1; i++)
    {
        if (i != argc - 1 && (strcmp(long_name, argv[i]) == 0 || strcmp(short_name, argv[i]) == 0))
        {
            int n;
            sscanf(argv[i + 1], "%d", &n);
            return n;
        }
    }

    return 0;
}

bool find_argument(int argc, char *argv[], const char *long_name, const char *short_name)
{
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], long_name) == 0 || strcmp(argv[i], short_name) == 0)
            return true;
    }
    return false;
}

int try_to_generate(int argc, char *argv[], SetOfFunctions funcs)
{
    int n = find_int_argument(argc, argv, "--generate", "-g");

    if (n == 0)
        return 0;

    const char *filename = find_string_argument(argc, argv, "--out=", "-o");

    FILE *file = NULL;
    if (filename != NULL)
    {
        file = fopen(filename, "w");

        if (file == NULL)
            return 0;
    }

    for (int i = 0; i < n; i++)
    {
        void *p_work = get_random_work();

        char *s = funcs.get_str(p_work);

        if (filename != NULL)
        {
            fprintf(file, "%s\n", s);
        }
        else
        {
            printf("%s\n", s);
        }
        free(s);
        free(p_work);
    }

    if (filename != NULL)
    {
        fclose(file);
    }

    return 0;
}

int try_to_print(int argc, char *argv[], SetOfFunctions funcs)
{

    if (!find_argument(argc, argv, "--print", "-p"))
        return 0;

    const char *filename = find_string_argument(argc, argv, "--in=", "-i");

    if (filename == NULL)
    {
        printf("Enter input filename: ");
        scanf("%s", filename);
    }

    FILE *file = NULL;
    file = fopen(filename, "r");

    if (file == NULL)
        return 0;

    const char *output_filename = find_string_argument(argc, argv, "--out=", "-o");

    FILE *output = NULL;

    if (output_filename != NULL)
    {
        output = fopen(output_filename, "w");

        if (output == NULL)
            return 0;
    }

    char *s = (char *)malloc(sizeof(char) * 170);

    while (fscanf(file, "%s", s) != -1)
    {
        void *object = funcs.get_object_from_str(s);
        free(s);
        s = funcs.get_format_string(object);
        if (output_filename == NULL)
        {
            printf("%s\n", s);
        }
        else
        {
            fprintf(output, "%s\n", s);
        }
        free(s);
        s = (char *)malloc(sizeof(char) * 170);

        free(object);
    }

    if (output_filename != NULL)
    {
        fclose(output);
    }
    fclose(file);

    return 0;
}

int try_to_sort(int argc, char *argv[], SetOfFunctions funcs)
{

    if (!find_argument(argc, argv, "--sort", "-s"))
        return 0;

    void *container = funcs.create();

    const char *input_filename = find_string_argument(argc, argv, "--in=", "-i");
    char s[170];
    if (input_filename == NULL)
    {
        printf("Enter quantity: ");
        int n = 0;
        scanf("%d", &n);

        for (int i = 0; i < n; i++)
        {
            scanf("%s", s);
            void *object = funcs.get_object_from_str(s);
            funcs.push_back(container, object);
            free(object);
        }
    }
    else
    {

        FILE *file = NULL;
        file = fopen(input_filename, "r");

        if (file == NULL)
        {
            free(container);
            return 0;
        }

        while (fscanf(file, "%s", s) != -1)
        {
            void *object = funcs.get_object_from_str(s);
            funcs.push_back(container, object);
            free(object);
        }
    }

    funcs.sort(container, funcs);

    const char *output_filename = find_string_argument(argc, argv, "--out=", "-o");

    FILE *output = NULL;

    if (output_filename != NULL)
    {
        output = fopen(output_filename, "w");

        if (output == NULL)
            return 0;

        funcs.print(output, container);
    }
    else
    {
        funcs.print(stdout, container);
    }

    funcs.free_container(container);
}

int processing(int argc, char *argv[], SetOfFunctions funcs)
{

    try_to_generate(argc, argv, funcs);
    try_to_print(argc, argv, funcs);
    try_to_sort(argc, argv, funcs);

    return 0;
}