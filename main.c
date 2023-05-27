#include "monty.h"

/**
 * free_all - frees dynamic allocated memory
 * @stack:stack linked list
 * @opcode: operation code
 * @arg: argument to opcode if available
 */
void free_all(stack_t **stack, char *opcode, char *arg)
{
	if (arg != NULL)
		free(arg);
	if (opcode != NULL)
		free(opcode);
	free_stack(*stack);
	free_inst();
}

/**
 * push_op - performs the push operation
 * @stack: pointer to stack
 * @arg: arg to push
 * @ln: line number read from script
 * @opcode: operation code "push"
 *
 * Return: nothing
 */
void push_op(stack_t **stack, char *arg, ssize_t ln, char *opcode)
{
	int num = atoi(arg), x;
	stack_t *new;

	if (arg == NULL)
	{
		free_all(stack, opcode, arg);
		fprintf(stderr, "L%lu: usage: push integer\n", ln);
		exit(EXIT_FAILURE);
	}
	for (x = 0; arg[x] != '\0'; x++)
	{
		if ((arg[x] < 48 || arg[x] > 57) && arg[x] != '-')
		{
			free_all(stack, opcode, arg);
			fprintf(stderr, "L%lu: usage: push integer\n", ln);
			exit(EXIT_FAILURE);
		}
	}
	new = (stack_t *) malloc(sizeof(stack_t));
	if (new == NULL)
	{
		free_all(stack, opcode, arg);
		print_mal_err();
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
}

/**
 * other_op - performs various other op instructions
 * @stk: top of stack
 * @op_c: operation code
 * @oparr: array containing opcodes and associated functions
 * @l_n: line number read from script
 *
 * Return: nothing
 */
void other_op(stack_t **stk, char *op_c, instruction_t **oparr, ssize_t l_n)
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
		fprintf(stderr, "L%lu: unknown instruction %s\n", l_n, op_c);
		free_all(stk, op_c, NULL);
		exit(EXIT_FAILURE);
	}
	free(op_c);
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
	ssize_t line_number = 1, check;
	stack_t *stack = NULL;
	char *buf, *opcode = NULL, *arg = NULL;

	if (argc != 2)
		print_usage_err();
	script = fopen(argv[1], "r");
	if (script == NULL)
		print_file_err(argv[1]);
	create_oplist();
	buf = malloc(256 * sizeof(char));
	if (buf == NULL)
		print_mal_err();
	while ((fgets(buf, 256, script)) != NULL)
	{
		check = tokenize(buf, &opcode, &arg);
		if (check == 1)
			continue;
		else if (check == -1)
		{
			free_all(&stack, NULL, NULL);
			print_mal_err();
		}
		if (strcmp(opcode, "push") == 0)
			push_op(&stack, arg, line_number, opcode);
		else
			other_op(&stack, opcode, oplist, line_number);
		line_number++;
	}
	fclose(script);
	free(buf);
	free_all(&stack, NULL, NULL);
	exit(EXIT_SUCCESS);
}
