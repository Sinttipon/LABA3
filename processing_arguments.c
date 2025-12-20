#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "processing_arguments.h"
#include "scientific_work.h"
#include "stack.h"
#include "sorting.h"

const char *find_string_argument(int argc, char *argv[], const char *long_name, const char *short_name)
{

    for (int i = 1; i < argc; i++)
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

            free(start);
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

int try_to_generate(int argc, char *argv[])
{
    int n = find_int_argument(argc, argv, "--generate", "-g");

    if (n == 0)
        return 0;

    const char *filename = find_string_argument(argc, argv, "--out=", "-o");
    FILE *file = stdout;
    if (filename != NULL)
    {
        FILE *temp = fopen(filename, "w");

        if (temp != NULL)
            file = temp;
    }

    for (int i = 0; i < n; i++)
    {
        void *p_work = get_random_work();

        char *s = get_string(p_work);

        fprintf(file,"%s\n",s);

        free(s);
        free_work(p_work);
    }

    if (filename != NULL)
    {
        fclose(file);
    }

    return 0;
}

int try_to_print(int argc, char *argv[])
{

    if (!find_argument(argc, argv, "--print", "-p"))
        return 0;

    const char *filename = find_string_argument(argc, argv, "--in=", "-i");

    if (filename == NULL)
    {
        printf("Введите файл куда : ");
        char temp_filename_buffer[256];
        if (scanf("%255s", temp_filename_buffer) != 1)
        {
            return 0;
        }
        filename = temp_filename_buffer;
    }

    FILE *file = NULL;
    file = fopen(filename, "r");

    if (file == NULL)
        return 0;

    const char *output_filename = find_string_argument(argc, argv, "--out=", "-o");

    FILE *output = stdout;

    if (output_filename != NULL)
    {
        FILE *temp = fopen(output_filename, "w");
        if (temp != NULL)
            output = temp;
    }

    char *s = (char *)malloc(sizeof(char) * 170);

    while (fscanf(file, "%s", s) != -1)
    {
        void *object = get_work_from_string(s);
        free(s);
        s = get_format_string(object);
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

        free_work(object);
    }
    free(s);

    if (output_filename != NULL)
    {
        fclose(output);
    }
    fclose(file);

    return 0;
}

static int compare_by_year_desc_wrapper(void *left, void *right)
{
    return -compare_by_year(left, right);
}

int try_to_sort(int argc, char *argv[])
{

    if (!find_argument(argc, argv, "--sort", "-s"))
        return 0;

    void *container = create_stack();

    const char *input_filename = find_string_argument(argc, argv, "--in=", "-i");
    char s[170];
    if (input_filename == NULL)
    {
        printf("Введите кол-во : ");
        int n = 0;
        scanf("%d", &n);

        for (int i = 0; i < n; i++)
        {
            scanf("%s", s);
            void *object = get_work_from_string(s);
            push_back_stack(container, object);
            free_work(object);
        }
    }
    else
    {

        FILE *file = NULL;
        file = fopen(input_filename, "r");

        if (file == NULL)
        {
            free_stack(container);
            return 0;
        }

        while (fscanf(file, "%s", s) != -1)
        {
            void *object = get_work_from_string(s);
            push_back_stack(container, object);
            free_work(object);
        }
        fclose(file);
    }

    const char *sort_type = find_string_argument(argc, argv, "--type=", "-t");
    int (*compare_func)(void *, void *) = compare_by_year;

    if (sort_type != NULL)
    {
        if (strcmp(sort_type, "desc") == 0)
        {
            compare_func = compare_by_year_desc_wrapper;
        }
        else if (strcmp(sort_type, "asc") == 0)
        {
            compare_func = compare_by_year;
        }
    }
    sort(container, compare_func);

    const char *output_filename = find_string_argument(argc, argv, "--out=", "-o");

    FILE *output = stdout;

    if (output_filename != NULL)
    {
        FILE* temp = fopen(output_filename, "w");

        if (temp != NULL)
        {
            output=temp;
        }
    }
    print_stack(output, container);

    if (output != stdout)
    {
        fclose(output);
    }

    free_stack(container);
    return 0;
    
}

int processing(int argc, char *argv[])
{

    try_to_generate(argc, argv);
    try_to_print(argc, argv);
    try_to_sort(argc, argv);
    try_to_benchmark(argc, argv);

    return 0;
}

int try_to_benchmark(int argc, char *argv[])
{
    if (!find_argument(argc, argv, "--benchmark", "-b"))
    {
        return 0;
    }

    const char *output_filename = find_string_argument(argc, argv, "--out=", "-o");
    if (output_filename == NULL)
    {
        output_filename = "benchmark_results.csv";
    }

    FILE *out = fopen(output_filename, "w");
    
    int sizes[] = {10,100,200,300,400};
    int n_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < n_sizes; i++)
    {
        int n = sizes[i];
        void *container = create_stack();
        if (container == NULL)
        {
            fclose(out);
            return 1;
        }

        for (int j = 0; j < n; j++)
        {
            void *work = get_random_work();
            if (work != NULL)
            {
                push_back_stack(container, work);
            }
        }

        clock_t start = clock();

        sort(container, compare_by_year);

        clock_t end = clock();
        double time = ((double)(end - start)) / CLOCKS_PER_SEC;

        fprintf(out, "%d,%.6f\n", n, time);
        printf("Получение денных %d из %d ...\n", i, n_sizes-1);
        free_stack(container);
    }

    fclose(out);
    return 0;
}