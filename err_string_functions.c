#include "shell.h"

/**
 *e_putt - prints an input string
 * @s: the string to be printed
 *
 * Return: Nothing
 */
void e_putt(char* s)
{
	int i = 0;

	if (!s)
		return;
	while (s[i] != '\0')
	{
		e_putchar(s[i]);
		i++;
	}
}

/**
 * e_putchar - writes the character c to stderr
 * @ch: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int e_putchar(char ch)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
		buf[i++] = ch;
	return (1);
}

/**
 * put_fd - writes the character c to given fd
 * @ch: The character to print
 * @f: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int put_fd(char ch, int f)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(f, buf, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
		buf[i++] = ch;
	return (1);
}

/**
 * put_sfd - prints an input string
 * @s: the string to be printed
 * @f: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int put_sfd(char* s, int f)
{
	int i = 0;

	if (!s)
		return (0);
	while (*s)
	{
		i += put_fd(*s++, f);
	}
	return (i);
}

