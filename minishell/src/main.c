/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 02:12:22 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/05 21:24:12 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

#define PROGRAM_NAME "minishell"

char	**fetch_path(void)
{
	extern char		**environ;
	char			**out;
	char			*tmp;
	int				i;

	i = 0;
	out = NULL;
	while (environ[i])
	{
		tmp = ft_strnstr(environ[i++], "PATH", 4);
		if (tmp)
		{
			out = ft_strsplit(ft_strdup(&tmp[5]), ':');
			break ;
		}
	}
	return (out);
}

char	*look_in_path(char *program_name, char **path)
{
	char	*out;
	char	*full_path;
	int		amode;
	int		i;

	i = 0;
	amode = F_OK | X_OK;
	if (!path)
	{
		if (access(program_name, amode) >= 0)
			return (program_name);
		return (NULL);
	}
	while (path[i])
	{
		out = ft_strjoin(path[i], "/");
		full_path = ft_strjoin(out, program_name);
		ft_strdel(&out);
		if (access(full_path, amode) >= 0)
		{
			out = full_path;
			break ;
		}
		out = NULL;
		ft_strdel(&full_path);
		i++;
	}
	if (!out && access(program_name, amode) >= 0)
		return (program_name);
	return (out);
}

void	run_process(char *path, char **argv, char **environ)
{
	pid_t			fork_id;
	int				pid;

	fork_id = fork();
	if (fork_id == 0)
	{
		if (execve(path, argv, environ))
			ft_printf("ERROR: Something went bad...\n");
	}
	else
		wait(&pid);
}

int		parse_command(char **argv, t_sh_datas *sh_datas)
{
	char	**path;
	char	*program_name;
	char	*full_path;
	int		ret_val;

	if ((ret_val = check_builtins(argv, sh_datas)) >= 0)
		return (ret_val);
	program_name = ft_strdup(argv[0]);
	path = fetch_path();
	full_path = look_in_path(program_name, path);
	if (!full_path)
	{
		ft_printf("%s: %s: command not found\n", PROGRAM_NAME, program_name);
		return (-1);
	}
	run_process(full_path, argv, sh_datas->environ);
	return (0);
}

int		main(void)
{
	char		**argv;
	char		*line;
	t_sh_datas	sh_datas;
	int			i;

	sh_datas.environ = init_environ();
	set_prompt(&sh_datas);
	while (1)
	{
		ft_putstr(sh_datas.prompt);
		if (get_next_line(1, &line))
		{
			argv = ft_strsplit(line, ' ');
			parse_command(argv, &sh_datas);
			i = 0;
			while (argv[i])
				ft_strdel(&argv[i++]);
			ft_memdel((void **)&argv);
			ft_strdel(&line);
		}
	}
	return (0);
}
