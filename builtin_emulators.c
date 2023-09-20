i#include "shell.h"

/**
 * my_exit - exits the shell
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int my_exit(info_t* inf)
{
	int exitcheck;

	if (inf->argv[1])  
	{
		exitcheck = erra_toint(inf->argv[1]);
		if (exitcheck == -1)
		{
			inf->status = 2;
			print_err(inf, "Illegal number: ");
			e_putt(inf->argv[1]);
			e_putchar('\n');
			return (1);
		}
		inf->err_num = erra_toint(inf->argv[1]);
		return (-2);
	}
	inf->err_num = -1;
	return (-2);
}

/**
 * my_cd - changes the current directory of the process
 * @inf: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int my_cd(info_t* inf)
{
	char* s, * dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		putt("TODO: >>getcwd failure emsg here<<\n");
	if (!inf->argv[1])
	{
		dir = get_env(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
			chdir((dir = get_env(inf, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (string_cmp(inf->argv[1], "-") == 0)
	{
		if (!get_env(info, "OLDPWD="))
		{
			putt(s);
			put_char('\n');
			return (1);
		}
		putt(get_env(info, "OLDPWD=")), put_char('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = get_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_err(info, "can't cd to ");
		e_putt(info->argv[1]), e_putchar('\n');
	}
	else
	{
		set_env(info, "OLDPWD", get_env(info, "PWD="));
		set_env(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * my_help - changes the current directory of the process
 * @inf0: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int my_help(info_t* inf)
{
	char** arg_array;

	arg_array = inf->argv;
	putt("help call works. Function not yet implemented \n");
	if (0)
		putt(*arg_array); /* temp att_unused workaround */
	return (0);
}
