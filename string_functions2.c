
#include "shell.h"

/**
 * string_cpy - copies a string
 * @d: the destination
 * @s1: the source
 *
 * Return: pointer to destination
 */
char* string_cpy(char* d, char* s1)
{
	int i = 0;

	if (d == s1 || s1 == 0)
		return (d);
	while (s1[i])
	{
		d[i] = s1[i];
		i++;
	}
	d[i] = 0;
	return (d);
}

/**
 * string_dup - duplicates a string
 * @s1: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char* string_dup(const char* s1)
{
	int length = 0;
	char* ret;

	if (s1 == NULL)
		return (NULL);
	while (*s1++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--s1;
	return (ret);
}

/**
 *putt - prints an input string
 *@s1: the string to be printed
 *
 * Return: Nothing
 */
void putt(char* s1)
{
	int i = 0;

	if (!s1)
		return;
	while (s1[i] != '\0')
	{
		put_char(s1[i]);
		i++;
	}
}

/**
 * put_char - writes the character c to stdout
 * @ch: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int put_char(char ch)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
		buf[i++] = ch;
	return (1);
}

