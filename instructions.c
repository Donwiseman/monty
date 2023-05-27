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
void free_inst(void)
{
	int x;

	for (x = 0; oplist[x] != NULL; x++)
	{
		free((oplist[x])->opcode);
		free(oplist[x]);
	}
	free(oplist);
}

/**
 * create_oplist - creates an array of instruction_t data for opcodes
 *
 * Return: return a pointer to an array of instructions with matcged opcodes
 */
void create_oplist(void)
{
	oplist = malloc(7 * sizeof(instruction_t *));

	if (oplist == NULL)
		print_mal_err();
	add_inst(&oplist[0], "pall", &print_stack);
	add_inst(&oplist[1], "pop", &pop_stack);
	add_inst(&oplist[2], "pint", &pint_stack);
	add_inst(&oplist[3], "swap", &swap_stack);
	add_inst(&oplist[4], "add", &add_stack);
	add_inst(&oplist[5], "nop", NULL);
	oplist[6] = NULL;
}
