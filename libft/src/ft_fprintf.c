/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 20:40:22 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/22 18:44:33 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

#ifdef FORBIDDEN

int			ft_vfprintf(FILE *stream, const char *restrict format, va_list *ap)
{
	return (ft_putstr_fd(ft_vdprintf(fileno(stream), format, ap), fd));
}

#else

int			ft_vfprintf(FILE *stream, const char *restrict format, va_list *ap)
{
	(void)stream;
	(void)format;
	(void)ap;
	return (-1);
}

#endif

int			ft_fprintf(FILE *stream, const char *restrict format, ...)
{
	va_list		ap;
	int			count;

	va_start(ap, format);
	count = ft_vfprintf(stream, format, &ap);
	va_end(ap);
	return (count);
}
