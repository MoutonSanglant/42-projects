/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 10:44:05 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/06 11:38:52 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		refresh(t_select *select)
{
	static t_select		*s_select = NULL;

	if (!s_select)
		s_select = select;
	clear(s_select);
	display_list(s_select, s_select->list);
}
