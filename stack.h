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

// �������������
void *create_stack();

// ��������� �������� ������� (���������� �������� ���������)
int get_size_stack(void*);

// ��������� ������������� �������� �� �������
void **get_item_stack(void *, int);

// ��������� ��������� �� ������
Node* begin(Stack*);

// ��������� ��������� �� �����
Node* end(Stack*);

// ��������� ����������� �������� �� ���������
Node* prev(Node*);

// ��������� ���������� �������� �� ���������
Node* next(Node*);

// ���������� �������� � ������
void push_front(Stack*, void*);

// ���������� �������� � �����
void push_back_stack(void*, void*);

// ���������� �������� � ������������ �����
void insert(Stack*, void*, Node*);

// �������� �������� �� ������
void pop_front(Stack*);

// �������� �������� �� �����
void pop_back(Stack*);

// �������� �������� �� ������������� �����
void erase(Stack*, Node*);

// ������ ���� ��������� ���� �� �����;
void swap_items_in_stack(void*, int, int);

// �������������� ������� � ���������-���������
Stack* transform(void*, int);

// �������������� ���������-���������� � ������
void* transform(Stack*, int*);

// �������.
void clear_stack(void*);

// ������������ ����� � ������
char* get_string(Stack*);

// ���������� ����� �� ������ ������
Stack* get_stack_from_string(char*);