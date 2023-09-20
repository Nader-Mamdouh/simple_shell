#include "shell.h"

/**
 * my_history - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @inf: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int my_history(info_t* inf)
{
	print_list(inf->history);
	return (0);
}

/**
 * unset_aliass - sets alias to string
 * @inf: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_aliass(info_t* inf, char* s1)
{
	char* p, c;
	int ret;

	p = string_chr(s1, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(inf->alias),
		get_node_index(inf->alias, node_starts_with(inf->alias, s1, -1)));
	*p = c;
	return (ret);
}

/**
 * set_aliass - sets alias to string
 * @inf: parameter struct
 * @s2: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_aliass(info_t* inf, char* s2)
{
	char* p;

	p = string_chr(s2, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_aliass(inf, s2));

	unset_aliass(inf, s2);
	return (add_node_end(&(inf->alias), s2, 0) == NULL);
}

/**
 * print_aliass - prints an alias string
 * @nd: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_aliass(list_t* nd)
{
	char* p = NULL, * a = NULL;

	if (nd)
	{
		p = string_chr(nd->str, '=');
		for (a = nd->str; a <= p; a++)
			put_char(*a);
		put_char('\'');
		putt(p + 1);
		putt("'\n");
		return (0);
	}
	return (1);
}

/**
 * myaliass - mimics the alias builtin (man alias)
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int myaliass(info_t* inf)
{
	int i = 0;
	char* p = NULL;
	list_t* node = NULL;

	if (inf->argc == 1)
	{
		node = inf->alias;
		while (node)
		{
			print_aliass(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; inf->argv[i]; i++)
	{
		p = string_chr(inf->argv[i], '=');
		if (p)
			set_aliass(inf, inf->argv[i]);
		else
			print_aliass(node_starts_with(inf->alias, inf->argv[i], '='));
	}

	return (0);
}
