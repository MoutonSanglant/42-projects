/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/19 00:09:45 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/10 17:58:33 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	parse_comment(t_lemin_parser *parser, char *line)
{
	t_key	key;

	if (*line != '#')
		return (0);
	key.type = TYPE_COMMENT;
	key.value = (void *)ft_strdup(line);
	queue_add_key(&parser->queue, &key);
	line++;
	parser->command = 0;
	if (ft_strequ(line, "#start"))
		parser->command = TYPE_START;
	else if (ft_strequ(line, "#end"))
		parser->command = TYPE_END;
	else if (*line == '#')
		parser->command = TYPE_ROOM;
	else
		parser->command = 0;
	return (1);
}

static int	parse_connection(t_lemin_parser *parser, char *line)
{
	static t_queue	*queue = NULL;

	if (!queue)
	{
		queue = parser->queue;
		while (queue)
		{
			if (!queue->next)
				break ;
			queue = queue->next;
		}
	}
	if (new_connection(&queue, line))
	{
		if (!parser->connections)
			parser->connections = queue->next;
		return (0);
	}
	return (1);
}

static int	parse_room(t_lemin_parser *parser, char *line)
{
	static t_type	mask = 0;
	t_type			type;

	type = TYPE_ROOM | parser->command;
	mask |= type;
	parser->command = 0;
	if (new_room(&parser->queue, line, type))
	{
		parser->rooms_count++;
		return (0);
	}
	else
	{
		if (mask != (TYPE_ROOM | TYPE_START | TYPE_END))
			error(ERR_MISSING_ROOM);
		parse_connection(parser, line);
	}
	return (1);
}

static int	parse_ants(t_lemin_parser *parser, char *line)
{
	char	**split;

	split = ft_strsplit(line, ' ');
	if (split[0] && split[1])
		error(ERR_INVALID_ANT_LINE);
	if ((parser->ants_count = ft_atoi(split[0])) < 1)
		error(ERR_INVALID_ANT_NUMBER);
	ft_memdel((void *)&split[0]);
	ft_memdel((void *)&split);
	return (1);
}

int			parse_line(char *line, void *st)
{
	static int		state = 0;
	static int		(*parse_fn[3])(t_lemin_parser *, char *) = {
		&parse_ants,
		&parse_room,
		&parse_connection
	};

	if (line[0] == 'L')
		error(ERR_L_PREFIX);
	if (parse_comment((t_lemin_parser *)st, line))
		return (1);
	if ((parse_fn[state])((t_lemin_parser *)st, line))
		state++;
	return (state < 3);
}
