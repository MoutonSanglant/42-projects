/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 06:33:28 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/11 21:59:00 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"



static int	node_exist(t_node *graph, char *name)
{
	t_node	*link;
	size_t	i;
	size_t	count;

	i = 0;
	count = graph->links_count;
	while (i < count)
	{
		link = graph->links[i];
		if (link && ft_strequ(link->name, name))
			return (1);
		i++;
	}
	return (0);
}

/*
** First, init all nodes connected to a root
** Then, connect nodes together
** Remove root node
** Return start node
** -----------------
** -> Preserve existing nodes
** x Rewrite existing nodes
** ========================
** TODO
** @optimization
** prevent multiple records of same room
*/
t_graph		*new_graph(t_input *input)
{
	t_graph		*graph;
	char		*name;
	char		*to;
	t_node		root;
	size_t		i;
	t_queue		*rooms;
	t_queue		*connections;

	rooms = input->rooms;
	connections = input->connections;

	graph = (t_graph *)ft_memalloc(sizeof(t_graph));
	graph->start = NULL;
	graph->end = NULL;

	root.links_count = ft_queuesize(rooms);
	root.links = (t_node **)ft_memalloc(sizeof(t_node*) * root.links_count);
	i = 0;
	while (i < root.links_count)
	{
		root.links[i] = NULL;
		i++;
	}

	i = 0;
	while (rooms)
	{
		to = ft_strchr((char*)rooms->content, ' ');
		name = ft_strsub((char*)rooms->content, 0, to - (char *)rooms->content);
		if (!node_exist(&root, name))
		{
			ft_printf("%s\n", (char *)rooms->content);
			root.links[i] = new_node(name, connections);
			if (ft_strequ((char *)rooms->content, (char *)input->start->content))
				graph->start = root.links[i];
			else if (ft_strequ((char *)rooms->content, (char *)input->end->content))
				graph->end = root.links[i];
		}
		ft_strdel(&name);
		rooms = rooms->next;
		i++;
	}
	i = 0;
	while (i < root.links_count)
	{
		if (root.links[i])
			parse_connections(&root, root.links[i]->name, connections);
		i++;
	}
	return (graph);
}
