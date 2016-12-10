/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 13:47:06 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/07 13:47:06 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <libft.h>

# define BUFF_SIZE 128

# define TREE_RIGHT 1
# define TREE_LEFT 2
# define BRANCH(t, x) (x == TREE_RIGHT) ? t->right : t->left

int		get_next_line(const int fd, char **line);

typedef struct	s_2tree t_btree;

/*
** >> 8 + 8 + 8 + (4)
** >> 32
*/

struct	s_2tree
{
	char	*content;
	t_btree	*left;
	t_btree	*right;
	int		length;
};

/*
** >> 8 + (4 + 4) + (4)
** 24
*/

typedef struct	s_gnl
{
	t_btree	*lines;
	int		count;
	int		idx;
	int		eof;
}				t_gnl;

#endif
