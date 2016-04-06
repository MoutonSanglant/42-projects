/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 02:12:22 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/06 14:13:24 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

char	**fetch_environ(char **environ, const char *name, const int len)
{
	int				i;

	i = 0;
	while (environ[i])
	{
		if (!ft_strncmp(environ[i], name, len))
			return (ft_strsplit(ft_strdup(&environ[i][len]), ':'));
		i++;
	}
	return (NULL);
}

char	*look_in_path(char *program_name, char **path, int amode)
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

int		parse_command(char **argv, t_sh_datas *sh_datas)
{
	char	**path;
	char	*program_name;
	char	*full_path;
	int		ret_val;

	if ((ret_val = check_builtins(argv, sh_datas)) >= 0)
		return (ret_val);
	program_name = ft_strdup(argv[0]);
	path = fetch_environ(sh_datas->environ, "PATH=", 5);
	full_path = (path) ? look_in_path(program_name, path, F_OK | X_OK) : NULL;
	if (!full_path && access(program_name, F_OK | X_OK) < 0)
	{
		ft_printf("%s: %s: command not found\n", PROGRAM_NAME, program_name);
		return (-1);
	}
	run_process((full_path) ? full_path : program_name, argv, sh_datas->environ);
	ft_strdel(&full_path);
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
