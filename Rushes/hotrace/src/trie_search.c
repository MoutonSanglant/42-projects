/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trie_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/23 18:16:14 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/01 01:51:50 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

static t_node	*get_matching_children(t_node **children, char value)
{
	while (*children)
	{
		if ((*children)->value == value)
			return (*children);
		children++;
	}
	return (NULL);
}

char			*get_value_from_key(const t_node *root, char *key)
{
	t_node	*parent;
	t_node	*child;

	parent = (t_node *)root;
	while (*key)
	{
		if (parent->children)
		{
			child = get_matching_children((t_node **)parent->children, *key);
			if (!child)
				return (NULL);
			else if (*(key + 1) == '\0')
			{
				if (child->not_leaf)
					return (NULL);
				else
					return (str_dup((char *)child->children));
			}
			parent = child;
		}
		key++;
	}
	return (NULL);
}
