/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 02:12:22 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/08 20:01:09 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "get_next_line.h"

int		parse_command(char **argv, t_sh_datas *sh_datas)
{
	int		ret_val;

	if ((ret_val = check_builtins(argv, sh_datas)) >= 0)
		return (ret_val);
	else
		return (run_exec(argv, sh_datas, NULL));
	return (0);
}

int		main(void)
{
	extern char		**environ;
	char			**argv;
	char			*line;
	t_sh_datas		sh_datas;
	int				i;

	sh_datas.environ = cpy_environ(environ);
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
