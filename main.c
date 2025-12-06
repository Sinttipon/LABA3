#include <stdio.h>

#include "processing_arguments.h"
#include "stack.h"
#include "sorting.h"

void read_file(char* filename, Stack*);

void write_file(FILE *file, void *p_container, int (*get_size)(void *), char *(*get_string)(void *, int))
{

	for (int i = 0; i < get_size(p_container); i++)
	{
		char *line = get_string(p_container, i);
		fputs(line, file);
		fputs("\n", file);
		free(line);
	}
}

const char *find_output(int argc, char *argv[])
{

	for (int i = 1; i < argc; i++)
	{
		const char *s = argv[i];
		int len = strlen(s);
		if (len >= 8 && s[0] == '-' && s[1] == '-' &&
			s[2] == 'o' && s[3] == 'u' && s[4] == 't' &&
			s[5] == '=')
		{

			int new_len = len - 6;
			char *result = (char *)malloc(sizeof(char) * (new_len + 1));

			for (int i = 6; i < len; i++)
			{
				result[i - 6] = s[i];
			}
			result[new_len] = '\0';

			return result;
		}

		if (i != argc - 1 && len >= 2 && s[0] == '-' && s[1] == 'o' && s[2] == '\0')
		{

			return argv[i + 1];
		}
	}

	return NULL;
}

int main(int argc, char* argv[]) {


	return 0;
}