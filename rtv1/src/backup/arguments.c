/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 23:20:52 by tdefresn          #+#    #+#             */
/*   Updated: 2017/03/18 14:52:49 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	match_flags(char **arguments, t_rt *rt)
{
	int		ignored_arguments;

	ignored_arguments = 0;
	if (rt->flags & FLAG_WIDTH)
	{
		if (arguments == NULL || !ft_isdigit(arguments[1][0]))
			error(ERRNO_USAGE, NULL); // ERR_WIDTH: "width must be a value between ... and ..."
		rt->width = ft_atoi(arguments[1]);
		ignored_arguments = 1;
	}
	else if (rt->flags & FLAG_HEIGHT)
	{
		if (arguments == NULL || !ft_isdigit(arguments[1][0]))
			error(ERRNO_USAGE, NULL); // ERR_WIDTH: "width must be a value between ... and ..."
		rt->height = ft_atoi(arguments[1]);
		ignored_arguments = 1;
	}
	return (ignored_arguments);
}

void		parse_arguments(int count, char **arguments, t_rt *rt)
{
	char		*arg;
	int			i;

	i = 0;
	rt->flags = FLAG_NONE;
	while (i < count)
	{
		arg = arguments[i];
		if (arg[0] == '-')
		{
			match_options(arg, &rt->flags);
			if (i + 1 < count)
				i += match_flags(&arguments[i], rt);
			else
				i += match_flags(NULL, rt);
			rt->flags = FLAG_NONE;
		}
		i++;
	}
}
