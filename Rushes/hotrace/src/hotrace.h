/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 20:43:30 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/24 19:25:56 by bbetz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOTRACE_H
# define HOTRACE_H

# include <unistd.h>
# include <stdlib.h>

# define BUFF_SIZE 2048

/*
**	Data structure is:
**	  [int]		4-bytes
**	  [*]		8-bytes
**	  [char]	1-bytes
**	-------------------
**	biggest:	8-bytes
**	total:		13-bytes
**	-------------------
**	expanded:	16-bytes
**	unused:		3-bytes
*/

typedef struct	s_node
{
	int				not_leaf;
	void			**children;
	char			value;
}				t_node;

typedef struct	s_list
{
	struct s_list	*next;
	char			*value;
}				t_list;

void			error();

/*
** 	==============
**	==	INPUT	==
**	==============
*/

char			*read_stdin();

/*
** 	==============
**	==	TRIE	==
**	==============
*/

void			create_node_chain(const t_node *root, char *key, char *value);
char			*get_value_from_key(const t_node *root, char *key);

/*
** 	==============
**	==	STRINGS	==
**	==============
*/

int				str_len(const char *str);
void			putstr(char *str);
char			*str_dup(char *src);
char			*strjoin(char *s1, const char *s2);
void			strjoin_nl(char *s1, const char *s2, int *idx);

/*
** 	==============
**	==	MEMORY	==
**	==============
*/

void			*memalloc(size_t size);
void			memdel(void **ap);
void			*mem_move(void *dst, void const *src, size_t len);
void			mem_move2(void **dst, void const *src, size_t len);
#endif
