#include "shell.h"

/**
 * intractiv - returns true if shell is interactive mode
 * @inf: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int intractiv(info_t* inf)
{
	return (isatty(STDIN_FILENO) && inf->readfd <= 2);
}

/**
 * is_delimeter - checks if character is a delimeter
 * @ch: the char to check
 * @dm: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delimeter(char ch, char* dm)
{
	while (*dm)
		if (*dm++ == ch)
			return (1);
	return (0);
}

/**
 *is_alpha - checks for alphabetic character
 *@ch: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int is_alpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *strtoint - converts a string to an integer
 *@s1: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int strtoint(char* s1)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s1[i] != '\0' && flag != 2; i++)
	{
		if (s1[i] == '-')
			sign *= -1;

		if (s1[i] >= '0' && s1[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s1[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

