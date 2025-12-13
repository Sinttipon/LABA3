#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "processing_arguments.h"
#include "stack.h"
#include "sorting.h"

int main(int argc, char *argv[])
{

	srand(time(0));

	processing(argc, argv);

	return 0;
}