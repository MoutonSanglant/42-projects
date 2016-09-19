/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/18 17:39:56 by tdefresn          #+#    #+#             */
/*   Updated: 2016/09/19 16:05:09 by tdefresn         ###   ########.fr       */
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

int			new_room(t_input *input, char *line, int command)
{
	t_queue	*room;

	if (valid_room_str(line))
	{
		room = ft_queuenew((void *)line, ft_strlen(line) + 1);
		if (!input->rooms)
			input->rooms = room;
		else
			ft_queuepush(input->rooms, room);
		if (command == 1)
			input->start = room;
		else if (command == 2)
			input->end = room;
		return (1);
	}
	return (0);
}
