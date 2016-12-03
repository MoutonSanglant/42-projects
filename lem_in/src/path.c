/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 13:03:53 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/03 21:18:27 by tdefresn         ###   ########.fr       */
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

static void	mark_invalid(t_node *node)
{
	int		i;
	int		count;
	t_state	state;
	t_node	**links;

	state = node->state;
	count = node->links_count;
	if (!state || state & (STATE_START | STATE_END) || count > 2)
		return ;
	// ICI CE PRODUIT LE BUG:
	// ANTONIN FAIT TOUT PLANTER,
	// start est marque comme invalide ?!
	ft_printf("invalid: %s, %i\n", node->name, node->weight);
	links = node->links;
	node->state = STATE_INVALID;
	i = -1;
	while (++i < node->links_count)
		mark_invalid(links[i]);
}

t_node		*compare_paths(t_node *link, t_node *best_path, int *best_depth,
																	int depth)
{
	if (best_path)
		mark_invalid(best_path);
	*best_depth = depth;
	return (link);
}

int			mark_all_path(t_node *root, int w, t_graph *graph, int links)
{
	t_node	*link;
	t_node	*best_path;
	int		best_depth;
	int		depth;

	depth = w;
	best_path = NULL;
	best_depth = INT_MAX;
	mark_neighbourgs(root, w + 1);
	while (links)
	{
		link = root->links[root->links_count - links--];
		if (link->weight < w)
			continue ;
		if (link == graph->start)
			return (w + 1);
		depth = mark_all_path(link, w + 1, graph, link->links_count);
		if (root == graph->end)
			continue ;
		if (depth < best_depth)
			best_path = compare_paths(link, best_path, &best_depth, depth);
		else
			mark_invalid(link);
	}
	return (depth);
}
