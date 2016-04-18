/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/07 12:05:01 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/10 17:15:35 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		clear_environ(char **environ)
{
	int		i;

	i = 0;
	while (environ[i])
		ft_strdel(&environ[i++]);
	ft_memdel((void **)&environ);
}

static void		print_environ(char **environ)
{
	int		i;

	i = 0;
	while (environ[i])
		ft_printf("%s\n", environ[i++]);
}

static int		fetch_pairs(char **argv, t_env_datas *env_datas)
{
	char		*name;
	char		*value;
	size_t		len;
	size_t		pos;
	int			i;

	clear_environ(env_datas->environ);
	env_datas->environ = cpy_environ(NULL);
	i = 0;
	while (argv[i] && (pos = (size_t)ft_strchr(&argv[i][1], '=')))
	{
		len = pos - (size_t)&argv[i][0];
		name = ft_strnew(len);
		value = ft_strnew(ft_strlen(&argv[i][len + 1]));
		ft_strncpy(name, &argv[i][0], len);
		ft_strcpy(value, &argv[i][len + 1]);
		env_datas->environ = set_environ(env_datas->environ, name, value, 1);
		ft_strdel(&name);
		ft_strdel(&value);
		i++;
	}
	return (i);
}

static int		read_flags(char **argv, t_env_datas *env_datas)
{
	int		pairs;
	int		i;

	i = 0;
	pairs = 0;
	while (argv[i] && argv[i][0] == '-')
	{
		if (ft_strchr(argv[i], 'i'))
			pairs = fetch_pairs(&argv[i + 1], env_datas);
		if (ft_strchr(argv[i], 'v'))
			return (env_error(ENVERR_VERB));
		else if (ft_strchr(argv[i], 'P'))
			return (env_error(ENVERR_PATH));
		else if (ft_strchr(argv[i], 'S'))
			return (env_error(ENVERR_SPLIT));
		else if (ft_strchr(argv[i], 'u') && argv[i + 1])
			env_datas->environ = unset_environ(env_datas->environ, argv[++i]);
		i++;
	}
	i += pairs;
	if (argv[i])
		env_datas->utility = &argv[i];
	return (0);
}

void			env(char **argv, t_sh_datas *sh_datas)
{
	t_env_datas		env_datas;

	env_datas.environ = cpy_environ(sh_datas->environ);
	env_datas.utility = NULL;
	if (read_flags(&argv[1], &env_datas))
		return ;
	if (env_datas.utility)
		run_exec(env_datas.utility, sh_datas,
				(env_datas.environ) ? env_datas.environ : NULL);
	else
		print_environ((env_datas.environ)
						? env_datas.environ : sh_datas->environ);
	clear_environ(env_datas.environ);
}
