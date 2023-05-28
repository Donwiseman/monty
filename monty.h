#ifndef MONTY_H
#define MONTY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

extern instruction_t **oplist;
instruction_t **oplist;
void create_oplist(void);
void print_stack(stack_t **stack, unsigned int line_number);
void free_stack(stack_t *rear);
void free_all(stack_t **stack, char *opcode, char *arg);
void pop_stack(stack_t **stack, unsigned int line_number);
int tokenize(char *buf, char **opcode, char **arg);
void add_inst(instruction_t **d, char *oc, void (*f)(stack_t**, unsigned int));
void free_inst(void);
void print_file_err(char *file);
void print_usage_err(void);
void print_mal_err(void);
void pint_stack(stack_t **stack, unsigned int line_number);
void swap_stack(stack_t **stack, unsigned int line_number);
void add_stack(stack_t **stack, unsigned int line_number);
void sub_stack(stack_t **stack, unsigned int line_number);
void mul_stack(stack_t **stack, unsigned int line_number);
void div_stack(stack_t **stack, unsigned int line_number);
void mod_stack(stack_t **stack, unsigned int line_number);
void pchar(stack_t **stack, unsigned int line_number);
void pstr(stack_t **stack, unsigned int line_number);
void rotr(stack_t **stack, unsigned int line_number);
void rotl(stack_t **stack, unsigned int line_number);
void check_arg(stack_t **stack, unsigned int line_number, char *op, char *arg);

#endif
