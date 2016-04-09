/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_default_environ.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/09 13:23:00 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/09 20:05:21 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		**set_default_vars(char **env_cpy)
{
	char	*depth_str;
	char	*str;
	int		depth;
	int		i;

	env_cpy = set_environ(env_cpy, "SHLVL", "0", 0);
	env_cpy = set_environ(env_cpy, "PWD", "", 0);
	env_cpy = set_environ(env_cpy, "PATH",
							"/usr/gnu/bin:/usr/local/bin:/usr/bin:/bin:.", 0);
	i = 0;
	while (env_cpy[i])
	{
		if (!ft_strncmp(env_cpy[i], "SHLVL=", 6))
		{
			depth = ft_atoi(&env_cpy[i][6]);
			depth++;
			depth_str = ft_itoa(depth);
			ft_strdel(&env_cpy[i]);
			str = ft_strnew(ft_strlen(depth_str) + 6);
			ft_strcpy(str, "SHLVL=");
			ft_strcpy(&str[6], depth_str);
			env_cpy[i] = str;
			ft_strdel(&depth_str);
		}
		i++;
	}
	return (env_cpy);
}


char	**create_default_environ(char **environ)
{
	char	**env_cpy;

	env_cpy = cpy_environ(environ);
	env_cpy = set_default_vars(env_cpy);
	return (env_cpy);
}
