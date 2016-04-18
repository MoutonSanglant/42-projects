/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/04 18:23:37 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/10 14:36:55 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		print_error(char *path)
{
	struct stat		st_stat;
	char			*error_msg;
	int				stat_ret;

	error_msg = NULL;
	if ((stat_ret = lstat(path, &st_stat)) < 0)
		error_msg = ft_strdup("no such file or directory");
	else
	{
		if (!S_ISDIR(st_stat.st_mode))
			error_msg = ft_strdup("not a directory");
		else if (access(path, R_OK) < 0)
			error_msg = ft_strdup("permission denied");
	}
	ft_printf("cd: %s: %s\n", error_msg, path);
	ft_strdel(&error_msg);
}

static char		*get_home_path(t_sh_datas *sh_datas)
{
	char	**path_env;
	char	*home;
	int		i;

	i = 0;
	home = NULL;
	if ((path_env = get_environ(sh_datas->environ, "HOME=")))
		home = ft_strdup(path_env[0]);
	while (path_env[i])
		ft_strdel(&path_env[i++]);
	ft_memdel((void **)&path_env);
	return (home);
}

int				cd(char *path, t_sh_datas *sh_datas)
{
	char	*p;

	p = NULL;
	if (!path || path[0] == '~')
	{
		if (!(p = get_home_path(sh_datas)))
		{
			ft_printf("cd: HOME not set\n");
			return (1);
		}
	}
	if (p)
		path = p;
	if (chdir(path) < 0)
	{
		print_error(path);
		if (p)
			ft_strdel(&p);
		return (1);
	}
	if (p)
		ft_strdel(&p);
	set_prompt(sh_datas);
	return (0);
}
