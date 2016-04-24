/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 19:34:40 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/24 22:29:55 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

int		str_len(const char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*str_dup(char *src)
{
	char	*dst;
	int		i;

	dst = (char *)memalloc(sizeof(char) * (str_len(src) + 1));
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*strjoin(char *s1, const char *s2)
{
	char	*str_new;
	char	*ptr;
	char	*ptr_s1;

	ptr_s1 = s1;
	str_new = (char *)memalloc(sizeof(char)
								* (str_len(s1) + str_len(s2) + 1));
	if (str_new)
	{
		ptr = str_new;
		while (*s1)
			*ptr++ = *s1++;
		while (*s2)
			*ptr++ = *s2++;
		*ptr++ = '\0';
	}
	return (str_new);
}

void	putstr(char *str)
{
	write(1, str, str_len(str));
}
