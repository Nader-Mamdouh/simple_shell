#include "shell.h"

/**
 * clear_info - initializes info_t struct
 * @info: struct address
 */
void clear_info(info_t* info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void set_info(info_t* inf, char** av)
{
	int i = 0;

	inf->fname = av[0];
	if (inf->arg)
	{
		inf->argv = stow(inf->arg, " \t");
		if (!inf->argv)
		{

			inf->argv = malloc(sizeof(char*) * 2);
			if (inf->argv)
			{
				inf->argv[0] = string_dup(inf->arg);
				inf->argv[1] = NULL;
			}
		}
		for (i = 0; inf->argv && inf->argv[i]; i++)
			;
		inf->argc = i;

		replace_aliass(inf);
		replace_varss(inf);
	}
}

/**
 * free_info - frees info_t struct fields
 * @inf: struct address
 * @al: true if freeing all fields
 */
void free_info(info_t* inf, int al)
{
	f_free(inf->argv);
	inf->argv = NULL;
	inf->path = NULL;
	if (al)
	{
		if (!inf->cmd_buf)
			free(inf->arg);
		if (inf->env)
			free_list(&(inf->env));
		if (inf->history)
			free_list(&(inf->history));
		if (inf->alias)
			free_list(&(inf->alias));
		f_free(inf->environ);
		inf->environ = NULL;
		pfree((void**)inf->cmd_buf);
		if (inf->readfd > 2)
			close(inf->readfd);
		put_char(BUF_FLUSH);
	}
}
