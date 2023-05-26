#include "monty.h"

/**
 * pop_stack - deletes the node at rear of list
 * @stack: pointer to rear node of linked list
 * @line_number: line number read from script
 */
void pop_stack(stack_t **stack, unsigned int line_number)
{
	stack_t *r;

	if (stack == NULL || *stack == NULL)
	{
		fprintf(stderr, "L%d: can't pop an empty stack", line_number);
		exit(EXIT_FAILURE);
	}
	r = *stack;
	*stack = r->prev;
	free(r);
}
