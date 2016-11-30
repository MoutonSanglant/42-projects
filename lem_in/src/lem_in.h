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

# define ERR_MISSING_ROOM "missing start or end room"
# define ERR_HIDDEN_ROOM "start or end room is hidden by multiple records"
# define ERR_BAD_FORMAT "bad parser format (start/end commands on duplicate)"
# define ERR_INVALID_ANT_LINE "ant line format error"
# define ERR_INVALID_ANT_NUMBER "ant_count < 1"
# define ERR_L_PREFIX "a room name starts with a L"
# define ERR_NO_LINK "no link between START & END"

# define CMD_START 1
# define CMD_END 2
# define CMD_UNKNOWN 3
# define CMD_COMMENT 0

typedef enum	e_flags
{
	FLAG_COLORS = 0x1,
	FLAG_TURNS = 0x2
}				t_flags;

typedef enum	e_type
{
	TYPE_INVALID = 0x0,
	TYPE_ROOM = 0x1,
	TYPE_CONNECTION = 0x2,
	TYPE_START = 0x4,
	TYPE_END = 0x8,
	TYPE_COMMENT = 0x20
}				t_type;

typedef enum	e_state
{
	STATE_INVALID = 0x0,
	STATE_VALID = 0x1,
	STATE_BUSY = 0x2,
	STATE_START = 0x4,
	STATE_END = 0x8,
	STATE_DELETED = 0x100
}				t_state;

typedef struct s_node	t_node;

/*
** 8 + 8 + (4 + 4) + (4 + 4) + (4)
** = 40 {4}
*/
struct			s_node
{
	char		*name;
	t_node		**links;
	int			links_count;
	int			weight;
	int			x;
	int			y;
	t_state		state;
};

/*
** 8 + 8 + 8
** = 24 {-}
*/
typedef struct	s_ant
{
	char		*name;
	char		*color;
	t_node		*room;
}				t_ant;

/*
** 8 + (4 + 4)
** = 16 {-}
*/
typedef struct	s_room
{
	char	*name;
	int		x;
	int		y;
}				t_room;

/*
** 8 + 8
** = 16 {-}
*/
typedef struct	s_connection
{
	char	*from;
	char	*to;
}				t_connection;

/*
** 8 + 4
** = 16 {4}
*/
typedef struct	s_key
{
	void	*value;
	t_type	type;
}				t_key;

/*
** 8 + 8 + 8 + (4 + 4) + (4 + ...)
** = 36 {4}
*/
typedef struct	s_graph
{
	t_node		*start;
	t_node		*end;
	t_node		**root_links;
	t_ant		**ants;
	int			root_links_count;
	int			ants_count;
	int			sleeping_ants;
	t_flags		flags;
}				t_graph;

/*
** 8 + 8 + (4 + 4) + (4)
** = 32 {4}
*/
typedef struct	s_parser
{
	t_queue	*queue;
	t_queue	*connections;
	t_type	command;
	int		ants_count;
	int		rooms_count;
}				t_parser;

/*
** =============================== arguments.c ==============================
*/
void			parse_arguments(int count, char **arguments, t_graph *graph);

/*
** =============================== read_stin.c ==============================
*/
void			read_stdin(int (read_line)(char *, void *), void *st);

/*
** ================================= rooms.c ================================
*/
int				new_room(t_queue **queue, char *line, t_type type);

/*
** =============================== connection.c =============================
*/
int				new_connection(t_queue **queue, char *line);

/*
** ================================ parser.c ================================
*/
int				parse_line(char *line, void *st);

/*
** ============================== queue_tools.c =============================
*/
void			queue_add_key(t_queue **queue, t_key *key);

/*
** ================================= graph.c =================================
*/
void			new_graph(t_graph *graph, t_parser *parser);
void			clear_graph(t_graph *graph);

/*
** ================================= node.c =================================
*/
t_node			*new_node(t_room *room, t_queue *links);
void			connect_nodes(t_node *a, t_node *b);

/*
** ================================= link.c =================================
*/
void			create_node_links(t_node *g, t_node *n, t_queue *connections);

/*
** ================================= path.c =================================
*/
int				mark_all_path(t_node *root, int weight, t_graph *graph, int c);

/*
** ================================ resolve.c ===============================
*/
void			resolve(t_graph *graph);

/*
** ================================= ways.c =================================
*/
t_node			**new_ways_list(t_node *room);

/*
** ================================ errors.c ================================
*/
void			error(char *str);
void			memerror(void);

#endif
