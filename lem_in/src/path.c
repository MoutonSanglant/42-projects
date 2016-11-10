/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 13:03:53 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/10 00:56:55 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	mark_neighbourgs(t_node *node, int w)
{
	t_node	*link;
	int		count;
	int		i;

	i = -1;
	count = 0;
	while (++i < node->links_count)
	{
		link = node->links[i];
		if (!link->state || link->weight > w)
		{
			link->state = STATE_VALID;
			link->weight = w;
			count++;
		}
	}
	return (count);
}

static void	mark_invalid(t_node *node, t_graph *graph)
{
	int		i;

	if (!node->state || node->links_count > 2 || node == graph->end
			|| node == graph->start)
		return ;
	node->state = STATE_INVALID;
	i = -1;
	while (++i < node->links_count)
		mark_invalid(node->links[i], graph);
}

int			mark_all_path(t_node *root, int w, t_graph *graph)
{
	t_node	*link;
	t_node	*shortest_path;
	int		smallest_depth;
	int		depth;
	int		i;

	if (root == graph->start)
		return (w);
	mark_neighbourgs(root, w + 1);
	i = -1;
	depth = w;
	smallest_depth = INT_MAX;
	shortest_path = NULL;
	while (++i < root->links_count)
	{
		link = root->links[i];
		if (link->weight >= w)
		{
			depth = mark_all_path(link, w + 1, graph);
			if (root != graph->end)
			{
				if (depth < smallest_depth)
				{
					if (shortest_path)
						mark_invalid(shortest_path, graph);
					smallest_depth = depth;
					shortest_path = link;
				}
				else
					mark_invalid(link, graph);
			}
		}
	}
	return (depth);
}
