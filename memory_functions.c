#include "shell.h"

/**
 **_memset - fills memory with a constant byte
 *@pa: the pointer to the memory area
 *@bs: the byte to fill *s with
 *@by: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char* mem_set(char* pa, char bs, unsigned int by)
{
	unsigned int i;

	for (i = 0; i < by; i++)
		pa[i] = bs;
	return (pa);
}

/**
 * ffree - frees a string of strings
 * @ss: string of strings
 */
void f_free(char** ss)
{
	char** a = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(a);
}

/**
 * real_location - reallocates a block of memory
 * @ptr1: pointer to previous malloc'ated block
 * @size1: byte size of previous block
 * @size2: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void* real_location(void* ptr1, unsigned int size1, unsigned int size2)
{
	char* p;

	if (!ptr1)
		return (malloc(size2));
	if (!size2)
		return (free(ptr1), NULL);
	if (size2 == size1)
		return (ptr1);

	p = malloc(size2);
	if (!p)
		return (NULL);

	size1 = size1 < size2 ? size1 : size2;
	while (size1--)
		p[size1] = ((char*)ptr1)[size1];
	free(ptr1);
	return (p);
}
