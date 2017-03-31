/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 23:20:52 by tdefresn          #+#    #+#             */
/*   Updated: 2017/03/22 14:41:42 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <libftprintf.h>

#include "philo.h"

static int	match_flags(char **arguments, t_data *data)
{
	int		ignored_arguments;

	ignored_arguments = 0;
	(void)arguments;
	ft_putendl("== arguments:");
	ft_printf("flags: %x\n", data->flags);
	if (data->flags & FLAG_COLOR)
		ft_putendl("colors");
	if (data->flags & FLAG_TEST)
		ft_putendl("test");
	/*
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
	*/
	return (ignored_arguments);
}

void		parse_arguments(int count, char **arguments, t_data *data)
{
	char		*arg;
	int			i;

	(void)data;
	i = 0;
	data->flags = FLAG_NONE;
	while (i < count)
	{
		arg = arguments[i];
		if (arg[0] == '-')
		{
			match_options(arg, &data->flags);
			if (i + 1 < count)
				i += match_flags(&arguments[i], data);
			else
				i += match_flags(NULL, data);
			data->flags = FLAG_NONE;
		}
		i++;
	}
}
