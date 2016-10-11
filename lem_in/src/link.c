/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 20:33:18 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/11 10:05:13 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** side:
** 1 = left
** 2 = right
*/
static void		find_nodes(t_node *graph, t_queue *connection, int side)
{
	t_node	*a;
	t_node	*b;
	char	*name_a;
	char	*name_b;
	size_t	i;

	(void) side;
	a = NULL;
	b = NULL;
	name_b = ft_strchr((char*)connection->content, '-');
	name_a = ft_strsub((char*)connection->content, 0, name_b - (char *)connection->content);
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

	//ft_printf("connect node '%s' with '%s'\n", name_a, name_b);
	if (a && b)
	{
		connect_nodes(a, b);
	}

}

static int	match(char *name, t_queue *connection)
{
	char	*node_a_name;
	char	*node_b_name;

	node_b_name = ft_strchr((char*)connection->content, '-');
	node_a_name = ft_strsub((char*)connection->content, 0, node_b_name - (char *)connection->content);
	node_b_name++;
	if (ft_strequ(name, node_a_name))
	{
		ft_strdel(&node_a_name);
		return (1);
	}
	else if  (ft_strequ(name, node_b_name))
	{
		ft_strdel(&node_a_name);
		return (2);
	}
	ft_strdel(&node_a_name);
	return (0);
}

void		parse_connections(t_node *graph, char *name, t_queue *connections)
{
	int side;

	side = 0;
	while (connections)
	{
		if ((side = match(name, connections)))
		{
			find_nodes(graph, connections, side);
		}
		connections = connections->next;
	}
}
