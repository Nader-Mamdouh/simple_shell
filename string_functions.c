#include "shell.h"

/**
 * string_len - returns the length of a string
 * @s1: the string whose length to check
 *
 * Return: integer length of string
 */
int string_len(char* s1)
{
	int i = 0;

	if (!s1)
		return (0);

	while (*s1++)
		i++;
	return (i);
}

/**
 * string_cmp - performs lexicogarphic comparison of two strangs.
 * @s11: the first strang
 * @s22: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int string_cmp(char* s11, char* s22)
{
	while (*s11 && *s22)
	{
		if (*s11 != *s22)
			return (*s11 - *s22);
		s11++;
		s22++;
	}
	if (*s11 == *s22)
		return (0);
	else
		return (*s11 < *s22 ? -1 : 1);
}

/**
 * start_with - checks if needle starts with haystack
 * @ss: string to search
 * @nd: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char* start_with(const char* ss, const char* nd)
{
	while (*nd)
		if (*nd++ != *ss++)
			return (NULL);
	return ((char*)ss);
}

/**
 * string_cat - concatenates two strings
 * @d: the destination buffer
 * @s1: the source buffer
 *
 * Return: pointer to destination buffer
 */
char* string_cat(char* d, char* s1)
{
	char* ret = d;

	while (*d)
		d++;
	while (*s1)
		*d++ = *s1++;
	*d = *s1;
	return (ret);
}
