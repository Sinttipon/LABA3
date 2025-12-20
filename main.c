#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#include "processing_arguments.h"
#include "stack.h"
#include "sorting.h"

int main(int argc, char *argv[])
{
	SetConsoleOutputCP(CP_UTF8);
	srand(time(0));

	processing(argc, argv);

	return 0;
}