#pragma once

#include <stdbool.h>

struct ScientificWork {     // Научная публикация
	char* name;             // Название публикации:
	char* surname;          // Фамилия первого автора
	char* initials;         // Инициалы первого автора
	char* magazine;         // Название журнала
	int year;               // Год публикации
	int volume;             // Том журнала
	bool is_included_RINC;  // Входит в РИНЦ
	int n_pages;            // Количество страниц
	int n_citations;        // Количество Цитирований 
};

typedef struct ScientificWork ScientificWork;

int get_len(int);

char* get_string(ScientificWork*);

ScientificWork* get_work_from_string(char*);

int compare_by_year(void*, void*);

int compare_by_statistic(void*, void*);