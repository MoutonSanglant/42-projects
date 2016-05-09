/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stackpop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 14:44:28 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/10 01:33:30 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

t_stack		*ft_stackpop(t_stack **astack)
{
	t_stack	*top;

	if (!astack)
	{
		ERROR_PARAM("ft_stackpop");
		return (NULL);
	}
	top = *astack;
	if (top->prev)
	{
		*astack = top->prev;
		//ft_memdel((void *)&top);
	}
	else
		return (NULL);
		//ft_memdel((void **)astack);
	return (top);
}

#else

t_stack		*ft_stackpop(t_stack **astack)
{
	t_stack	*top;

	top = *astack;
	if (top->prev)
	{
		*astack = top->prev;
		//ft_memdel((void *)&top);
	}
	else
		return (NULL);
		//ft_memdel((void **)astack);
	return (top);
}
#endif
