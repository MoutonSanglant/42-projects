/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_selected.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 19:08:18 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/17 19:08:30 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		is_selected(t_select *select, char *el)
{
	t_list	*l;

	l = select->selected;
	while (l)
	{
		if (ft_strequ(el, (char *)l->content))
			return (1);
		l = l->next;
	}
	return (0);
}
