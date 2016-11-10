/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 00:49:32 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/10 01:07:18 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

void			create_node_links(t_node *root, t_node *node,
													t_queue *connections)
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
		connections = connections->next;
	}
}
