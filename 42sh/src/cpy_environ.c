/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_environ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/08 20:02:51 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/09 13:24:10 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		count_vars(char **environ)
{
	int		i;

	i = 0;
	if (environ)
	{
		while (environ[i++])
			;
	}
	return (i);
}

char			**cpy_environ(char **environ)
{
	char	**env_cpy;
	int		i;

	i = 0;
	env_cpy = ft_memalloc(sizeof(char *) * (count_vars(environ) + 1));
	if (environ)
	{
		while (environ[i])
		{
			env_cpy[i] = ft_strdup(environ[i]);
			i++;
		}
	}
	env_cpy[i] = NULL;
	return (env_cpy);
}
