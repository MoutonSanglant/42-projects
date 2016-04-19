/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_formated_space.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/24 09:44:05 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/19 19:31:01 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static void		justify(char c, t_fdata *fdatas)
{
	if (fdatas->flag & FLAG_SPACE)
		fdatas->output = ft_strconcat(fdatas->output, " ");
	if (ft_isprint(c))
		fdatas->output = ft_strnconcat(fdatas->output, &c, 1);
}

static int		format_error(const char *format, t_fdata *fdatas)
{
	if (format[0] != '%')
	{
		if (format[0] == '\0' || format[1] == '\0')
			fdatas->flag |= FLAG_FORMAT_ERROR;
		return (1);
	}
	return (0);
}

void			ft_print_formated_space(const char *format, t_fdata *fdatas)
{
	char	c;

	c = '%';
	if (format_error(format, fdatas))
		c = *format;
	fdatas->flag ^= (fdatas->flag & FLAG_SPACE) ? FLAG_SPACE : FLAG_NONE;
	fdatas->flag ^= (fdatas->flag & FLAG_MORE) ? FLAG_MORE : FLAG_NONE;
	if (fdatas->flag & FLAG_LESS)
		justify(c, fdatas);
	fdatas->width--;
	while (fdatas->width > 0)
	{
		if (!(fdatas->flag & FLAG_MORE) || fdatas->width > 1)
			fdatas->output = ft_strnconcat(fdatas->output, &fdatas->fill_char, 1);
		fdatas->width--;
	}
	if (!(fdatas->flag & FLAG_LESS))
		justify(c, fdatas);
}
