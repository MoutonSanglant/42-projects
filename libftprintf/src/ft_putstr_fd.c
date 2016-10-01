/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 21:38:49 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/01 21:49:30 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

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
