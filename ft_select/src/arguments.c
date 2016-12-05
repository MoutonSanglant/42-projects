/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 23:20:52 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/05 20:49:52 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int	parse_long(char *arg, t_select *select)
{
	if (ft_strequ(&arg[2], "inline"))
	{
		select->flags |= FLAG_INLINE;
		return (1);
	}
	else if (ft_strequ(&arg[2], "column"))
	{
		select->flags |= FLAG_COLUMNS;
		return (1);
	}
	return (0);
}

static int	parse_short(char *arg, t_select *select)
{
	int		c;

	c = 0;
	if (ft_strchr(arg, 'i'))
	{
		select->flags |= FLAG_INLINE;
		c++;
	}
	if (ft_strchr(arg, 'c'))
	{
		select->flags |= FLAG_COLUMNS;
		c++;
	}
	return (c);
}

int			parse_arguments(int count, char **arguments, t_select *select)
{
	char	*arg;
	int		c;
	int		i;

	i = 1;
	c = 1;
	while (i < count)
	{
		arg = arguments[i];
		if (arg[0] != '-')
			break ;
		else if (arg[1] == '-')
			c += parse_long(arg, select);
		else
			c += parse_short(arg, select);
		i++;
	}
	return (c);
}
