/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 20:14:00 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/22 00:15:04 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

/*
**	#define ft_eprintf(format, ...) ft_dprintf(stderr, format, __VA_ARGS__)
*/

int					ft_veprintf(const char *restrict format, va_list *ap)
{
	return (ft_vdprintf(2, format, ap));
}

int					ft_eprintf(const char *restrict format, ...)
{
	va_list		ap;
	int			count;

	va_start(ap, format);
	count = ft_veprintf(format, &ap);
	va_end(ap);
	return (count);
}
