/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 21:40:20 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/01 21:49:11 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

#ifdef DEBUG

size_t	ft_strlen(char const *s)
{
	size_t	i;

	if (!s)
	{
		ERROR_PARAM("ft_strlen");
		return (0);
	}
	i = 0;
	while (*s++ != '\0')
		i++;
	return (i);
}

#else

size_t	ft_strlen(char const *s)
{
	size_t	i;

	i = 0;
	while (*s++ != '\0')
		i++;
	return (i);
}
#endif
