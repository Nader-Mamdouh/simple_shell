#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t* info, char* path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char* dup_chars(char* pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_cmdpath - finds this cmd in the PATH string
 * @inf: the info struct
 * @paths1: the PATH string
 * @cmd1: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char* find_cmdpath(info_t* inf, char* paths1, char* cmd1)
{
	int i = 0, curr_pos = 0;
	char* path;

	if (!paths1)
		return (NULL);
	if ((string_len(cmd1) > 2) && start_with(cmd1, "./"))
	{
		if (is_cmd(inf, cmd1))
			return (cmd1);
	}
	while (1)
	{
		if (!paths1[i] || paths1[i] == ':')
		{
			path = dup_chars(paths1, curr_pos, i);
			if (!*path)
				string_cat(path, cmd1);
			else
			{
				string_cat(path, "/");
				string_cat(path, cmd1);
			}
			if (is_cmd(inf, path))
				return (path);
			if (!paths1[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

