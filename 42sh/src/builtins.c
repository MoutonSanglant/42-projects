/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/04 21:04:51 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/25 16:44:22 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int				call_builtin_exit(char **argv, t_sh_datas *sh_datas)
{
	if (!(argv[1] && argv[2]))
		sh_exit(argv, sh_datas);
	else
		ft_printf("%s: quit: too many arguments\n", PROGRAM_NAME);
	return (1);
}

int				check_builtins(char **argv, t_sh_datas *sh_datas)
{
	if (!argv[0])
		return (0);
	if (!ft_strcmp(argv[0], "cd"))
		cd(argv[1], sh_datas);
	else if (!ft_strcmp(argv[0], "env"))
		env(argv, sh_datas);
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
		return (call_builtin_exit(argv, sh_datas));
	else
		return (-1);
	return (0);
}
