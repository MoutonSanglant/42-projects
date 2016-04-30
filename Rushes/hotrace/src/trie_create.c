/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trie_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/23 18:15:20 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/01 01:53:27 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

static void		add_leaf(t_node *parent, char *leaf)
{
	parent->not_leaf = 0;
	parent->children = NULL;
	if ((char *)parent->children)
		memdel((void *)&parent->children);
	parent->children = (void **)leaf;
}

static void		create_node(t_node **parent, char value)
{
	t_node	*child;

	child = (t_node *)memalloc(sizeof(t_node));
	child->not_leaf = 1;
	child->children = NULL;
	child->value = value;
	(*parent)->children = (void **)memalloc(sizeof(t_node *) * 2);
	(*parent)->children[0] = (void *)child;
	(*parent)->children[1] = NULL;
	*parent = child;
}

static t_node	*realloc_node_list(t_node *parent, char value)
{
	t_node	**list_start;
	t_node	**list_end;
	t_node	**new_list;
	t_node	*new_child;
	int		new_size;

	list_start = (t_node **)parent->children;
	list_end = list_start;
	while (*list_end++)
		;
	new_child = (t_node *)memalloc(sizeof(t_node));
	new_child->not_leaf = 1;
	new_child->children = NULL;
	new_child->value = value;
	new_size = list_end - list_start;
	new_list = (t_node **)memalloc(sizeof(t_node *) * (new_size + 1));
	new_list = mem_move(new_list, list_start, sizeof(t_node *) * new_size);
	new_list[new_size - 1] = new_child;
	new_list[new_size] = NULL;
	memdel((void **)&list_start);
	parent->children = (void **)new_list;
	return (new_child);
}

static t_node	*get_matching_children(t_node **children, char value)
{
	while (*children)
	{
		if ((*children)->value == value)
		{
			(*children)->not_leaf = 1;
			return (*children);
		}
		children++;
	}
	return (NULL);
}

void			create_node_chain(const t_node *root, char *key, char *value)
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
				parent = realloc_node_list(parent, *key);
			else
				parent = child;
		}
		else
			create_node(&parent, *key);
		key++;
	}
	add_leaf(parent, value);
}
