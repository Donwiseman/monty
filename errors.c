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
