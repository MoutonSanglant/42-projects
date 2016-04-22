/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 20:43:30 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/22 20:43:30 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOTRACE_H
# define HOTRACE_H

#include <unistd.h>
#include <stdlib.h>

# define BUFF_SIZE 1024

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
	struct s_node	**children;
	char			value;
}				t_node;

/*
** 	==============
**	==	INPUT	==
**	==============
*/

char			*read_stdin();

/*
** 	==============
**	==	STRINGS	==
**	==============
*/

int				strlength(const char *str);
void			putstr(char *str);
char			*strjoin(char const *s1, char const *s2);

/*
** 	==============
**	==	MEMORY	==
**	==============
*/

void			*memalloc(size_t size);
void			memdel(void **ap);

#endif
