/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 06:33:28 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/10 17:58:38 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		node_exist(t_node *graph, t_room *room)
{
	t_node	*link;
	size_t	count;
	size_t	i;

	i = 0;
	count = graph->links_count;
	while (i < count)
	{
		link = graph->links[i];
		if (link && ft_strequ(link->name, room->name))
			return (1);
		i++;
	}
	return (0);
}

static t_node	*insert_node(t_graph *graph, t_node *link, t_key *key,
															t_lemin_parser *parser)
{
	link = new_node(((t_room *)key->value), parser->connections);
	if (key->type & TYPE_START)
		graph->start = link;
	else if (key->type & TYPE_END)
		graph->end = link;
	return (link);
}

static void		build_graph(t_graph *g, t_node *root, t_lemin_parser *parser)
{
	t_queue	*queue;
	t_key	*key;
	int		idx;

	idx = 0;
	queue = parser->queue;
	key = (t_key *)queue->content;
	while (!(key->type & TYPE_CONNECTION))
	{
		if (!(key->type & TYPE_ROOM))
		{
			queue = queue->next;
			key = (t_key *)queue->content;
			continue ;
		}
		if (!node_exist(root, (t_room *)key->value))
			root->links[idx] = insert_node(g, root->links[idx], key, parser);
		queue = queue->next;
		if (!queue)
			break ;
		key = (t_key *)queue->content;
		idx++;
	}
}

void			clear_graph(t_graph *graph)
{
	t_node	*link;
	int		i;

	i = graph->root_links_count;
	while (--i >= 0)
	{
		if ((link = graph->root_links[i]))
		{
			if (link->name)
				ft_memdel((void *)&link->name);
			if (link->links)
				ft_memdel((void *)&link->links);
			ft_memdel((void *)&link);
		}
	}
	ft_memdel((void **)&graph->root_links);
}

/*
** Create all nodes, connected to a root node
** Then, connect nodes together
** -----------------
** -> Preserve existing nodes
** x Rewrite existing nodes
** ========================
*/

void			new_graph(t_graph *graph, t_lemin_parser *parser)
{
	t_node	root;
	int		i;

	root.links_count = parser->rooms_count;
	root.links = (t_node **)ft_memalloc(sizeof(t_node *) * root.links_count);
	ft_bzero(root.links, sizeof(t_node *) * root.links_count);
	build_graph(graph, &root, parser);
	i = -1;
	while (++i < root.links_count)
		create_node_links(&root, root.links[i], parser->connections);
	graph->root_links = root.links;
	graph->root_links_count = root.links_count;
	if (!graph->start || !graph->end)
		error(ERR_HIDDEN_ROOM);
}
