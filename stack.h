#pragma once

#include "scientific_work.h"

struct Node {
	void* p_work;
	int size;
	// ScientificWork work;
	Node* next;
	Node* prev;
};

typedef struct Node Node;

struct Stack {
	int size;
	Node* bottom;
	Node* top;
};

typedef struct Stack Stack;

// инициализация
Stack* create();

// получение текущего размера (количества хранимых элементов)
int get_size(Stack*);

// получение произвольного элемента по индексу
void* get_item(Stack* , int);

// получение указателя на начало
Node* begin(Stack*);

// получение указателя на конец
Node* end(Stack*);

// получение предыдущего элемента от указателя
Node* prev(Node*);

// получение следующего элемента от указателя
Node* next(Node*);

// добавление элемента в начало
void push_front(Stack*, void*);

// добавление элемента в конец
void push_back(Stack*, void*);

// добавление элемента в произвольное место
void insert(Stack*, void*, Node*);

// удаление элемента из начала
void pop_front(Stack*);

// удаление элемента из конца
void pop_back(Stack*);

// удаление элемента из произвольного места
void erase(Stack*, Node*);

// замена пары элементов друг на друга;
void swap(Node*, Node*);

// преобразование массива в структуру-контейнер
Stack* transform(void*, int);

// преобразование структуры-контейнера в массив
void* transform(Stack*, int*);

// очистка.
void clear(Stack*);

// сериализация стека в строку
char* get_string(Stack*);

// построение стека на основе строки
Stack* get_stack_from_string(char*);