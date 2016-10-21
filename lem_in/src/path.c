/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 13:03:53 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/21 15:40:52 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	mark_all_path(t_graph *graph, t_node *root, int w)
{
	t_node	*link;
	int		i;

	i = -1;
	while (++i < root->links_count)
	{
		link = root->links[i];
		if (link && (link->weight == 0 || link->weight > w + 1))
			link->weight = w + 1;
	}
	i = -1;
	while (++i < root->links_count)
	{
		link = root->links[i];
		if (link && link->weight >= w)
			mark_all_path(graph, link, w + 1);
	}
}
