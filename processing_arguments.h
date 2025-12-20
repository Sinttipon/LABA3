#pragma once
#include <stdbool.h>
#include <stdio.h>

/**
 * @brief Вызывает все функции обработки аргументов 
 * @param argc Количество аргументов командной строки.
 * @param argv Массив аргументов командной строки.
 * @return 0 
 */
int processing(int, char *[]);
/**
 * @brief Генерирует заданное количество случайных научных работ и выводит их в файл или в stdout
 * @param argc Количество аргументов командной строки.
 * @param argv Массив аргументов командной строки.
 * @return 0 
 */
int try_to_generate(int, char *[]);
/**
 * @brief Читает научные работы из файла и выводит их в форматированном виде в файл или в stdout
 * @param argc Количество аргументов командной строки
 * @param argv Массив аргументов командной строки
 * @return 0 
 */
int try_to_print(int, char *[]);
/**
 * @brief Читает научные работы из файла или stdin, сортирует их и выводит в файл или в stdout
 * @param argc Количество аргументов командной строки.
 * @param argv Массив аргументов командной строки.
 * @return 0 
 */
int try_to_sort(int, char *[]);
/**
 * @brief Ищет аргументы в формате --name=value или -n value.
 * @param argc Количество аргументов командной строки
 * @param argv Массив аргументов командной строки
 * @param long_name Длинное имя аргумента 
 * @param short_name Короткое имя аргумента 
 * @return Указатель на строку значения аргумента
 */
const char *find_string_argument(int, char *[], const char *, const char *);
/**
 * @brief Ищет целочисленный аргумент в командной строке по длинному или короткому имени.
 * @param argc Количество аргументов командной строки
 * @param argv Массив аргументов командной строки
 * @param long_name Длинное имя аргумента
 * @param short_name Короткое имя аргумента 
 * @return Значение аргумента
 */
int find_int_argument(int, char *[], const char *, const char *);
/**
 * @brief Проверяет наличие аргумента в командной строке по длинному или короткому имени
 * @param argc Количество аргументов командной строки
 * @param argv Массив аргументов командной строки
 * @param long_name Длинное имя аргумента 
 * @param short_name Короткое имя аргумента
 * @return true, если аргумент найден, иначе false.
 */
bool find_argument(int, char *[], const char *, const char *);
/**
 * @brief Проводит бенчмарк сортировки с разным количеством элементов.
 * @param argc Количество аргументов командной строки.
 * @param argv Массив аргументов командной строки.
 * @return 0 
 */
int try_to_benchmark(int, char *[]);