/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_traversal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/11 10:55:39 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/11 13:16:19 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	compute_pathes(t_node *root, size_t length)
{
	t_node *link;
	size_t	i;

	root->path_length = length;
	ft_printf("%s: %i\n", root->name, length);

	i = 0;
	while (i < root->links_count)
	{
		// If inside recursive ?
		// mark neighbourg first, then enter !!
		link = root->links[i];
		if (link && link->path_length == 0 && !(link->end || link->start))
			compute_pathes(link, length + 1);
		i++;
	}
}

void	graph_traversal(t_node *root, t_node *parent, int depth)
{
	t_node *link;
	size_t	i;

	if (depth < 0)
		return;
	ft_printf("node: %s, depth: %i\n", root->name, depth);

	i = 0;
	while (i < root->links_count)
	{
		link = root->links[i];
		if (link && link != parent)
			graph_traversal(link, root, depth - 1);
		i++;
	}
}
