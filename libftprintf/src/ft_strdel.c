/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 21:39:52 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/03 03:31:39 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

#ifdef DEBUG

void	ft_strdel(char **as)
{
	if (!as)
	{
		ft_printf("ft_strdel: param error");
		return ;
	}
	if (!*as)
	{
		ft_printf("ft_strdel: free error");
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
