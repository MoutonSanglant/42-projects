/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 14:13:27 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/09 21:11:43 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
static char		*look_in_path(char *program_name, char **path, int amode)
{
	char	*full_path;
	char	*tmp;
	int		i;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		full_path = ft_strjoin(tmp, program_name);
		ft_strdel(&tmp);
		if (access(full_path, amode) >= 0)
			return (full_path);
		ft_strdel(&full_path);
		i++;
	}
	return (NULL);
}


static void		run_process(char *path, char **argv, char **environ)
{
	pid_t			fork_id;
	int				pid;

	fork_id = fork();
	if (fork_id == 0)
	{
		if (execve(path, argv, environ) < 0)
		{
			ft_printf("%s: exec format error: %s\n", PROGRAM_NAME, path);
			ft_strdel(&path);
			exit(1);
		}
	}
	else
		wait(&pid);
	//ft_strdel(&path);
}

static void		clear(char **split)
{
	int		i;

	i = 0;
	while (split[i])
		ft_strdel(&split[i++]);
	ft_memdel((void **)&split);
}

int				run_exec(char **argv, t_sh_datas *sh_datas, char **exec_environ)
{
	char	**path;
	char	*program_name;
	char	*full_path;

	path = get_environ(sh_datas->environ, "PATH=");
	program_name = ft_strdup(argv[0]);
	full_path = (path) ? look_in_path(program_name, path, F_OK | X_OK) : NULL;
	clear(path);
	if (!full_path && access(program_name, F_OK | X_OK) < 0)
	{
		ft_printf("%s: %s: command not found\n", PROGRAM_NAME, program_name);
		ft_strdel(&program_name);
		return (-1);
	}
	if (exec_environ)
		run_process((full_path) ? full_path : program_name, argv, exec_environ);
	else
		run_process((full_path) ? full_path : program_name, argv, sh_datas->environ);
	if (full_path)
		ft_strdel(&full_path);
	ft_strdel(&program_name);
	return (0);
}
