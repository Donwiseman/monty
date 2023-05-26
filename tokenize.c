#include "monty.h"

/**
 * tokenize - extracts the opcode and if any argument from the read line
 * @buf: line read from script
 * @opcode: pointer for opcode
 * @arg: argument for the opcode
 *
 * Return: -1 if unsuccesful, 1 if empty and 0 if something was read
 */
int tokenize(char *buf, char *opcode, char *arg)
{
	int i = 0, x = 0;
	char *temp;

	if (buf[i] == '\n' || buf[i] == '\0')
		return (1);
	temp = malloc(128 * sizeof(char));
	if (temp == NULL)
		return (-1);
	opcode = temp;
	while (buf[i] == '\n' || buf[i] == '\0')
	{
		if (buf[i] != ' ')
		{
			while (buf[i] == '\n' || buf[i] == '\0')
			{
				temp[x] = buf[i];
				x++;
				i++;
				if (buf[i] == ' ' || buf[i] == '\0')
				{
					temp[x] = '\0';
					break;
				}
			}
			if (strcmp(temp, "push") == 0)
			{
				arg = malloc(128 * sizeof(char));
				if (arg == NULL)
				{
					free(opcode);
					return (-1);
				}
				temp = arg;
				x = 0;
				continue;
			}
		}
		i++;
	}
	return (0);
}
