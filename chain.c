#include "shell.h"

/**
 * is_chainn - test if current char in buffer is a chain delimeter
 * @inf: the parameter struct
 * @buff: the char buffer
 * @pbuf: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chainn(info_t* inf, char* buff, size_t* pbuf)
{
	size_t j = *p;

	if (buff[j] == '|' && buff[j + 1] == '|')
	{
		buff[j] = 0;
		j++;
		inf->cmd_buf_type = CMD_OR;
	}
	else if (buff[j] == '&' && buff[j + 1] == '&')
	{
		buff[j] = 0;
		j++;
		inf->cmd_buf_type = CMD_AND;
	}
	else if (buff[j] == ';') /* found end of this command */
	{
		buff[j] = 0; /* replace semicolon with null */
		inf->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chainn - checks we should continue chaining based on last status
 * @inf: the parameter struct
 * @buff: the char buffer
 * @pbuf: address of current position in buf
 * @ibuf: starting position in buf
 * @lenbuf: length of buf
 *
 * Return: Void
 */
void check_chainn(info_t* inf, char* buff, size_t* pbuf, size_t ibuf, size_t lenbuf)
{
	size_t j = *p;

	if (inf->cmd_buf_type == CMD_AND)
	{
		if (inf->status)
		{
			buff[ibuf] = 0;
			j = lenbuf;
		}
	}
	if (inf->cmd_buf_type == CMD_OR)
	{
		if (!inf->status)
		{
			buff[ibuf] = 0;
			j = lenbuf;
		}
	}

	*p = j;
}

/**
 * replace_aliass - replaces an aliases in the tokenized string
 * @inf: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_aliass(info_t* inf)
{
	int i;
	list_t* node;
	char* p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(inf->alias, inf->argv[0], '=');
		if (!node)
			return (0);
		free(inf->argv[0]);
		p = string_chr(node->str, '=');
		if (!p)
			return (0);
		p = string_dup(p + 1);
		if (!p)
			return (0);
		inf->argv[0] = p;
	}
	return (1);
}

/**
 * replace_varss - replaces vars in the tokenized string
 * @inf: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_varss(info_t* inf)
{
	int i = 0;
	list_t* node;

	for (i = 0; inf->argv[i]; i++)
	{
		if (inf->argv[i][0] != '$' || !inf->argv[i][1])
			continue;

		if (!string_cmp(inf->argv[i], "$?"))
		{
			replace_string(&(inf->argv[i]),
				string_dup(convert_numbers(inf->status, 10, 0)));
			continue;
		}
		if (!string_cmp(inf->argv[i], "$$"))
		{
			replace_string(&(inf->argv[i]),
				string_dup(convert_numbers(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(inf->env, &inf->argv[i][1], '=');
		if (node)
		{
			replace_string(&(inf->argv[i]),
				string_dup(string_chr(node->str, '=') + 1));
			continue;
		}
		replace_string(&inf->argv[i], string_dup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char** old, char* new)
{
	free(*old);
	*old = new;
	return (1);
}

