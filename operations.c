#include "monty.h"

/**
 * pint_stack - prints the value at the top of the stack
 * @stack: pointer to stack
 * @line_number: line number read from script
 */
void pint_stack(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	printf("%d\n", (*stack)->n);
}

/**
 * swap_stack - swaps the top two elements of the stack
 * @stack: pointer to stack
 * @line_number: line number read from script
 */
void swap_stack(stack_t **stack, unsigned int line_number)
{
	stack_t *prev = (*stack)->prev, *temp = *stack;
	unsigned int num = line_number;

	if ((*stack)->prev == NULL)
	{
		free_stack(*stack);
		fprintf(stderr, "L%u: can't swap, stack too short\n", num);
		exit(EXIT_FAILURE);
	}
	prev->next = NULL;
	temp->prev = prev->prev;
	prev->prev->next = temp;
	prev->prev = temp;
	temp->next = prev;
	*stack = prev;
}

/**
 * add_stack -  adds the top two elements of the stack_
 * @stack: pointer to stack
 * @line_number: line number read from script
 */
void add_stack(stack_t **stack, unsigned int line_number)
{
	unsigned int num = line_number;
	int integer;
	stack_t *prev = (*stack)->prev, *new, *temp = *stack;

	if ((*stack)->prev == NULL)
	{
		free_stack(*stack);
		fprintf(stderr, "L%u: can't swap, stack too short\n", num);
		exit(EXIT_FAILURE);
	}
	integer = prev->n + (*stack)->n;
	new = malloc(sizeof(stack_t));
	if (new == NULL)
	{
		free_stack(*stack);
		print_mal_err();
	}
	new->n = integer;
	new->prev = prev->prev;
	new->next = NULL;
	*stack = new;
	free(prev);
	free(temp);
}
