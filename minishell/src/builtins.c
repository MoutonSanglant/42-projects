/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/04 21:04:51 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/06 14:16:04 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		print_environ(char **environ)
{
	int		i;

	i = 0;
	while (environ[i])
		ft_printf("%s\n", environ[i++]);
}

static void		quit(int errno, t_sh_datas *sh_datas)
{
	int		i;

	i = 0;
	while (sh_datas->environ[i])
	{
		ft_strdel(&sh_datas->environ[i]);
		i++;
	}
	ft_memdel((void **)&sh_datas->environ);
	exit(errno);
}

static int		builtin_exit(char **argv, t_sh_datas *sh_datas)
{
	int		i;

	ft_putendl("exit");
	if (argv[1])
	{
		i = 0;
		while (argv[1][i])
		{
			if (!ft_isdigit(argv[1][i]))
			{
				ft_printf("%s: quit: %s: numeric argument required\n",
							PROGRAM_NAME, argv[1]);
				quit(255, sh_datas);
			}
			i++;
		}
		if (argv[2])
		{
			ft_printf("%s: quit: too many arguments\n", PROGRAM_NAME);
			return (1);
		}
		quit(ft_atoi(argv[1]), sh_datas);
	}
	quit(0, sh_datas);
	return (0);
}

int				check_builtins(char **argv, t_sh_datas *sh_datas)
{
	int n;

	n = 2;
	if (!argv[0])
		return (0);
	if (!ft_strcmp(argv[0], "cd"))
		cd(argv[1], sh_datas);
	else if (!ft_strcmp(argv[0], "env"))
	{
		if (argv[1])
			run_process(argv[n], &argv[n + 1], sh_datas->environ);
		else
			print_environ(sh_datas->environ);
	}
	else if (!ft_strcmp(argv[0], "setenv"))
	{
		if (!(argv[1] && argv[2]))
			return (1);
		sh_datas->environ = set_environ(sh_datas->environ, argv[1], argv[2], 1);
	}
	else if (!ft_strcmp(argv[0], "unsetenv"))
	{
		if (!argv[1])
			return (1);
		sh_datas->environ = unset_environ(sh_datas->environ, argv[1]);
	}
	else if (!ft_strcmp(argv[0], "exit"))
		return (builtin_exit(argv, sh_datas));
	else
		return (-1);
	return (0);
}
