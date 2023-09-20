#include "shell.h"

/**
 * erra_toint - converts a string to an integer
 * @s1: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int erra_toint(char* s1)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s1 == '+')
		s1++;  /* TODO: why does this make main return 255? */
	for (i = 0; s1[i] != '\0'; i++)
	{
		if (s1[i] >= '0' && s1[i] <= '9')
		{
			result *= 10;
			result += (s1[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_err - prints an error message
 * @inf: the parameter & return info struct
 * @es: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_err(info_t* inf, char* es)
{
	e_putt(inf->fname);
	e_putt(": ");
	print_dc(inf->line_count, STDERR_FILENO);
	e_putt(": ");
	e_putt(inf->argv[0]);
	e_putt(": ");
	e_putt(es);
}

/**
 * print_dc - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_dc(int input, int f)
{
	int (*put_char)(char) = put_char;
	int i, count = 0;
	unsigned int _abs_, current;

	if (f == STDERR_FILENO)
		put_char = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		put_char('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			put_char('0' + current / i);
			count++;
		}
		current %= i;
	}
	put_char('0' + current);
	count++;

	return (count);
}

/**
 * convert_numbers - converter function, a clone of itoa
 * @num1: number
 * @bs: base
 * @flag: argument flags
 *
 * Return: string
 */
char* convert_numbers(long int num1, int bs, int flag)
{
	static char* array;
	static char buffer[50];
	char sign = 0;
	char* ptr;
	unsigned long n = num1;

	if (!(flag & CONVERT_UNSIGNED) && num1 < 0)
	{
		n = -num1;
		sign = '-';

	}
	array = flag & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % bs];
		n /= bs;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comment - function replaces first instance of '#' with '\0'
 * @buff: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comment(char* buff)
{
	int i;

	for (i = 0; buff[i] != '\0'; i++)
		if (buff[i] == '#' && (!i || buff[i - 1] == ' '))
		{
			buff[i] = '\0';
			break;
		}
}
