#pragma once

#include "scientific_work.h"

struct Node
{
	void *p_work;
	struct Node *prev;
};

typedef struct Node Node;

struct Stack
{
	unsigned int size;
	Node *top;
};

typedef struct Stack Stack;
/**
 * @brief Создаёт новый узел стека с копией элемента
 * @param element Указатель на элемент, который нужно скопировать в узел
 * @return Указатель на новый узел
 */
Node *create_node(void *);
/**
 * @brief Освобождает память, выделенную под узел стека
 * @param node Указатель на узел стека
 */
void free_node(Node *);
/**
 * @brief Освобождает память, выделенную под стек
 * @param p_container Указатель на стек
 */
void free_stack(void *);
/**
 * @brief Создаёт новый пустой стек
 * @return Указатель на новый стек
 */
void *create_stack();
/**
 * @brief Очищает стек, удаляя все элементы
 * @param p_container Указатель на стек
 */
void clear_stack(void *);
/**
 * @brief Возвращает размер стека
 * @param p_container Указатель на стек
 * @return Количество элементов в стеке
 */
int get_size_stack(void *);
/**
 * @brief Получает указатель на элемент по индексу в стеке
 * @param p_container Указатель на стек
 * @param index Индекс элемента 
 * @return Указатель на элемент
 */
void **get_item_stack(void *, int);
/**
 * @brief Добавляет элемент в конец стека
 * @param p_container Указатель на стек
 * @param element Указатель на элемент для добавления
 */
void push_back_stack(void *, void *);
/**
 * @brief Удаляет элемент из конца стека
 * @param p_container Указатель на стек
 */
void pop_back_stack(void *);
/**
 * @brief Меняет местами два элемента в стеке по индексам
 * @param p_container Указатель на стек
 * @param i1 Индекс первого элемента
 * @param i2 Индекс второго элемента
 */
void swap_items_in_stack(void *, int, int);
/**
 * @brief Сравнивает два элемента в стеке по индексам
 * @param p_container Указатель на стек
 * @param i1 Индекс первого элемента
 * @param i2 Индекс второго элемента
 * @param comparator Указатель на функцию сравнения
 * @return Результат сравнения
 */
int comparator_stack(void *, int, int, int (*)(void *, void *));
/**
 * @brief Преобразует элемент стека в строку по индексу
 * @param p_container Указатель на стек
 * @param index Индекс элемента
 * @return Указатель на строку
 */
char *get_string_stack_line(void *, int);
/**
 * @brief Возвращает указатель на начало стека
 * @param p_container Указатель на стек
 * @return Указатель на первый элемент
 */
void *begin_stack(void *);
/**
 * @brief Возвращает указатель на вершину стека
 * @param p_container Указатель на стек
 * @return Указатель на вершину стека
 */
void *end_stack(void *);
/**
 * @brief Возвращает указатель на предыдущий узел
 * @param p_node Указатель на текущий узел
 * @return Указатель на предыдущий узел
 */
void *prev_stack(void *);
/**
 * @brief Возвращает указатель на следующий узел
 * @param p_container Указатель на стек
 * @param p_node Указатель на текущий узел
 * @return Указатель на следующий узел
 */
void *next_stack(void *, void *);
/**
 * @brief Добавляет элемент в начало стека
 * @param p_container Указатель на стек
 * @param element Указатель на элемент для добавления
 */
void push_front_stack(void *, void *);
/**
 * @brief Вставляет элемент перед указанным узлом
 * @param p_container Указатель на стек
 * @param element Указатель на элемент для вставки
 * @param p_node Указатель на узел, перед которым вставляется элемент
 */
void insert_stack(void *, void *, void *);
/**
 * @brief Удаляет элемент из начала стека
 * @param p_container Указатель на стек
 */
void pop_front_stack(void *);
/**
 * @brief Удаляет указанный узел из стека
 * @param p_container Указатель на стек
 * @param p_node Указатель на узел для удаления
 */
void erase_stack(void *, void *);
/**
 * @brief Преобразует массив элементов в стек
 * @param p_array Указатель на массив элементов
 * @param size Размер массива
 * @return Указатель на новый стек
 */
void *transform_array_to_stack(void *, int);
/**
 * @brief Преобразует стек в массив
 * @param p_container Указатель на стек
 * @param p_size Указатель на переменную с рамером 
 * @return Указатель на массив
 */
void *transform_stack_to_array(void *, int *);
/**
 * @brief Преобразует весь стек в строку
 * @param p_container Указатель на стек
 * @return Указатель на строку
 */
char *get_string_stack(void *);
/**
 * @brief Создаёт стек из строки
 * @param s Входная строка
 * @return Указатель на новый стек
 */
void *get_stack_from_string(char *);
/**
 * @brief Печатает содержимое стека в файл
 * @param file Указатель на файл
 * @param p_container Указатель на стек
 */
void print_stack(FILE *, void *);
/**
 * @brief Перемещает заданное количество элементов из одного стека в другой
 * @param destination Указатель на куда
 * @param source Указатель на откуда
 * @param quantity Количество элементов для перемещения
 */
void move(Stack *, Stack *, int);