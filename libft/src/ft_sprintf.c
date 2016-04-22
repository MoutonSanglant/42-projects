/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 20:30:45 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/22 19:02:49 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

char				*ft_vsprintf(const char *restrict format, va_list *ap)
{
	const char	*from_ptr;
	const char	*to_ptr;
	t_fdata		fdatas;

	fdatas.out = ft_strnew(1);
	fdatas.bcount = 0;
	from_ptr = format;
	while ((to_ptr = ft_strchr(from_ptr, '%')))
	{
		fdatas.out = ft_strnconcat(fdatas.out, from_ptr, (to_ptr - from_ptr));
		to_ptr = ft_get_formated_argument(ap, (to_ptr + 1), &fdatas);
		if (to_ptr == NULL)
		{
			ft_strdel(&fdatas.out);
			return (NULL);
		}
		to_ptr += 1;
		if (fdatas.flag & FLAG_FORMAT_ERROR)
			return (fdatas.out);
		from_ptr = to_ptr;
	}
	fdatas.out = ft_strconcat(fdatas.out, from_ptr);
	return (fdatas.out);
}

char				*ft_sprintf(const char *restrict format, ...)
{
	va_list		ap;
	char		*out;

	va_start(ap, format);
	out = ft_vsprintf(format, &ap);
	va_end(ap);
	return (out);
}
