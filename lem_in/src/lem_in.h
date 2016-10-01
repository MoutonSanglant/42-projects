/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/18 04:20:37 by tdefresn          #+#    #+#             */
/*   Updated: 2016/09/18 04:20:37 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <libft.h>
# include <libftprintf.h>


/*
** type:
** 0 -> normal
** 1 -> start
** 2 -> end
** ==========
** packing:
** 8 + 8 + (4 i 2 + 2)
** --> 28 (no loss)
*/
typedef struct	s_node
{
	struct s_node	**links;
	char			*name;
	size_t			links_count;
	short			x;
	short			y;
}				t_node;

typedef struct	s_graph
{
	t_node		*start;
	t_node		*end;

}				t_graph;

typedef struct	s_ant
{
	t_node		*room;
}				t_ant;

/*
** state:
** 0 -> read_ant_count
** 1 -> read_rooms
** 2 -> read_connections
** 3 -> done
** packing:
** 8 + 8 + 8 + (4 + 4)
** --> 32 (no loss)
*/
typedef struct	s_input
{
	t_graph	*graph;
	t_queue	*rooms;
	t_queue	*connections;
	t_queue *start;
	t_queue *end;
	int		ant_count;
	int		state;
}				t_input;

void	read_stdin(int (callback)(char *, void *), void *st);

int		new_room(t_input *input, char *line, int command);
int		new_connection(t_queue **connections, char *line);

/* ================================= Graphs ================================= */
t_graph	*new_graph(t_input *input);
t_node	*new_node(char *name, t_queue *links);
void	connect_nodes(t_node *a, t_node *b);
void	new_link(t_node *node_a, t_node *node_b);
void	parse_connections(t_node *graph, char *name, t_queue *connections);

void	error(char *str);
void	memory_error(void);

#endif
