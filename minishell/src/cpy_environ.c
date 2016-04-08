/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_environ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/08 20:02:51 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/08 20:44:14 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**cpy_environ(char **environ)
{
	char			**env_cpy;
	int				i;

	i = 0;
	if (environ)
	{
		while (environ[i])
			i++;
		env_cpy = ft_memalloc(sizeof(char *) * (i + 1));
		i = 0;
		while (environ[i])
		{
			env_cpy[i] = ft_strdup(environ[i]);
			i++;
		}
	}
	else
		env_cpy = ft_memalloc(sizeof(char *));
	env_cpy[i] = NULL;
	env_cpy = set_environ(env_cpy, "SHLVL", "1", 0);
	env_cpy = set_environ(env_cpy, "PWD", "", 0);
	env_cpy = set_environ(env_cpy, "PATH",
					"/usr/gnu/bin:/usr/local/bin:/usr/bin:/bin:.", 0);
	return (env_cpy);
}
