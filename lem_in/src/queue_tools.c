/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/18 23:00:48 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/18 23:09:34 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	queue_add_key(t_queue **queue, t_key *key)
{
	t_queue	*el;

	el = ft_queuenew((void *)key, sizeof(t_key));
	if (!*queue)
		*queue = el;
	else
		ft_queuepush(*queue, el);
}
