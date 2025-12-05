#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "scientific_work.h"

const char *names[] = {"Ivan", "Petr", "Mihail", "Artem"};
const char *surnames[] = {"Ivanov", "Volkov", "Medvedev", "Zaitsev"};
const char *initials_list[] = {"A.B.", "B.C.", "C.D.", "D.E."};
const char *magazines[] = {"Science", "Nature", "Space", "Discovery"};

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
*/

void *get_random_work() {
	ScientificWork *p_work = (ScientificWork *)malloc(sizeof(ScientificWork));

	p_work->year = rand() % 26 + 2000;	   
	p_work->volume = rand() % 4 + 1;	   
	p_work->is_included_RINC = rand() % 2; 
	p_work->n_pages = rand() % 201 + 200;  
	p_work->n_citations = rand() % 51;	   

	int n = sizeof(names) / sizeof(names[0]);
	const char *s = names[rand() % n];
	p_work->name = (char *)malloc(sizeof(char) * (strlen(s) + 1));
	strcpy(p_work->name, s);

	n = sizeof(surnames) / sizeof(surnames[0]);
	s = surnames[rand() % n];
	p_work->surname = (char *)malloc(sizeof(char) * (strlen(s) + 1));
	strcpy(p_work->surname, s);

	n = sizeof(initials_list) / sizeof(initials_list[0]);
	s = initials_list[rand() % n];
	p_work->initials = (char *)malloc(sizeof(char) * (strlen(s) + 1));
	strcpy(p_work->initials, s);

	n = sizeof(magazines) / sizeof(magazines[0]);
	s = magazines[rand() % n];
	p_work->magazine = (char *)malloc(sizeof(char) * (strlen(s) + 1));
	strcpy(p_work->magazine, s);

	return (void *)p_work;
}

char* get_string(ScientificWork* sw) {
	int len = strlen(sw->name) + strlen(sw->surname) +
		strlen(sw->initials) + strlen(sw->magazine) +
		get_len(sw->year) + get_len(sw->volume) +
		1 + get_len(sw->n_pages) + get_len(sw->n_citations);

	char* buffer = (char*)malloc(sizeof(char) * (len + 1 + 9));

	if (buffer == NULL)
		return NULL;

	sprintf(buffer, "%s;%s;%s;%s;%d;%d;%d;%d;%d;",
		sw->name, sw->surname, sw->initials, sw->magazine,
		sw->year, sw->volume, sw->is_included_RINC,
		sw->n_pages, sw->n_citations);

	return buffer;
}

ScientificWork* get_work_from_string(char* s) {
	ScientificWork* sw = (ScientificWork*)malloc(sizeof(ScientificWork));

	int i = 0;
	for (; s[i] != ';'; i++);
	sw->name = (char*)malloc(sizeof(char) * (i + 1));
	s[i] = '\0';
	strcpy(sw->name, s);

	return sw;
}

void copy_work(void *destination, void *source) {
	ScientificWork *dest = (ScientificWork *)destination;
	ScientificWork *src = (ScientificWork *)source;

	dest->year = src->year;
	dest->volume = src->volume;
	dest->is_included_RINC = src->is_included_RINC;
	dest->n_pages = src->n_pages;
	dest->n_citations = src->n_citations;

	dest->name = (char *)malloc(sizeof(char) * (strlen(src->name) + 1));
	strcpy(dest->name, src->name);

	dest->surname = (char *)malloc(sizeof(char) * (strlen(src->surname) + 1));
	strcpy(dest->surname, src->surname);

	dest->initials = (char *)malloc(sizeof(char) * (strlen(src->initials) + 1));
	strcpy(dest->initials, src->initials);

	dest->magazine = (char *)malloc(sizeof(char) * (strlen(src->magazine) + 1));
	strcpy(dest->magazine, src->magazine);
}

void free_work(void *p)
{
	if (p == NULL)
		return;

	ScientificWork *p_work = (ScientificWork *)p;

	free(p_work->name);
	free(p_work->surname);
	free(p_work->initials);
	free(p_work->magazine);

	free(p_work);
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