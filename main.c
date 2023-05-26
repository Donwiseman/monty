#include "monty.h"

/**
 * push_op - performs the push operation
 * @stack: pointer to stack
 * @arg: arg to push
 * @line_number: line number read from script
 * @opcode: operation code "push"
 *
 * Return: 1 if succesful and 0 otherwise
 */
ssize_t push_op(stack_t **stack, char *arg, ssize_t line_number, char *opcode)
{
	int num;
	stack_t *new;

	if (arg == NULL)
	{
		free(opcode);
		fprintf(stderr, "L%lu: usage: push integer\n", line_number);
		return (0);
	}
	num = atoi(arg);
	if (num == 0)
	{
		free(opcode);
		free(arg);
		fprintf(stderr, "L%lu: usage: push integer\n", line_number);
		return (0);
	}
	new = (stack_t *) malloc(sizeof(stack_t));
	if (new == NULL)
	{
		free(opcode);
		free(arg);
		fprintf(stderr, "Error: malloc failed");
		return (0);
	}
	new->n = num;
	new->prev = NULL;
	new->next = NULL;
	if (*stack == NULL)
		*stack = new;
	else
	{
		new->prev = *stack;
		(*stack)->next = new;
		*stack = new;
	}
	free(opcode);
	free(arg);
	return (1);
}

/**
 * other_op - performs various other op instructions
 * @stk: top of stack
 * @op_c: operation code
 * @oparr: array containing opcodes and associated functions
 * @l_n: line number read from script
 *
 * Return: 1 if succesful and 0 otherwise
 */
ssize_t other_op(stack_t **stk, char *op_c, instruction_t **oparr, ssize_t l_n)
{
	int num, found = 0;

	for (num = 0; oparr[num] != NULL; num++)
	{
		if (strcmp(op_c, (oparr[num])->opcode) == 0)
		{
			if (oparr[num]->f != NULL)
				oparr[num]->f(stk, l_n);
			found = 1;
			break;
		}
	}
	if (found == 0)
	{
		free(op_c);
		fprintf(stderr, "L%lu: unknown instruction %s\n", l_n, op_c);
		return (0);
	}
	free(op_c);
	return (1);
}

/**
 * create_oplist - creates an array of instruction_t data for opcodes
 *
 * Return: return a pointer to an array of instructions with matcged opcodes
 */
instruction_t **create_oplist()
{
	instruction_t **oplist = malloc(7 * sizeof(instruction_t));

	if (oplist == NULL)
		print_mal_err();
	add_inst(oplist[0], "pall", &print_stack);
	add_inst(oplist[1], "pop", &pop_stack);
	add_inst(oplist[2], "pint", &pint_stack);
	add_inst(oplist[3], "swap", &swap_stack);
	add_inst(oplist[4], "add", &add_stack);
	add_inst(oplist[5], "nop", NULL);
	oplist[6] = NULL;
	return (oplist);
}

/**
 * free_all - frees dynamic allocated memory
 * @oplist: instruction data array
 * @stack:stack linked list
 */
void free_all(instruction_t **oplist, stack_t *stack)
{
	free_stack(stack);
	free_inst(oplist);
}

/**
 * main - main monty function
 * @argc: arg count
 * @argv: arg vector
 *
 * Return: 0 if succesful
 */
int main(int argc, char **argv)
{
	FILE *script;
	ssize_t line_number = 1, check, valid;
	stack_t *stack = NULL;
	instruction_t **oplist;
	char *buf, *opcode = NULL, *arg = NULL;

	if (argc != 2)
		print_usage_err();
	script = fopen(argv[1], "r");
	if (script == NULL)
		print_file_err(argv[1]);
	oplist = create_oplist();
	buf = malloc(256 * sizeof(char));
	if (buf == NULL)
		print_mal_err();
	while ((fgets(buf, 256, script)) != NULL)
	{
		valid = 0;
		check = tokenize(buf, opcode, arg);
		if (check == 1)
			continue;
		else if (check == -1)
		{
			free_all(oplist, stack);
			print_mal_err();
		}
		if (strcmp(opcode, "push") == 0)
			valid = push_op(&stack, arg, line_number, opcode);
		else
			valid = other_op(&stack, opcode, oplist, line_number);
		if (valid != 1)
		{
			free_all(oplist, stack);
			exit(EXIT_FAILURE);
		}
		line_number++;
	}
	free_all(oplist, stack);
	exit(EXIT_SUCCESS);

