/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 20:40:22 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/18 21:34:45 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"


int			ft_vfprintf(int fd, const char *restrict format, va_list *ap)
{
	(void)fd;
	return (ft_vsprintf(format, ap));
}

int			ft_fprintf(int fd, const char *restrict format, ...)
{
	va_list		ap;
	int			count;

	va_start(ap, format);
	count = ft_vfprintf(fd, format, &ap);
	va_end(ap);
	return (count);
}
