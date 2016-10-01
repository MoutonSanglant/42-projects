/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 21:40:00 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/01 21:49:16 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

#ifdef DEBUG

char	*ft_strdup(char const *s1)
{
	char	*str_new;
	char	*ptr;

	if (!s1)
	{
		ERROR_PARAM("ft_strdup");
		return (NULL);
	}
	str_new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (str_new)
	{
		ptr = str_new;
		while (*s1)
			*ptr++ = *s1++;
		*ptr = *s1;
	}
	return (str_new);
}

#else

char	*ft_strdup(char const *s1)
{
	char	*str_new;
	char	*ptr;

	str_new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (str_new)
	{
		ptr = str_new;
		while (*s1)
			*ptr++ = *s1++;
		*ptr = *s1;
	}
	return (str_new);
}
#endif
