/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/18 17:39:56 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/20 19:39:22 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Check for:
** - space at start
** - space at end
** - consecutive spaces
** - space count is 2
*/
static int	valid_room_str(char *str)
{
	int		i;

	if (ft_isspace(*str))
		return (0);
	i = 0;
	while (*str)
	{
		if (*str == ' ')
		{
			str++;
			if (*str == '\0' || *str == ' ')
				return (0);
			i++;
		}
		str++;
	}
	if (i == 2)
		return (1);
	return (0);
}

static int	is_duplicate(t_queue *queue, char *name)
{
	t_room	*room;
	t_key	*key;

	while (queue)
	{
		key = (t_key *)queue->content;
		if (key->type & TYPE_ROOM)
		{
			room = (t_room *)key->value;
			if (ft_strequ(name, room->name))
				return (1);
		}
		queue = queue->next;
	}
	return (0);
}


int		new_room(t_queue **queue, char *line, t_type type)
{
	t_room	*room;
	t_key	key;
	char	**split;
	int		i;

	if (valid_room_str(line))
	{
		split = ft_strsplit(line, ' ');
		if (is_duplicate(*queue, split[0]))
		{
			i = 0;
			while (split[i])
				ft_memdel((void *)&split[i++]);
			ft_memdel((void *)&split);
			return (1);
		}
		room = (t_room *)malloc(sizeof(t_room));
		room->name = split[0];
		room->x = ft_atoi(split[1]);
		room->y = ft_atoi(split[2]);
		i = 1;
		while (split[i])
			ft_memdel((void *)&split[i++]);
		ft_memdel((void *)&split);
		key.type = type;
		key.value = (void *)room;
		queue_add_key(queue, &key);
		return (1);
	}
	return (0);
}
