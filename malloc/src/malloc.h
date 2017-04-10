/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 16:05:48 by tdefresn          #+#    #+#             */
/*   Updated: 2017/03/22 16:05:48 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <pthread.h>

typedef struct	s_map
{
	void	*data;
	size_t	size;
	size_t	idx;
	size_t	alloc_max_size;
}				t_map;

typedef enum	e_malloc_map_type
{
	MALLOC_MAP_TINY = 0x0,
	MALLOC_MAP_SMALL = 0x1,
	MALLOC_MAP_LARGE = 0x2
}				t_malloc_map_type;

t_map				g_maps[3];
pthread_mutex_t		g_mutex;

void		free(void *ptr);
void		*malloc(size_t size);
void		*realloc(void *ptr, size_t size);

void		show_alloc_mem();

#endif
