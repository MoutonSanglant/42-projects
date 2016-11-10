/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ways.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 15:31:51 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/10 15:41:42 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_node	**sort(t_node **way_list)
{
	t_node	*way;
	t_node	*ref;
	t_node	*min;
	int		idx;
	int		i;

	idx = -1;
	while ((ref = way_list[++idx]))
	{
		i = idx;
		min = ref;
		while ((way = way_list[i++]))
			if (way->weight < min->weight)
				min = way;
		if (min->weight < ref->weight)
			way_list[idx] = min;
		i = idx;
		while ((way = way_list[++i]))
			if (way == min)
				way_list[i] = ref;
	}
	return (way_list);
}

static int		count_valid_rooms(t_node *room)
{
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
	return (count);
}

static void		populate_way_list(t_node *room, t_node **way_list)
{
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
		way_list[count++] = dest;
	}
}

t_node			**new_ways_list(t_node *room)
{
	t_node	**way_list;
	int		count;

	count = count_valid_rooms(room);
	way_list = (t_node **)malloc(sizeof(t_node *) * (count + 1));
	way_list[count] = NULL;
	populate_way_list(room, way_list);
	return (sort(way_list));
}
