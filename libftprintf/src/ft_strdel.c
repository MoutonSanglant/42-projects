/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 21:39:52 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/01 21:49:17 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

#ifdef DEBUG

void	ft_strdel(char **as)
{
	if (!as)
	{
		ERROR_PARAM("ft_strdel");
		return ;
	}
	if (!*as)
	{
		ERROR_FREE("ft_strdel");
		return ;
	}
	free(*as);
	*as = NULL;
}

#else

void	ft_strdel(char **as)
{
	free(*as);
	*as = NULL;
}
#endif
