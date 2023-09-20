#include "shell.h"

/**
 * pfree - frees a pointer and NULLs the address
 * @ptr1: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int pfree(void** ptr1)
{
	if (ptr1 && *ptr1)
	{
		free(*ptr1);
		*ptr1 = NULL;
		return (1);
	}
	return (0);
}

