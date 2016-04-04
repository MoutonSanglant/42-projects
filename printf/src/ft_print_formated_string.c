/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_formated_string.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 16:07:37 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/24 14:52:56 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static void		print_formated_string(t_fdata *fdatas, char *str)
{
	int		len;

	len = ft_strlen(str);
	fdatas->precision = (fdatas->precision >= 0) ? fdatas->precision : len;
	fdatas->precision = (fdatas->precision < len) ? fdatas->precision : len;
	fdatas->width = fdatas->width - fdatas->precision;
	if (fdatas->flag & FLAG_LESS)
		fdatas->bcount += write(1, str, fdatas->precision);
	while (fdatas->width > 0)
	{
		fdatas->bcount += write(1, &fdatas->fill_char, 1);
		fdatas->width--;
	}
	if (!(fdatas->flag & FLAG_LESS))
		fdatas->bcount += write(1, str, fdatas->precision);
}

static int		justify_long_string(wchar_t *wstr, t_fdata *fdatas, int dry)
{
	int		r_bytes;
	int		w_bytes;
	int		n;

	r_bytes = -1;
	w_bytes = 0;
	while (wstr[++r_bytes])
	{
		n = 4;
		if (wstr[r_bytes] < (1 << 7))
			n = 1;
		else if (wstr[r_bytes] < (1 << 11))
			n = 2;
		else if (wstr[r_bytes] < (1 << 16))
			n = 3;
		w_bytes += n;
		if (w_bytes > fdatas->precision)
		{
			w_bytes -= n;
			break ;
		}
		else if (!dry)
			fdatas->bcount += ft_putwchar(&wstr[r_bytes]);
	}
	return (w_bytes);
}

static void		print_formated_long_string(t_fdata *fdatas, wchar_t *wstr)
{
	int		w_bytes;

	fdatas->precision = (fdatas->precision >= 0) ? fdatas->precision : INT_MAX;
	w_bytes = justify_long_string(wstr, fdatas, 1);
	if (fdatas->flag & FLAG_LESS)
		justify_long_string(wstr, fdatas, 0);
	fdatas->width = (fdatas->width > 0) ? fdatas->width : 0;
	fdatas->width -= w_bytes;
	while (fdatas->width-- > 0)
		fdatas->bcount += write(1, &fdatas->fill_char, 1);
	if (!(fdatas->flag & FLAG_LESS))
		justify_long_string(wstr, fdatas, 0);
}

void			ft_print_formated_string(va_list *ap, t_fdata *fdatas, char *s)
{
	wchar_t		*wstr;
	char		*str;

	str = NULL;
	wstr = NULL;
	if (s != NULL)
		str = s;
	else if (fdatas->length == LENGTH_L)
		wstr = (wchar_t *)va_arg(*ap, wchar_t *);
	else
		str = va_arg(*ap, char *);
	if (!str && !wstr)
	{
		fdatas->precision = (fdatas->precision < 0) ? 7 : fdatas->precision;
		if (fdatas->precision < 6)
			str = ft_strdup(" ");
		else
			str = ft_strdup("(null)");
		print_formated_string(fdatas, str);
		ft_strdel(&str);
	}
	else if (str)
		print_formated_string(fdatas, str);
	else
		print_formated_long_string(fdatas, wstr);
}
