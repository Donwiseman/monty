#include "monty.h"

/**
 * add_inst - creates a instruction data
 * @d: allocated memory for data
 * @oc: opcode for the instruction
 * @f: function for particular opcode
 */
void add_inst(instruction_t **d, char *oc, void (*f)(stack_t **, unsigned int))
{
	char *opcode;
	void (*func)(stack_t **, unsigned int) = f;
	instruction_t *new;

	opcode = malloc((strlen(oc) + 1) * sizeof(char));
	if (opcode == NULL)
		print_mal_err();
	strcpy(opcode, oc);
	new = malloc(sizeof(instruction_t));
	*d = new;
	(*d)->opcode = opcode;
	(*d)->f = func;
}

/**
 * free_inst - frees array of instruction data type
 * @oplist: array of instruction
 */
void free_inst(instruction_t **oplist)
{
	int x;

	for (x = 0; oplist[x] != NULL; x++)
	{
		free((oplist[x])->opcode);
		free(oplist[x]);
	}
	free(oplist);
}
