/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 19:12:53 by tdefresn          #+#    #+#             */
/*   Updated: 2017/03/22 15:42:21 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include "philo.h"

void	*thread_start(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while(1)
	{
		if (pthread_mutex_trylock(&g_mutex) == 0)
			break ;
	}
	ft_putstr("My name is ");
	ft_putendl(philo->name);
	g_datas.count++;
	pthread_mutex_unlock(&g_mutex);
	return ((void *)1);
}
