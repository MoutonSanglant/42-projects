/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_formated_char.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 09:45:47 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/21 20:57:18 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

/*
**	Case not handled:
**	(*c == 0)
*/

static void		justify(wint_t *c, t_fdata *fdatas)
{
	if (fdatas->flag & FLAG_SPACE)
		fdatas->output = ft_strconcat(fdatas->output, " ");
	else
		fdatas->output = ft_strnconcat(fdatas->output, (char *)c, 1);
}

void			ft_print_formated_char(va_list *ap, t_fdata *fdatas)
{
	wint_t	c;

	c = 0;
	if (fdatas->length == LENGTH_NONE)
		c = (wint_t)va_arg(*ap, int);
	else if (fdatas->length == LENGTH_L)
	{
		ft_print_formated_widechar(ap, fdatas);
		return ;
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
