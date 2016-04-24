/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/23 17:36:39 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/24 20:58:22 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

void			*memalloc(size_t size)
{
	void	*addr;

	if (!(addr = (void *)malloc(size)))
		error();
	return (addr);
}

void			memdel(void **ap)
{
	free(*ap);
	*ap = NULL;
}

void			*mem_move(void *dst, void const *src, size_t len)
{
	size_t		i;

	if (len == 0 || dst == src)
		return (dst);
	if ((char *)dst - ((const char *)src) < 0)
	{
		i = 0;
		while (i < len)
		{
			((char *)dst)[i] = ((const char *)src)[i];
			i++;
		}
	}
	else
	{
		i = len - 1;
		while (i > 0)
		{
			((char *)dst)[i] = ((const char *)src)[i];
			i--;
		}
		((char *)dst)[0] = ((const char *)src)[0];
	}
	return (dst);
}
