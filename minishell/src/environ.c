/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/04 19:25:43 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/05 21:24:38 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		**add_environ(char **environ, const char *name,
								const char *value, int old_size)
{
	char	**env_cpy;
	char	*str;

	env_cpy = ft_memalloc(sizeof(char *) * (old_size + 2));
	env_cpy = ft_memcpy(env_cpy, environ, sizeof(char *) * old_size);
	ft_memdel((void **)&environ);
	str = ft_strnew(ft_strlen(name) + ft_strlen(value) + 1);
	ft_strcpy(str, name);
	str[ft_strlen(name)] = '=';
	ft_strcpy(&str[ft_strlen(name) + 1], value);
	env_cpy[old_size] = str;
	env_cpy[old_size + 1] = NULL;
	return (env_cpy);
}

static char		**remove_environ(char **environ, int idx)
{
	char	**env_cpy;
	int		i;

	i = 0;
	while (environ[i])
		i++;
	env_cpy = ft_memalloc(sizeof(char *) * i);
	env_cpy = ft_memcpy(env_cpy, environ, sizeof(char *) * i);
	ft_memdel((void **)&environ);
	ft_strdel(&env_cpy[idx]);
	i--;
	while (idx < i)
	{
		env_cpy[idx] = env_cpy[idx + 1];
		idx++;
	}
	env_cpy[i] = NULL;
	return (env_cpy);
}

char			**init_environ(void)
{
	extern char		**environ;
	char			**env_cpy;
	int				i;

	i = 0;
	while (environ[i])
		i++;
	env_cpy = ft_memalloc(sizeof(char *) * (i + 1));
	i = 0;
	while (environ[i])
	{
		env_cpy[i] = ft_strdup(environ[i]);
		i++;
	}
	env_cpy[i] = NULL;
	env_cpy = set_environ(env_cpy, "SHLVL", "1", 0);
	env_cpy = set_environ(env_cpy, "PWD", "", 0);
	env_cpy = set_environ(env_cpy, "PATH",
					"/usr/gnu/bin:/usr/local/bin:/usr/bin:/bin:.", 0);
	return (env_cpy);
}

char			**set_environ(char **environ, const char *name,
						const char *value, int override)
{
	char			*str;
	size_t			len;
	int				i;

	i = 0;
	len = ft_strlen(name);
	while (environ[i])
	{
		if (!ft_strncmp(environ[i], name, len))
		{
			if (override)
			{
				ft_strdel(&environ[i]);
				str = ft_strnew(len + ft_strlen(value) + 1);
				ft_strcpy(str, name);
				str[len] = '=';
				ft_strcpy(&str[len + 1], value);
				environ[i] = str;
			}
			return (environ);
		}
		i++;
	}
	return (add_environ(environ, name, value, i));
}

char			**unset_environ(char **environ, const char *name)
{
	size_t			len;
	int				i;

	i = 0;
	while (environ[i])
	{
		len = ft_strchr(environ[i], '=') - environ[i];
		if (ft_strlen(name) == len && !ft_strncmp(environ[i], name, len))
			return (remove_environ(environ, i));
		i++;
	}
	return (environ);
}
