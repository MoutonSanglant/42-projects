/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/17 22:49:52 by tdefresn          #+#    #+#             */
/*   Updated: 2016/09/17 23:25:14 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	delelem(void *content, size_t content_size)
{
	if (content)
	{
		(void)content_size;
		ft_bzero(content, content_size);
		ft_memdel((void **)&content);
	}
}
