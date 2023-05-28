#include "monty.h"

/**
 * div_stack -  divides the second stack element by the top element and
 * removes the top element euqting the second to th result.
 * @stack: pointer to stack
 * @line_number: line number read from script
 */
void div_stack(stack_t **stack, unsigned int line_number)
{
	unsigned int num = line_number;
	int integer;
	stack_t *prev, *temp = *stack;

	if (*stack == NULL || (*stack)->prev == NULL)
	{
		free_all(stack, NULL, NULL);
		fprintf(stderr, "L%u: can't div, stack too short\n", num);
		exit(EXIT_FAILURE);
	}
	if ((*stack)->n == 0)
	{
		free_all(stack, NULL, NULL);
		fprintf(stderr, "L%u: division by zero\n", num);
		exit(EXIT_FAILURE);
	}
	prev = (*stack)->prev;
	integer = prev->n / (*stack)->n;
	prev->n = integer;
	prev->next = NULL;
	*stack = prev;
	free(temp);
}

/**
 * mod_stack - finds the remainder from division of the top two elements
 * @stack: pointer to stack
 * @line_number: line number read from script
 */
void mod_stack(stack_t **stack, unsigned int line_number)
{
	unsigned int num = line_number;
	int integer;
	stack_t *prev, *temp = *stack;

	if (*stack == NULL || (*stack)->prev == NULL)
	{
		free_all(stack, NULL, NULL);
		fprintf(stderr, "L%u: can't mod, stack too short\n", num);
		exit(EXIT_FAILURE);
	}
	if ((*stack)->n == 0)
	{
		free_all(stack, NULL, NULL);
		fprintf(stderr, "L%u: division by zero\n", num);
		exit(EXIT_FAILURE);
	}
	prev = (*stack)->prev;
	integer = prev->n % (*stack)->n;
	prev->n = integer;
	prev->next = NULL;
	*stack = prev;
	free(temp);
}
