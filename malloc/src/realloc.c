/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 16:17:33 by tdefresn          #+#    #+#             */
/*   Updated: 2017/03/22 16:24:04 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*realloc(void *ptr, size_t size)
{
	void	*new_ptr;
	int		err;

	(void)size;
	err = 0;
	new_ptr = ptr;
	if (err)
		return (NULL);
	return (new_ptr);
}
