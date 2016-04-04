/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 02:12:22 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/04 19:32:38 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

#define PROGRAM_NAME "minishell"

char	**fetch_path()
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
			break;
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
			break;
		}
		out = NULL;
		ft_strdel(&full_path);
		i++;
	}
	if (!out && access(program_name, amode) >= 0)
		return (program_name);
	return (out);
}

int		parse_command(char *command, t_sh_datas *sh_datas)
{
	char	**argv;
	char	**env = { NULL };
	char	**path;
	char	*program_name;
	char	*full_path;
	pid_t	fork_id;
	int		a;

	path = fetch_path();
	while (*command == ' ')
		command++;
	if (*command == '\0')
		return (0);
	else if (ft_strnequ(command, "env", 3))
	{
		print_environ();
		return (0);
	}
	else if (ft_strnequ(command, "cd", 2))
	{
		cd(&command[3], sh_datas);
		return (0);
	}
	else if (ft_strnequ(command, "exit", 4))
	{
		//get exit value
		exit(0);
	}
	// Split the command
	argv = ft_strsplit(command, ' ');
	program_name = ft_strdup(argv[0]);
	//argv[0] = ft_strdup("");
	full_path = look_in_path(program_name, path);
	if (full_path)
	{
		fork_id = fork();
		if (fork_id == 0)
		{
			if (execve(full_path, argv, env))
				ft_printf("ERROR: Something went bad...\n");
		}
		else
			wait(&a);
	}
	else
	{
		ft_printf("%s: %s: command not found\n", PROGRAM_NAME, program_name);
		return (-1);
	}
	return (0);
}

void	get_user_command(t_sh_datas *sh_datas)
{
	char	*line;

	if (get_next_line(1, &line))
	{
		parse_command(line, sh_datas);
		ft_strdel(&line);
	}
}

int		main(void)
{
	t_sh_datas	sh_datas;

	set_prompt(&sh_datas);
	init_environ();
	while (1)
	{
		ft_putstr(sh_datas.prompt);
		get_user_command(&sh_datas);
	}
	return (0);
}
