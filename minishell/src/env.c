/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/07 12:05:01 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/07 16:26:51 by tdefresn         ###   ########.fr       */
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

static void		clear_env_datas(t_env_datas *env_datas)
{
	int		i;

	i = 0;
	if (env_datas->environ)
	{
		while (env_datas->environ[i])
			ft_strdel(&env_datas->environ[i++]);
	}
}

static int		count_pairs(char **argv)
{
	int		i;

	i = 0;
	while (argv[i] && ft_strchr(argv[i], '='))
		i++;
	return (i);
}

static void		fetch_pairs(char **argv, t_env_datas *env_datas)
{
	int		i;

	env_datas->environ = (char **)ft_memalloc(sizeof(char *) * (count_pairs(argv) + 1));
	i = 0;
	while (argv[i] && ft_strchr(argv[i], '='))
	{
		env_datas->environ[i] = ft_strdup(argv[i]);
		i++;
	}
	if (argv[i])
		env_datas->utility = &argv[i];
}

/*
**	'env ./minishell'
**	should act as './minishell'
*/
static void		read_flags(char **argv, t_env_datas *env_datas)
{
	int		i;

	i = 0;
	while (argv[i] && argv[i][0] == '-')
	{
		if (argv[i][1] == '\0')
			break ;
		if (argv[i] && ft_strchr(argv[i], 'i'))
			fetch_pairs(&argv[i + 1], env_datas);
		if (argv[i] && ft_strchr(argv[i], 'v'))
			ft_printf("env: verbose mode not implemented\n", PROGRAM_NAME);
		if (argv[i] && ft_strchr(argv[i], 'P'))
		{
			ft_printf("env: alternate path not implemented\n", PROGRAM_NAME);
			i += 2;
			continue ;
		}
		if (argv[i] && ft_strchr(argv[i], 'S'))
		{
			ft_printf("env: split string not implemented\n", PROGRAM_NAME);
			i += 2;
			continue ;
		}
		if (argv[i] && ft_strchr(argv[i], 'u'))
		{
			ft_printf("env: pre-unset not implemented\n", PROGRAM_NAME);
			i += 2;
			continue ;
		}
		i++;
	}
}

void			env(char **argv, t_sh_datas *sh_datas)
{
	t_env_datas		env_datas;

	env_datas.environ = NULL;
	env_datas.utility = NULL;
	read_flags(&argv[1], &env_datas);
	if (env_datas.utility)
		run_exec(env_datas.utility, sh_datas,
				(env_datas.environ) ? env_datas.environ : NULL);
	else
		print_environ((env_datas.environ) ? env_datas.environ : sh_datas->environ);
	clear_env_datas(&env_datas);
}
