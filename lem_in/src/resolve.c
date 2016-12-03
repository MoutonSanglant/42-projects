/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 13:59:13 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/03 09:19:03 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_node	*find_best_path(t_node *room, t_graph *graph)
{
	t_node	**path_list;
	t_node	*path;
	int		total_weight;
	int		i;

	path = NULL;
	i = -1;
	path_list = new_ways_list(room);
	total_weight = 0;
	while (path_list[++i])
	{
		if (total_weight < graph->ants_count)
		{
			path = path_list[i];
			if (path->state & STATE_BUSY)
				path = NULL;
			else
				break ;
		}
		total_weight += path_list[i]->weight;
	}
	free(path_list);
	return (path);
}

static int		ant_move(t_ant *ant, t_graph *graph)
{
	t_node	*best_room;

	ant->room->state &= ~STATE_BUSY;
	best_room = find_best_path(ant->room, graph);
	if (best_room)
	{
		if (ant->room->state & STATE_START)
			graph->sleeping_ants--;
		ant->room = best_room;
	}
	ant->room->state |= STATE_BUSY;
	graph->start->state &= ~STATE_BUSY;
	return (best_room != NULL);
}

static int		resolve_turn(t_graph *graph, int count)
{
	t_ant	*ant;
	t_node	*room;
	int		update;

	update = 0;
	while (--count >= 0)
	{
		ant = graph->ants[count];
		if (ant && ant_move(ant, graph))
		{
			room = ant->room;
			if (update)
				write(1, " ", 1);
			ft_printf("\033[%smL%s-%s\033[0m", ant->color, ant->name, room->name, room->weight);
			update = 1;
			if (room->state & STATE_END)
			{
				room->state = STATE_END;
				ft_memdel((void *)&graph->ants[count]->name);
				ft_memdel((void *)&graph->ants[count]);
			}
		}
	}
	return (update);
}

static int		get_ant_color(t_graph *graph)
{
	static int	color = 31;

	if (!(graph->flags & FLAG_COLORS))
		return (0);

	if (color > 96)
		color = 31;
	if (color > 37 && color < 90)
		color = 90;
	return (color++);
}

void			resolve(t_graph *graph)
{
	t_ant	*ant;
	int		count;
	int		i;

	i = graph->ants_count;
	graph->sleeping_ants = graph->ants_count;
	graph->ants = (t_ant **)malloc(sizeof(t_ant *) * i);
	while (--i >= 0)
	{
		ant = (t_ant *)malloc(sizeof(t_ant));
		ant->name = ft_itoa(graph->ants_count - i);
		ant->color = ft_itoa(get_ant_color(graph));
		ant->room = graph->start;
		graph->ants[i] = ant;
	}
	count = 0;
	while (resolve_turn(graph, graph->ants_count))
	{
		ft_printf("\n");
		count++;
	}
	ft_memdel((void **)&graph->ants);
	clear_graph(graph);
	if (graph->flags & FLAG_TURNS)
		ft_printf("\033[31mresolve in %i turns\033[0m\n", count);
}
/*
** ft_printf("resolve in %i turns\n", count);
** if (graph->sleeping_ants > 0)
**   ft_printf("SOME ANTS ARE STILL SLEEPING (%i)\n", graph->sleeping_ants);
*/
