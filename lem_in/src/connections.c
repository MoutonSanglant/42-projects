/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/18 17:39:21 by tdefresn          #+#    #+#             */
/*   Updated: 2016/09/19 20:49:58 by tdefresn         ###   ########.fr       */
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

int			new_connection(t_queue **connections, char *line)
{
	t_queue	*connection;

	if (valid_str(line))
	{
		connection = ft_queuenew((void *)line, ft_strlen(line) + 1);
		if (!*connections)
			*connections = connection;
		else
			ft_queuepush(*connections, connection);
		return (1);
	}
	return (0);
}
