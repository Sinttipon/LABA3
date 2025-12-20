#pragma once

#include <stdbool.h>
/**
 * @file scientific_work.h
 * @brief Заголовочный файл структуры работы
 */

/**
 * @brief Структура научной работы
 */
struct ScientificWork {     
	char* name;             
	char* surname;          
	char* initials;         
	char* magazine;         
	int year;              
	int volume;             
	bool is_included_RINC;  
	int n_pages;            
	int n_citations;        
};

typedef struct ScientificWork ScientificWork;
/**
 * @brief Вычисляет количество цифр в целом числе
 * @param number Число
 * @return Количество цифр в числе
 */
int get_len(int);
/**
 * @brief Преобразует научную работу в строку с разделителями
 * @param s Указатель на структуру
 * @return Указатель на строку
 */
char *get_string(void*);
/**
 * @brief Преобразует научную работу в форматированную строку 
 * @param s Указатель на структуру
 * @return Указатель на строку
 */
char *get_format_string(void*);
/**
 * @brief Создаёт структуру из строки
 * @param s Входная строка.
 * @return Указатель на новую структуру
 */
void *get_work_from_string(char*);
/**
 * @brief Извлекает целое число из строки
 * @param s Входная строка
 * @param start Начальный индекс в строке
 * @param len Количество символов, из которых нужно извлечь число.
 * @return Целое число, извлечённое из строки
 */
int get_int_from_string(char*, int, int);
/**
 * @brief Сравнивает две научные работы по году
 * @param left Указатель на левую работу
 * @param right Указатель на правую работу
 * @return Разница
 */
int compare_by_year(void*, void*);
/**
 * @brief Сравнивает две научные работы по статистике (цитирования/страницы).
 * @param left Указатель на левую структуру 
 * @param right Указатель на правую структуру 
 * @return Разница
 */
int compare_by_statistic(void*, void*);
/**
 * @brief Копирует данные одной научной работы в другую.
 * @param destination Указатель на назначение
 * @param source Указатель на источник
 */
void copy_work(void *, void*);
/**
 * @brief Освобождает память, выделенную под структуру
 * @param p Указатель на структуру 
 */
void free_work(void *);
/**
 * @brief Создаёт научную работу.
 * @return Указатель на новую структуру
 */
void *get_random_work();