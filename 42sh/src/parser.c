/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/10 14:42:15 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/25 16:46:25 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void			keep_content(void *content, size_t size)
{
	(void)content;
	(void)size;
	return ;
}

static t_list		*del_elem(t_list *elem)
{
	t_list	*next;

	next = elem->next;
	ft_lstdelone(&elem, &keep_content);
	return (next);
}

static t_list		*add_word(t_list *word_list, int idx, char **word)
{
	t_list	*start;
	char	*tmp;

	tmp = ft_strnew(idx);
	ft_strncpy(tmp, *word, idx);
	*word = NULL;
	if (!word_list)
	{
		word_list = ft_lstnew((void *)tmp, idx + 1);
		start = word_list;
	}
	else
	{
		start = word_list;
		while (word_list->next)
			word_list = word_list->next;
		word_list->next = ft_lstnew((void *)tmp, idx + 1);
	}
	ft_strdel(&tmp);
	return (start);
}

static t_list		*split_input(char *input)
{
	t_list	*word_list;
	char	*word;
	int		i;

	i = 0;
	word = NULL;
	word_list = NULL;
	while (*input)
	{
		if (!word)
			word = &input[i];
		if (input[i] == '\0')
			return (add_word(word_list, i, &word));
		else if (input[i] == '\\')
			i++;
		else if (ft_isspace(input[i]))
		{
			word_list = add_word(word_list, i, &word);
			input = &input[i + 1];
			i = 0;
			continue ;
		}
		i++;
	}
	return (word_list);
}

char				**parse_input(char *input)
{
	char	**blocks;
	char	**first_block;
	t_list	*word_list;

	input = ft_strtrim(input);
	if (*input == '\0')
	{
		ft_strdel(&input);
		return ((char **)ft_memalloc(sizeof(char *)));
	}
	word_list = split_input(input);
	first_block =
		(char **)ft_memalloc(sizeof(char *) * (ft_lstsize(word_list) + 1));
	blocks = first_block;
	while (word_list)
	{
		*blocks = (char *)word_list->content;
		word_list = del_elem(word_list);
		blocks++;
	}
	*blocks = NULL;
	first_block = unescape(first_block);
	ft_strdel(&input);
	return (first_block);
}
