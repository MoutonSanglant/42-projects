/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 06:33:28 by tdefresn          #+#    #+#             */
/*   Updated: 2016/09/19 16:33:56 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		connect_nodes(t_node *a, t_node *b)
{
	// There can be doubles in the output,
	// prevent multiple connections
	ft_printf(">> connect node '%s' with '%s'\n", a->name, b->name);
}


static void		find_nodes(t_node *graph, t_queue *link)
{
	t_node	*a;
	t_node	*b;
	char	*name_a;
	char	*name_b;
	size_t	i;

	a = NULL;
	b = NULL;
	name_b = ft_strchr((char*)link->content, '-');
	name_a = ft_strsub((char*)link->content, 0, name_b - (char *)link->content);
	name_b++;

	if (ft_strequ(name_a, name_b))
		return ;

	i = 0;
	while (i < graph->links_count)
	{
		if (graph->links[i])
		{
			if (ft_strequ(graph->links[i]->name, name_a))
				a = graph->links[i];
			else if (ft_strequ(graph->links[i]->name, name_b))
				b = graph->links[i];
		}
		i++;
	}

	ft_printf("connect node '%s' with '%s'\n", name_a, name_b);
	if (a && b)
		connect_nodes(a, b);

}

static int	is_matching_link(t_node *node, t_queue *link)
{
	char	*link_name;
	char	*to;
	int		match;

	match = 0;
	//ft_printf("test: '%s' with '%s'\n", node->name, (char *)link->content);
	to = ft_strchr((char*)link->content, '-');
	// leak (strsub)
	link_name = ft_strsub((char*)link->content, 0, to - (char *)link->content);
	if (ft_strequ(node->name, link_name))
		match = 1;
	ft_strdel(&link_name);
	return (match);
}

//static void		find_matching_links(t_node **nodes, size_t count, t_node *node, t_queue *links)
static void		find_matching_links(t_node *graph, t_node *node, t_queue *link)
{
	while (link)
	{
		if (is_matching_link(node, link))
			find_nodes(graph, link);
		link = link->next;
	}
}

static int	node_exist(t_node *graph, char *name)
{
	size_t		i;

	i = 0;
	//ft_printf("check if node exist\n");
	while (i < graph->links_count)
	{
		if (graph->links[i] && ft_strequ(graph->links[i]->name, name))
			return (1);
		i++;
	}
	//ft_printf("doesn't'\n");

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
*/
t_graph		*new_graph(t_input *input, t_queue *rooms, t_queue *links)
{
	t_graph		*graph;
	//t_node		*node;
	char		*name;
	char		*to;
	t_node		root;
	size_t		i;

	graph = (t_graph *)ft_memalloc(sizeof(t_graph));
	graph->start = NULL;
	graph->end = NULL;
	//output(input.rooms, "room");
	//output(input.connections, "connection");

	// TODO
	// @optimization
	// prevent multiple records of same room
	root.links_count = ft_queuesize(rooms);
	root.links = (t_node **)ft_memalloc(sizeof(t_node*) * root.links_count);
	i = 0;
	while (i < root.links_count)
	{
		root.links[i] = NULL;
		i++;
	}

	//node = NULL;

	i = 0;
	while (rooms)
	{
		to = ft_strchr((char*)rooms->content, ' ');
		name = ft_strsub((char*)rooms->content, 0, to - (char *)rooms->content);
		if (!node_exist(&root, name))
		{
			root.links[i] = new_node(name, links);
			if (ft_strequ((char *)rooms->content, (char *)input->start->content))
				graph->start = root.links[i];
			else if (ft_strequ((char *)rooms->content, (char *)input->end->content))
				graph->end = root.links[i];
		}
		ft_strdel(&name);
		rooms = rooms->next;
		// Don't pop the queue, we need to output it later !!
		//ft_queuepop(&rooms);
		i++;
	}
	i = 0;
	while (i < root.links_count)
	{
		if (!root.links[i])
		{
			i++;
			continue ;
		}
		ft_printf("# of links: %u\n", ft_queuesize(links));
		ft_printf("node %u: %s\n", i, root.links[i]->name);
		find_matching_links(&root, root.links[i], links);
		i++;
	}

	// TODO @placeholder
	// this is just to prevent graph from being empty
	//graph->start = root.links[0];
	//graph->end = root.links[0];

	return (graph);
}






/*
t_queue *start;
t_queue	*current;
t_queue *previous;
t_queue *next;

start = links;
next = links;
previous = links;
current = next;
while (current)
{
	next = current->next;
	if (is_matching_link(node, current))
	{
		if (current == start)
			start = next;
		previous->next = next;
		if (previous == current)
			previous = next;
		find_nodes(nodes, current);
		ft_queuepop(&current);
	}
	else
		previous = current;
	current = next;
}
return (start);
*/
