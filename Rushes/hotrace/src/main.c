/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 20:37:14 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/24 22:42:52 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

void	get_key_value_pairs(const t_node *root)
{
	char	*input;
	char	*key;
	int		i;

	i = 0;
	while (1)
	{
		if (i % 2 == 0)
		{
			key = read_stdin();
			if (*key == '\n' || *key == '\0')
				break ;
		}
		else
		{
			input = read_stdin();
			create_node_chain(root, key, input);
			memdel((void **)&key);
		}
		i++;
	}
	memdel((void **)&key);
}

void	register_value(const t_node *root, t_list *list, char *key)
{
	char	*value;

	value = get_value_from_key(root, key);
	if (!value)
	{
		key[str_len(key) - 1] = '\0';
		list->value = key;
		list->value = strjoin(list->value, ": Not found.\n");
	}
	else
		list->value = value;
}

void	get_pairs(const t_node *root, t_list *list)
{
	char	*key;
	t_list	*last;

	last = list;
	key = NULL;
	while (1)
	{
		if (key)
			memdel((void **)&key);
		key = read_stdin();
		if (!key || *key == '\n' || *key == '\0')
			break ;
		register_value(root, list, key);
		list->next = (t_list *)memalloc(sizeof(t_list));
		last = list;
		list = list->next;
		list->value = NULL;
		list->next = NULL;
	}
	memdel((void **)&key);
	if (last->next)
		memdel((void **)&last->next);
	last->next = NULL;
}

void	get_keywords(const t_node *root)
{
	t_list	*list;
	t_list	*last;

	list = (t_list *)memalloc(sizeof(t_list));
	list->value = NULL;
	list->next = NULL;
	get_pairs(root, list);
	while (list)
	{
		if (list->value)
		{
			putstr(list->value);
			memdel((void **)&list->value);
		}
		last = list;
		list = list->next;
		memdel((void **)&last);
	}
}

int		main(void)
{
	static t_node	root;

	root.not_leaf = 1;
	root.value = '\0';
	root.children = NULL;
	root.leaf = NULL;
	get_key_value_pairs(&root);
	get_keywords(&root);
	return (0);
}
