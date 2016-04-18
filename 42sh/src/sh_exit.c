/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/10 16:33:45 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/10 16:43:31 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	ft_strdel(&sh_datas->prompt);
	exit(errno);
}

void			sh_exit(char **argv, t_sh_datas *sh_datas)
{
	int		i;

	ft_putendl("exit");
	if (argv && argv[1])
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
		quit(ft_atoi(argv[1]), sh_datas);
	}
	quit(0, sh_datas);
}
