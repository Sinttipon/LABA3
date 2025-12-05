#pragma once

#include <stdbool.h>

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

int get_len(int);

char* get_string(ScientificWork*);

ScientificWork* get_work_from_string(char*);

int compare_by_year(void*, void*);

int compare_by_statistic(void*, void*);

void copy_work(void *, void*);

void free_work(void *);

void *get_random_work();