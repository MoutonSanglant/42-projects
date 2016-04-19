/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_formated_char.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 09:45:47 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/19 19:27:59 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"



static void		justify(wint_t *c, t_fdata *fdatas)
{

	if (fdatas->flag & FLAG_SPACE)
		fdatas->output = ft_strconcat(fdatas->output, " ");
	if (fdatas->length == LENGTH_L)
		fdatas->output = ft_strconcat(fdatas->output, ft_towstr((wchar_t *)c));
	else
		fdatas->output = ft_strnconcat(fdatas->output, (char *)c, 1);
}

static int		unicode_length(t_fdata *fdatas, wint_t c)
{
	if (c < (1 << 7))
	{
		fdatas->length = LENGTH_NONE;
		return (0);
	}
	else if (c < (1 << 11))
		return (2);
	else if (c < (1 << 16))
		return (3);
	else
		return (4);
	return (0);
}

void			ft_print_formated_char(va_list *ap, t_fdata *fdatas)
{
	wint_t	c;

	c = 0;
	if (fdatas->length == LENGTH_NONE)
		c = va_arg(*ap, int);
	else if (fdatas->length == LENGTH_L)
	{
		c = (wint_t)va_arg(*ap, wint_t);
		fdatas->width -= unicode_length(fdatas, c);
		fdatas->width++;
	}
	fdatas->flag ^= (fdatas->flag & FLAG_SPACE) ? FLAG_SPACE : FLAG_NONE;
	fdatas->flag ^= (fdatas->flag & FLAG_MORE) ? FLAG_MORE : FLAG_NONE;
	if (fdatas->flag & FLAG_LESS)
		justify(&c, fdatas);
	fdatas->width--;
	while (fdatas->width > 0)
	{
		if (!(fdatas->flag & FLAG_MORE) || fdatas->width > 1)
			fdatas->output = ft_strnconcat(fdatas->output, &fdatas->fill_char, 1);
		fdatas->width--;
	}
	if (!(fdatas->flag & FLAG_LESS))
		justify(&c, fdatas);
}
