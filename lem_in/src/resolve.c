/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 13:59:13 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/10 01:06:06 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		sort(t_node **path_list)
{
	t_node	*path;
	t_node	*ref;
	t_node	*min;
	int		i;
	int		idx;

	idx = 0;
	while ((ref = path_list[idx]))
	{
		i = idx;
		min = ref;
		while ((path = path_list[i]))
		{
			if (path->weight < min->weight)
				min = path;
			i++;
		}
		if (min->weight < ref->weight)
			path_list[idx] = min;
		i = idx + 1;
		while ((path = path_list[i]))
		{
			if (path == min)
				path_list[i] = ref;
			i++;
		}
		idx++;
	}
}

static t_node	**new_path_list(t_node *room)
{
	t_node	**path_list;
	t_node	*dest;
	int		count;
	int		i;

	i = -1;
	count = 0;
	while (++i < room->links_count)
	{
		dest = room->links[i];
		if (!dest || dest->state == STATE_INVALID || dest->state & STATE_START)
			continue ;
		count++;
	}
	path_list = (t_node **)malloc(sizeof(t_node *) * (count + 1));
	path_list[count] = NULL;
	i = -1;
	count = 0;
	while (++i < room->links_count)
	{
		dest = room->links[i];
		if (!dest || dest->state == STATE_INVALID || dest->state & STATE_START)
			continue ;
		path_list[count++] = dest;
	}
	sort(path_list);
	return (path_list);
}

static t_node	*find_best_path(t_node *room, t_graph *graph)
{
	t_node	**path_list;
	t_node	*path;
	int		total_weight;
	int		i;

	path = NULL;
	i = -1;
	path_list = new_path_list(room);
	total_weight = 0;
	while (path_list[++i])
	{
		if (graph->sleeping_ants >= total_weight)
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
	return (best_room != NULL);
}

static int		resolve_turn(t_graph *graph)
{
	t_ant	*ant;
	int		update;
	int		i;

	i = -1;
	update = 0;
	while (++i < graph->ants_count)
	{
		if ((ant = graph->ants[i]) && ant_move(ant, graph))
		{
			if (ant->room->state & STATE_END)
			{
				ant->room->state = STATE_END;
				graph->ants[i] = NULL;
			}
			if (update)
				ft_printf(" %s%s-%s", "L", ant->name, ant->room->name,
						ant->room->weight);
			else
			{
				ft_printf("%s%s-%s", "L", ant->name, ant->room->name,
						ant->room->weight);
				update = 1;
			}
		}
	}
	return (update);
}

void			resolve(t_graph *graph)
{
	t_ant	*ant;
	int		i;
	int		count;

	i = graph->ants_count;
	graph->sleeping_ants = graph->ants_count;
	graph->ants = (t_ant **)malloc(sizeof(t_ant *) * i);
	while (--i >= 0)
	{
		ant = (t_ant *)malloc(sizeof(t_ant));
		ant->name = ft_itoa(i + 1);
		ant->room = graph->start;
		graph->ants[i] = ant;
	}
	count = 0;
	while (resolve_turn(graph))
	{
		ft_printf("\n");
		count++;
	}
}
/*
** ft_printf("resolve in %i turns\n", count);
** if (graph->sleeping_ants > 0)
**   ft_printf("SOME ANTS ARE STILL SLEEPING (%i)\n", graph->sleeping_ants);
*/
