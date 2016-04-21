/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_formated_widechar.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/21 21:02:09 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/21 22:08:48 by tdefresn         ###   ########.fr       */
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
	char	*str;
	int		ret;

	if (fdatas->flag & FLAG_SPACE)
		fdatas->output = ft_strconcat(fdatas->output, " ");
	if (fdatas->length == LENGTH_L)
	{
		str = ft_towstr((wchar_t *)c, &ret);
		fdatas->output = ft_strconcat(fdatas->output, str);
	}
	else
		fdatas->output = ft_strnconcat(fdatas->output, (char *)c, 1);
}

static int		unicode_length(t_fdata *fdatas, wint_t c)
{
	const int	mask12 = 0b00000000000000000000100000000000;
	const int	mask16 = 0b00000000000000010000000000000000;

	if (c < 128)
	{
		fdatas->length = LENGTH_NONE;
		return (0);
	}
	else if (c < mask12)
		return (1);
	else if (c < mask16)
		return (2);
	else
		return (3);
	return (0);
}

void			ft_print_formated_widechar(va_list *ap, t_fdata *fdatas)
{
	wint_t	c;
	int		unicode_len;

	c = (wint_t)va_arg(*ap, wint_t);
	unicode_len = unicode_length(fdatas, c);
	fdatas->width -= (unicode_len + 1);
	fdatas->flag ^= (fdatas->flag & FLAG_SPACE) ? FLAG_SPACE : FLAG_NONE;
	fdatas->flag ^= (fdatas->flag & FLAG_MORE) ? FLAG_MORE : FLAG_NONE;
	if (fdatas->flag & FLAG_LESS)
		justify(&c, fdatas);
	while (fdatas->width > 0)
	{
		if (!(fdatas->flag & FLAG_MORE) || fdatas->width > 1)
			fdatas->output = ft_strnconcat(fdatas->output, &fdatas->fill_char, 1);
		fdatas->width--;
	}
	if (!(fdatas->flag & FLAG_LESS))
		justify(&c, fdatas);
}
