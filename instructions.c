#include "monty.h"

/**
 * add_inst - creates a instruction data
 * @dt: allocated memory for data
 * @op_c: opcode for the instruction
 * @f: function for particular opcode
 */
void add_inst(instruction_t *dt, char *oc, void (*f)(stack_t **, unsigned int))
{
	char *opcode;
	void (*func)(stack_t **, unsigned int) = f;

	opcode = malloc((strlen(oc) + 10) * sizeof(char));
	if (opcode == NULL)
		print_mal_err();
	strcpy(opcode, oc);
	dt->opcode = opcode;
	dt->f = func;
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
	}
	free(oplist);
}
