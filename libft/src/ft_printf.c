/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 20:30:37 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/22 00:15:17 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

/*
**	#define ft_printf(format, ...) ft_dprintf(stdout, format, __VA_ARGS__)
*/

int					ft_vprintf(const char *restrict format, va_list *ap)
{
	return (ft_vdprintf(1, format, ap));
}

int					ft_printf(const char *restrict format, ...)
{
	va_list		ap;
	int			count;

	va_start(ap, format);
	count = ft_vprintf(format, &ap);
	va_end(ap);
	return (count);
}
