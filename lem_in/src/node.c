/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 06:34:20 by tdefresn          #+#    #+#             */
/*   Updated: 2016/09/19 21:02:46 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	match_link(char *node_name, t_queue *link)
{
	char	*name_a;
	char	*name_b;
	int		match;

	match = 0;
	name_b = ft_strchr((char*)link->content, '-');
	name_a = ft_strsub((char*)link->content, 0, name_b - (char *)link->content);
	name_b++;
	if (ft_strequ(node_name, name_a) || ft_strequ(node_name, name_b))
		match = 1;
	ft_strdel(&name_a);
	return (match);
}

/*
** Doubles in output will result
** in existing but empty links
** I will do with it anyway
*/
static int		count_node_links(char *node_name, t_queue *link)
{
	int		i;

	i = 0;
	while (link)
	{
		if (match_link(node_name, link))
			i++;
		link = link->next;
	}
	return (i);
}

void		connect_nodes(t_node *a, t_node *b)
{
	// There can be doubles in the output,
	// prevent multiple connections
	ft_printf("%s-%s\n", a->name, b->name);
	ft_sprintf(">> connect node '%s' with '%s'\n", a->name, b->name);
}

t_node		*new_node(char *name, t_queue *links)
{
	t_node	*node;
	size_t	count;

	/*
	**  /!\ TODO /!\
	** Break on duplicate links
	*/
	count = count_node_links(name, links);
	if (count < 1)
		return NULL;
	node = (t_node *)ft_memalloc(sizeof(t_node));
	node->links = (t_node **)ft_memalloc(sizeof(t_node*) * count);
	node->name = ft_strdup(name);
	node->links_count = count;
	node->x = 0;
	node->y = 0;
	//ft_printf("new node: '%s'\n", name);

	return node;
}
