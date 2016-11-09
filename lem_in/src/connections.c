/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/18 17:39:21 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/09 16:54:29 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Check for:
** - space count is 0
** - `-` count is 1
*/

static int	valid_str(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (*str)
	{
		if (*str == ' ')
			i++;
		else if (*str == '-')
			j++;
		str++;
	}
	if (i < 1 && j == 1)
		return (1);
	return (0);
}

static int	is_duplicate(t_queue *queue, char *from, char *to)
{
	t_connection	*connection;
	t_key			*key;
	int				match_a;
	int				match_b;

	while (queue)
	{
		key = (t_key *)queue->content;
		if (key->type & TYPE_CONNECTION)
		{
			match_a = 0;
			match_b = 0;
			connection = (t_connection *)((t_key *)queue->content)->value;
			match_a |= ft_strequ(from, connection->from);
			match_a |= ft_strequ(from, connection->to);
			match_b |= ft_strequ(to, connection->from);
			match_b |= ft_strequ(to, connection->to);
			if (match_a && match_b)
				return (1);
		}
		queue = queue->next;
	}
	return (0);
}

int			new_connection(t_queue **queue, char *line)
{
	t_connection	*connection;
	t_queue			*el;
	t_key			key;
	char			**split;

	if (valid_str(line))
	{
		split = ft_strsplit(line, '-');
		if (is_duplicate((*queue)->next, split[0], split[1]))
		{
			ft_memdel((void *)&split[0]);
			ft_memdel((void *)&split[1]);
			ft_memdel((void *)&split);
			return (1);
		}
		connection = (t_connection *)malloc(sizeof(t_connection));
		connection->from = split[0];
		connection->to = split[1];
		ft_memdel((void *)&split);
		key.type = TYPE_CONNECTION;
		key.value = (void *)connection;
		el = ft_queuenew((void *)&key, sizeof(t_key));
		if (!*queue)
			*queue = el;
		else
			ft_queuepush(*queue, el);
		return (1);
	}
	return (0);
}
