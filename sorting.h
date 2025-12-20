#pragma once

#include "stack.h"
#include "processing_arguments.h"
/**
 * @file sorting.h
 * @brief Заголовочный файл для алгоритмов сортировки
 */

/**
 * @brief Сортировка пузырьком
 * @param p_container Указатель на контейнер
 * @param compare_func Функция сравнения
 */
void sort(void *, int (*)(void *, void *));
