/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/06 14:13:27 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/06 14:13:38 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_process(char *path, char **argv, char **environ)
{
	pid_t			fork_id;
	int				pid;

	fork_id = fork();
	if (fork_id == 0)
	{
		if (execve(path, argv, environ) < 0)
		{
			ft_printf("%s: exec format error: %s\n", PROGRAM_NAME, path);
			exit(1);
		}
	}
	else
		wait(&pid);
}
