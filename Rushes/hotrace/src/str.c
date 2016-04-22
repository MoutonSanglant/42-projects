/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 21:15:58 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/22 21:19:44 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

int		strlength(const char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*strjoin(char const *s1, char const *s2)
{
	char	*str_new;
	char	*ptr;

	str_new = (char *)memalloc(strlength(s1) + strlength(s2));
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
	write(1, str, strlength(str));
}
