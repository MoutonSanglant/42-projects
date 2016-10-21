/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 20:33:18 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/21 13:45:06 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** side:
** 1 = left
** 2 = right
*/
/*
static void		find_nodes(t_node *graph, t_queue *connections)
{
	t_node	*a;
	t_node	*b;
	char	*name_a;
	char	*name_b;
	size_t	i;

	a = NULL;
	b = NULL;
	name_b = ft_strchr((char*)connections->content, '-');
	name_a = ft_strsub((char*)connections->content, 0, name_b - (char *)connections->content);
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
		connect_nodes(a, b);

}
*/

static t_node	*find_node(char *name, t_node *root)
{
	int		i;

	i = 0;
	while (i < root->links_count)
	{
		if (root->links[i] && ft_strequ(root->links[i]->name, name))
			return (root->links[i]);
		i++;
	}

	return (NULL);
}

void		create_node_links(t_node *root, t_node *node, t_queue *connections)
{
	t_key			*key;
	t_node			*to;
	t_connection	*connection;

	if (!node)
		return ;
	while (connections)
	{
		to = NULL;
		key = (t_key *)connections->content;
		//if (key->type & TYPE_CONNECTION && match(node->name, key->value))
		if (key->type & TYPE_CONNECTION)
		{
			connection = (t_connection *)key->value;
			if (ft_strequ(node->name, connection->from))
				to = find_node(connection->to, root);
			else if (ft_strequ(node->name, connection->to))
				to = find_node(connection->from, root);
			if (to)
				connect_nodes(node, to);
		}
			//find_nodes(graph, connections);
		connections = connections->next;
	}
}
