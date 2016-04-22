/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 00:14:36 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/22 19:22:10 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int			ft_vdprintf(int fd, const char *restrict format, va_list *ap)
{
	char	*output;
	int		ret;

	if ((output = ft_vsprintf(format, ap)))
	{
		ret = ft_putstr_fd(output, fd);
		ft_strdel(&output);
		return (ret);
	}
	return (-1);
}

int			ft_dprintf(int fd, const char *restrict format, ...)
{
	va_list		ap;
	int			count;

	va_start(ap, format);
	count = ft_vdprintf(fd, format, &ap);
	va_end(ap);
	return (count);
}
