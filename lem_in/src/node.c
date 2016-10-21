/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 06:34:20 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/21 13:45:25 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	match_link(char *node_name, t_connection *link)
{
	return (ft_strequ(node_name, link->from) || ft_strequ(node_name, link->to));
}

/*
** Count links in input
** allow duplicates
*/
static int		count_node_links(char *node_name, t_queue *link)
{
	t_key	*key;
	int		i;

	i = 0;
	while (link)
	{
		key = (t_key *)link->content;
		if (key->type & TYPE_CONNECTION && match_link(node_name, key->value))
			i++;
		link = link->next;
	}
	return (i);
}

static void	link_to(t_node *a, t_node *b)
{
	int		i;

	i = 0;
	while (i < a->links_count)
	{
		if (!a->links[i])
			break;
		i++;
	}
	a->links[i] = b;
}

/*
** Create bidirectionnal links
*/
void		connect_nodes(t_node *a, t_node *b)
{
	t_node	*link;
	int		i;

	if (a == b)
		return ;
	link = NULL;
	i = -1;
	while (++i < a->links_count)
	{
		link = a->links[i];
		if (!link)
			continue;
		else if (ft_strequ(b->name, link->name))
			return;
	}
	link_to(a, b);
	link_to(b, a);
}

t_node		*new_node(t_room *room, t_queue *links)
{
	t_node	*node;
	size_t	count;

	count = count_node_links(room->name, links);
	if (count < 1)
		return (NULL);
	node = (t_node *)ft_memalloc(sizeof(t_node));
	ft_bzero(node, sizeof(t_node));
	node->links = (t_node **)ft_memalloc(sizeof(t_node *) * count);
	node->name = room->name;
	node->links_count = count;
	node->x = room->x;
	node->y = room->y;

	return (node);
}
