/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strconcat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 22:05:42 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/18 22:09:59 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strconcat(char *s1, char const *s2)
{
	char	*tmp;

	tmp = s1;
	s1 = ft_strjoin(s1, s2);
	ft_strdel(&tmp);
	return (s1);
}
