#include "shell.h"

/**
 * **stow - devide a string into words.
 * @s1: the input string
 * @s2: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char** stow(char* s1, char* s2)
{
	int i, j, k, m, numwords = 0;
	char** s;

	if (s1 == NULL || s1[0] == 0)
		return (NULL);
	if (!s2)
		s2 = " ";
	for (i = 0; s1[i] != '\0'; i++)
		if (!is_delimeter(s1[i], s2) && (is_delimeter(s1[i + 1], s2) || !s1[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char*));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delimeter(s1[i], s2))
			i++;
		k = 0;
		while (!is_delimeter(s1[i + k], s2) && s1[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = s1[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **stow2 - devide a string into words
 * @s1: the input string
 * @s2: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */

char** stow2(char* s1, char s2)
{
	int i, j, k, m, numwords = 0;
	char** s;

	if (s1 == NULL || s1[0] == 0)
		return (NULL);
	for (i = 0; s1[i] != '\0'; i++)
		if ((s1[i] != s2 && s1[i + 1] == s2) ||
			(s1[i] != s2 && !s1[i + 1]) || s1[i + 1] == s2)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char*));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (s1[i] == s2 && s1[i] != s2)
			i++;
		k = 0;
		while (s1[i + k] != s2 && s1[i + k] && s1[i + k] != s2)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = s1[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
