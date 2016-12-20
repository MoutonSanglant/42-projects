/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 19:12:53 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/15 19:57:43 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include "philo.h"

void	*thread_start(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	ft_putstr("My name is ");
	ft_putstr(philo->name);
	ft_putendl("");
	return ((void*)1);
}
