/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 13:59:13 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/21 15:44:21 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	ant_move(t_ant *ant)
{
	t_node	*best_room;
	t_node	*dest;
	t_node	*room;
	int		i;

	i = -1;
	best_room = NULL;
	room = ant->room;
	room->state &= ~STATE_BUSY;
	while (++i < room->links_count)
	{
		dest = room->links[i];
		if (dest->state & STATE_BUSY)
			continue;
		else if (!best_room)
			best_room = dest;
		else if (dest->weight < best_room->weight)
			best_room = dest;
	}
	if (best_room)
		ant->room = best_room;
	ant->room->state |= STATE_BUSY;
	return (best_room != NULL);
}


static int	resolve_turn(t_graph *graph)
{
	t_ant	*ant;
	int		update;
	int		i;

	i = 0;
	update = 0;
	while (i < graph->ants_count)
	{
		ant = graph->ants[i];
		if (ant && ant_move(ant))
		{
			if (ant->room->state & STATE_END)
			{
				ant->room->state = STATE_END;
				graph->ants[i] = NULL;
			}
			if (update)
				ft_printf(" %s%s-%s", "L", ant->name, ant->room->name);
			else
			{
				ft_printf("%s%s-%s", "L", ant->name, ant->room->name);
				update = 1;
			}
		}
		i++;
	}
	return (update);
}

void	resolve(t_graph *graph)
{
	t_ant	*ant;
	int		i;

	i = graph->ants_count;
	graph->ants = (t_ant **)malloc(sizeof(t_ant *) * i);
	while (--i >= 0)
	{
		ant = (t_ant *)malloc(sizeof(t_ant) * i);
		ant->name = ft_itoa(i + 1);
		ant->room = graph->start;
		graph->ants[i] = ant;
	}
	while (resolve_turn(graph))
		ft_printf("\n");
}
