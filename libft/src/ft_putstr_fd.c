/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:36:40 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/19 19:23:33 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

int		ft_putstr_fd(char const *s, int fd)
{
	if (!s)
	{
		ERROR_PARAM("ft_putstr_fd");
		return (-1);
	}
	return (write(fd, s, ft_strlen(s)));
}

#else

int		ft_putstr_fd(char const *s, int fd)
{
	return (write(fd, s, ft_strlen(s)));
}
#endif
