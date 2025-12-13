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

char *get_string(void *s){
	ScientificWork *sw = (ScientificWork *)s;

	int len = strlen(sw->name) + strlen(sw->surname) +
			  strlen(sw->initials) + strlen(sw->magazine) +
			  get_len(sw->year) + get_len(sw->volume) +
			  3 + get_len(sw->n_pages) + get_len(sw->n_citations);

	char *buffer = (char *)malloc(sizeof(char) * (len + 1 + 9));

	if (buffer == NULL)
		return NULL;

	sprintf(buffer, "%s;%s;%s;%s;%d;%d;%s;%d;%d;",
			sw->name, sw->surname, sw->initials, sw->magazine,
			sw->year, sw->volume, (sw->is_included_RINC ? "YES" : "NO"),
			sw->n_pages, sw->n_citations);

	return buffer;
}

char *get_format_string(void *s)
{
	ScientificWork *sw = (ScientificWork *)s;

	int len = 170;

	char *buffer = (char *)malloc(sizeof(char) * (len + 1 + 9));

	if (buffer == NULL)
		return NULL;

	sprintf(buffer, "Name: %15s Surname: %15s Initials: %8s Magazine: %10s Year: %4d Volume: %2d RINC: %3s Pages: %3d Citations: %4d",
			sw->name, sw->surname, sw->initials, sw->magazine,
			sw->year, sw->volume, (sw->is_included_RINC ? "YES" : "NO"),
			sw->n_pages, sw->n_citations);

	return buffer;
}

void *get_work_from_string(char *s)
{
	ScientificWork *sw = (ScientificWork *)malloc(sizeof(ScientificWork));

	int i = 0;
	for (; s[i] != ';'; i++);
	sw->name = (char *)malloc(sizeof(char) * (i + 1));

	for (int j = 0; j < i; j++)
		sw->name[j] = s[j];
	sw->name[i] = '\0';
	i++;
	int start = i;

	int len;

	for (; s[i] != ';'; i++);
	len = i - start;
	sw->surname = (char *)malloc(sizeof(char) * (len + 1));

	for (int j = 0; j < len; j++)
		sw->surname[j] = s[j + start];
	sw->surname[len] = '\0';
	i++;
	start = i;

	for (; s[i] != ';'; i++);
	len = i - start;
	sw->initials = (char *)malloc(sizeof(char) * (len + 1));

	for (int j = 0; j < len; j++)
		sw->initials[j] = s[j + start];
	sw->initials[len] = '\0';
	i++;
	start = i;

	for (; s[i] != ';'; i++);
	len = i - start;
	sw->magazine = (char *)malloc(sizeof(char) * (len + 1));

	for (int j = 0; j < len; j++)
		sw->magazine[j] = s[j + start];
	sw->magazine[len] = '\0';
	i++;
	start = i;

	for (; s[i] != ';'; i++);
	len = i - start;
	sw->year = get_int_from_string(s, start, len);
	i++;
	start = i;

	for (; s[i] != ';'; i++);
	len = i - start;
	sw->volume = get_int_from_string(s, start, len);
	i++;
	start = i;

	for (; s[i] != ';'; i++);
	len = i - start;
	sw->is_included_RINC = (s[start] == 'Y' ? 1 : 0);
	i++;
	start = i;

	for (; s[i] != ';'; i++);
	len = i - start;
	sw->n_pages = get_int_from_string(s, start, len);
	i++;
	start = i;

	for (; s[i] != ';'; i++);
	len = i - start;
	sw->n_citations = get_int_from_string(s, start, len);
	i++;
	start = i;

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

int get_int_from_string(char *s, int start, int len)
{
	int number = 0;
	for (int j = start; j < start + len; j++)
		number = number * 10 + s[j] - '0';

	return number;
}