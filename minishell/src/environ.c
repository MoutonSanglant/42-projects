/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/04 19:25:43 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/04 19:28:53 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_environ()
{
	extern char		**environ;

	if (environ[0])
		return ;
	environ[0] = ft_strdup("SHLVL=1");
	environ[1] = ft_strdup("PWD=");
	environ[2] = ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/usr/bin:/bin:.");
	environ[3] = NULL;
}

void	print_environ()
{
	extern char		**environ;
	int				i;

	i = 0;
	while (environ[i])
		ft_printf("%s\n", environ[i++]);
}
