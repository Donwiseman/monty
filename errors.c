#include "monty.h"

/**
 * print_file_err - prints error on file opening abd exits
 * @file: name of file which failed to open
 */
void print_file_err(char *file)
{
	fprintf(stderr, "Error: Can't open file %s\n", file);
	exit(EXIT_FAILURE);
}

/**
 * print_usage_err - prints error if from args passed to program
 */
void print_usage_err(void)
{
	fprintf(stderr, "USAGE: monty file\n");
	exit(EXIT_FAILURE);
}

/**
 * print_mal_err - prints error from failed malloc
 */
void print_mal_err(void)
{
	fprintf(stderr, "Error: malloc failed\n");
	exit(EXIT_FAILURE);
}

/**
 * check_arg - checks that the arguments are numerical and prints error
 * @stack: pointer to stack
 * @line_number: line number op was read from script
 * @op: operation code
 * @arg: argument to be checked
 */
void check_arg(stack_t **stack, unsigned int line_number, char *op, char *arg)
{
	unsigned int x, ln = line_number;

	for (x = 0; arg[x] != '\0'; x++)
	{
		if ((arg[x] < 48 || arg[x] > 57) && arg[x] != '-')
		{
			free_all(stack, op, arg);
			fprintf(stderr, "L%u: usage: push integer\n", ln);
			exit(EXIT_FAILURE);
		}
	}
}
