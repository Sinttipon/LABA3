#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "scientific_work.h"

int get_len(int number) {
	if (number == 0)
		return 1;

	int count = 0;
	while (number > 0) {
		number /= 10;
		count++;
	}

	return count;
}


/*
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
*/

char* get_string(ScientificWork* sw) {
	int len = strlen(sw->name) + strlen(sw->surname) +
		strlen(sw->initials) + strlen(sw->magazine) +
		get_len(sw->year) + get_len(sw->volume) +
		1 + get_len(sw->n_pages) + get_len(sw->n_citations);

	char* buffer = (char*)malloc(sizeof(char) * (len + 1));
	sprintf(buffer, "%s;%s;%s;%s;%d;%d;%d;%d;%d;",
		sw->name, sw->surname, sw->initials, sw->magazine,
		sw->year, sw->volume, sw->is_included_RINC,
		sw->n_pages, sw->n_citations);

	return buffer;
}

ScientificWork* get_work_from_string(char* s) {
	ScientificWork* sw = (ScientificWork*)malloc(sizeof(ScientificWork));

	// считывание имени
	int i = 0;
	for (; s[i] != ';'; i++);
	sw->name = (char*)malloc(sizeof(char) * (i + 1));
	s[i] = '\0';
	strcpy(sw->name, s);

	return sw;
}



int compare_by_year(void* left, void* right) {
	ScientificWork* sw_left = (ScientificWork*)left;
	ScientificWork* sw_right = (ScientificWork*)right;

	return sw_left->year - sw_right->year;
}

int compare_by_statistic(void* left, void* right) {
	ScientificWork* sw_left = (ScientificWork*)left;
	ScientificWork* sw_right = (ScientificWork*)right;

	return sw_left->n_citations * 1.0 / sw_left->n_pages - sw_right->n_citations * 1.0 / sw_right->n_pages;
}