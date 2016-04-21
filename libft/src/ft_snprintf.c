/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 00:23:39 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/22 00:40:08 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

char	*ft_vsnprintf(size_t size, const char *restrict format, va_list *ap)
{
	char	*sprintf_out;
	char	*output;
	size_t	len;

	sprintf_out = ft_vsprintf(format, ap);
	len = ft_strlen(sprintf_out);
	size = (size < len) ? size : len;
	output = ft_strnew(size);
	output = ft_strncpy(output, sprintf_out, size);
	ft_strdel(&sprintf_out);
	return (output);
}

char	*ft_snprintf(size_t size, const char *restrict format, ...)
{
	va_list		ap;
	char		*output;

	va_start(ap, format);
	output = ft_vsnprintf(size, format, &ap);
	va_end(ap);
	return (output);
}
