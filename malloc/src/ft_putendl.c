/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:37:07 by tdefresn          #+#    #+#             */
/*   Updated: 2017/03/29 12:26:02 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "internal.h"

#ifdef DEBUG

void	ft_putendl(char const *s)
{
	if (!s)
	{
		ERROR_PARAM("ft_putendl");
		return ;
	}
	ft_putstr(s);
	write(1, "\n", 1);
}

#else

void	ft_putendl(char const *s)
{
	ft_putstr(s);
	write(1, "\n", 1);
}
#endif
