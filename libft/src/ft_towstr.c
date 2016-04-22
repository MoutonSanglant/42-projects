/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_towstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 19:00:23 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/22 19:17:15 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

/*
**	h
**	xxxxxxx
**	|0xxxxxxx|
**	h+1		h
**	yyy|yyxxxxxx|
**	|110yyyyy|10xxxxxx|
**	h+1			h
**	|zzzzyyyy|yyxxxxxx|
**	|1110zzzz|10yyyyyy|10xxxxxx|
**	h+2		h+1		h
**	wwwzz|zzzzyyyy|yyxxxxxx|
**	|11110www|10zzzzzz|10yyyyyy|10xxxxxx|
*/

/*
**	mask12 = 0b00000000000000000000100000000000; <=> (1 << 11)
**	mask16 = 0b00000000000000010000000000000000; <=> (1 << 16)
*/

static int		convert(unsigned char *h, char *str, wchar_t c)
{
	int			i;

	i = 0;
	if (c > MASK21 || c < 0)
		return (-1);
	if (c < MASK11)
		str[i++] = ((((*h & 0b11000000) >> 6) | ((*(h + 1) << 2)
						& 0b00011111)) | 0b11000000);
	else
	{
		if (c < MASK16)
			str[i++] = (((*(h + 1) & 0b11110000) >> 4) | 0b11100000);
		else
		{
			str[i++] = (((*(h + 2) & 0b00011100) >> 2) | 0b11110000);
			str[i++] = ((((*(h + 1) & 0b11110000) >> 4) | ((*(h + 2) << 4)
							& 0b00111111)) | 0b10000000);
		}
		str[i++] = ((((*h & 0b11000000) >> 6) | ((*(h + 1) << 2)
							& 0b00111111)) | 0b10000000);
	}
	str[i++] = ((*h & 0b00111111) | 0b10000000);
	return (i);
}

#ifdef DEBUG

static char		*debug_ft_towstr(wchar_t *unicode_point, int *len)
{
	char	*str;
	wchar_t	c;

	*len = 0;
	c = *unicode_point;
	if (c < 128)
	{
		str = ft_strnew(1);
		str[0] = *((unsigned char *)unicode_point);
		*len = 1;
	}
	else
	{
		str = ft_strnew(4);
		*len = convert((unsigned char *)unicode_point, str, c);
		if (*len < 0)
		{
			ft_strdel(&str);
			return (NULL);
		}
	}
	str[*len] = '\0';
	return (str);
}

char			*ft_towstr(wchar_t *unicode_point, int *len)
{
	if (!unicode_point)
	{
		ERROR_PARAM("ft_towstr");
		return (0);
	}
	return (debug_ft_towstr(unicode_point));
}

#else

char			*ft_towstr(wchar_t *unicode_point, int *len)
{
	char	*str;
	wchar_t	c;

	*len = 0;
	c = *unicode_point;
	if (c < 128)
	{
		str = ft_strnew(1);
		str[0] = *((unsigned char *)unicode_point);
		*len = 1;
	}
	else
	{
		str = ft_strnew(4);
		*len = convert((unsigned char *)unicode_point, str, c);
		if (*len < 0)
		{
			ft_strdel(&str);
			return (NULL);
		}
	}
	str[*len] = '\0';
	return (str);
}
#endif
