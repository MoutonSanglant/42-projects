/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 06:34:20 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/11 22:00:38 by tdefresn         ###   ########.fr       */
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
** Count links in input
** allow duplicates
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

static void	link_to(t_node *a, t_node *b)
{
	size_t	i;

	i = 0;
	while (i < a->links_count)
	{
		if (!a->links[i])
			break;
		i++;
	}
	a->links[i] = b;
}

/*
** Create bidirectionnal links
*/
void		connect_nodes(t_node *a, t_node *b)
{
	t_node	*link;
	size_t	i;

	link = NULL;
	i = 0;
	while (i < a->links_count)
	{
		link = a->links[i];
		if (!link)
		{
			i++;
			continue;
		}
		if (ft_strequ(b->name, link->name))
			return;
		i++;
	}
	link_to(a, b);
	link_to(b, a);
	ft_printf("%s-%s\n", a->name, b->name);
}

/*
** Since count_node_links allows duplicates,
** it will allocate more memory than needed
** when user input is wrong
*/
t_node		*new_node(char *name, t_queue *links)
{
	t_node	*node;
	size_t	count;

	count = count_node_links(name, links);
	if (count < 1)
		return NULL;
	node = (t_node *)ft_memalloc(sizeof(t_node));
	ft_bzero(node, sizeof(t_node));
	node->links = (t_node **)ft_memalloc(sizeof(t_node*) * count);
	node->name = ft_strdup(name);
	node->links_count = count;
	//node->x = 0;
	//node->y = 0;

	return node;
}
