#include "monty.h"

/**
 * print_stack -  prints all the elements of a dlistint_t list.
 * @stack: top of double stack
 * @line_number: line number read from script
 */
void print_stack(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = *stack;
	(void) line_number;

	if (temp != NULL && temp->next == NULL)
	{
		while (temp != NULL)
		{
			printf("%d\n", temp->n);
			temp = temp->prev;
		}
	}
}
