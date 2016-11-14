/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 02:12:22 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/12 16:16:05 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "get_next_line.h"

static int		read_input(char **argv, t_sh_datas *sh_datas)
{
	int		ret_val;
	int		i;

	ret_val = 0;
	if ((ret_val = check_builtins(argv, sh_datas)) >= 0)
		;
	else
		ret_val = run_exec(argv, sh_datas, NULL);
	if (argv)
	{
		i = 0;
		while (argv[i])
			ft_strdel(&argv[i++]);
		ft_memdel((void **)&argv);
	}
	return (ret_val);
}

int				main(void)
{
	extern char		**environ;
	char			**argv;
	char			*line;
	t_sh_datas		sh_datas;
	int				gnl_ret;
	struct termios	term;

	termcaps_init(&term);
	sh_datas.prompt = NULL;
	sh_datas.environ = create_default_environ(environ);
	set_prompt(&sh_datas);
	while (1)
	{
		ft_putstr(sh_datas.prompt);
		gnl_ret = get_next_line(1, &line);
		if (gnl_ret > 0)
		{
			argv = parse_input(line);
			ft_strdel(&line);
			read_input(argv, &sh_datas);
		}
		else if (gnl_ret == 0)
			sh_exit(NULL, &sh_datas);
	}
	return (0);
}
