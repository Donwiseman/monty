#include "monty.h"

/**
 * rotr - moves the bottom element to the top
 * @stack: pointer to top element of stack
 * @line_number: line number of script opcode was gotten
 */
void rotr(stack_t **stack, unsigned int line_number)
{
	stack_t *last = *stack, *top = *stack;

	(void) line_number;
	if (*stack == NULL || (*stack)->prev == NULL)
		return;
	while (last->prev != NULL)
		last = last->prev;
	last->next->prev = NULL;
	last->next = NULL;
	top->next = last;
	last->prev = top;
	*stack = last;
}

/**
 * rotl - moves the top element to the bottom
 * @stack: pointer to top element of stack
 * @line_number: line number of script opcode was gotten
 */
void rotl(stack_t **stack, unsigned int line_number)
{
	stack_t *last = *stack, *top = *stack, *second;

	(void) line_number;
	if (*stack == NULL || (*stack)->prev == NULL)
		return;
	while (last->prev != NULL)
		last = last->prev;
	second = top->prev;
	second->next = NULL;
	top->prev = NULL;
	last->prev = top;
	top->next = last;
	*stack = second;
}
