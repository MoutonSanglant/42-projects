/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnconcat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 22:23:41 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/18 22:25:51 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnconcat(char *s1, char const *s2, int n)
{
	char	*tmp;

	tmp = s1;
	s1 = ft_strnjoin(s1, s2, n);
	ft_strdel(&tmp);
	return (s1);
}
