#include "shell.h"

/**
 **string_cpy - copies a string
 *@d: the destination string to be copied to
 *@s1: the source string
 *@a: the amount of characters to be copied
 *Return: the concatenated string
 */
char* string_cpy(char* d, char* s1, int a)
{
	int i, j;
	char* s = d;

	i = 0;
	while (s1[i] != '\0' && i < a - 1)
	{
		d[i] = s1[i];
		i++;
	}
	if (i < a)
	{
		j = i;
		while (j < a)
		{
			d[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 ** string_cat - concatenates two strings
 *@d: the first string
 *@s1: the second string
 *@a: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char* string_cat(char* d, char* s, int a)
{
	int i, j;
	char* s = d;

	i = 0;
	j = 0;
	while (d[i] != '\0')
		i++;
	while (s[j] != '\0' && j < a)
	{
		d[i] = s[j];
		i++;
		j++;
	}
	if (j < a)
		d[i] = '\0';
	return (s);
}

/**
 **string_chr - locates a character in a string
 *@s1: the string to be parsed
 *@ch: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char* string_chr(char* s1, char ch)
{
	do {
		if (*s1 == ch)
			return (s1);
	} while (*s1++ != '\0');

	return (NULL);
}
