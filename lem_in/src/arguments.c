/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 23:20:52 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/03 09:30:07 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	parse_long(char *arg, t_graph *graph)
{
	if (ft_strequ(&arg[2], "color"))
		graph->flags |= FLAG_COLORS;
	else if (ft_strequ(&arg[2], "turns"))
		graph->flags |= FLAG_TURNS;
}

static void	parse_short(char *arg, t_graph *graph)
{
	if (ft_strchr(arg, 'c'))
		graph->flags |= FLAG_COLORS;
	if (ft_strchr(arg, 't'))
		graph->flags |= FLAG_TURNS;
}

void		parse_arguments(int count, char **arguments, t_graph *graph)
{
	char	*arg;

	while (--count)
	{
		arg = arguments[count];
		if (arg[0] != '-')
			ft_eprintf("incorrect argument: %s\n", arg);
		else if (arg[1] == '-')
			parse_long(arg, graph);
		else
			parse_short(arg, graph);
	}
}
