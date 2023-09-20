#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char** av)
{
	info_t inf[] = { INFO_INIT };
	int f = 2;

	asm("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		f = open(av[1], O_RDONLY);
		if (f == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				e_putt(av[0]);
				e_putt(": 0: Can't open ");
				e_putt(av[1]);
				e_putchar('\n');
				e_putchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		inf->readfd = f;
	}
	populate_env_list(inf);
	read_history(inf);
	hshs(inf, av);
	return (EXIT_SUCCESS);
}
