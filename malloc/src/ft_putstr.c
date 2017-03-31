/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:36:49 by tdefresn          #+#    #+#             */
/*   Updated: 2017/03/29 12:25:53 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "internal.h"

#ifdef DEBUG

void	ft_putstr(char const *s)
{
	if (!s)
	{
		ERROR_PARAM("ft_putstr");
		return ;
	}
	write(1, s, ft_strlen(s));
}

#else

void	ft_putstr(char const *s)
{
	write(1, s, ft_strlen(s));
}
#endif
