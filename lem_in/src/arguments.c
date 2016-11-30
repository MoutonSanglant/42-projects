/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 23:20:52 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/29 23:42:27 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	parse_arguments(int count, char **arguments, t_graph *graph)
{
	char	*arg;

	while (--count)
	{
		arg = arguments[count];
		if (arg[0] != '-')
		{
			ft_eprintf("incorrect argument: %s\n", arg);
			continue ;
		}
		if (ft_strchr(arg, 'c'))
			graph->flags |= FLAG_COLORS;
		if (ft_strchr(arg, 't'))
			graph->flags |= FLAG_TURNS;
	}
}
