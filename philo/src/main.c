/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 18:38:45 by tdefresn          #+#    #+#             */
/*   Updated: 2017/03/22 15:42:38 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <libftprintf.h>

#include "philo.h"

t_philo		g_philo[7] =
{
	{ .name = "Joe", .state = STATE_SLEEP, .hp = MAX_LIFE },
	{ .name = "Archimede", .state = STATE_SLEEP, .hp = MAX_LIFE },
	{ .name = "Ptoleme", .state = STATE_SLEEP, .hp = MAX_LIFE },
	{ .name = "Platon", .state = STATE_SLEEP, .hp = MAX_LIFE },
	{ .name = "Aristote", .state = STATE_SLEEP, .hp = MAX_LIFE },
	{ .name = "Socrate", .state = STATE_SLEEP, .hp = MAX_LIFE },
	{ .name = "Pline", .state = STATE_SLEEP, .hp = MAX_LIFE }
};

pthread_mutex_t		g_mutex;
t_data				g_datas;

/*
** 3 globales MAX autorisées !
** -
** 7 philosophes (_p)
** 1 thread / _p_
** 1 baguette à <-- de / _p_ (7 baguettes)
** seul les baguettes adjacentes peuvent être utilisées
** 1 baguette ne peut être utilisée en même temps par 2 _p_
** ETAPES:
** - EAT Mange (nécessite 3 baguettes)
** - REST Repos (0 baguette)
** - THINK Réfléchit (1 baguette ??)
** après l'état REST, un _p_ peut passer dans l'état 'EAT' ou 'THINK'
** un _p_ qui n'est pas dans l'état 'EAT' perd 1PV / secondes
*/

int		main(int argc, char **argv)
{
	int			err;
	int			i;

	ft_bzero(&g_datas, sizeof(t_data));
	parse_arguments(argc, argv, &g_datas);
	pthread_mutex_init(&g_mutex, NULL);
	i = 0;
	while (i < 7)
	{
		//pthread_t t;
		if ((err = pthread_create(&g_philo[i].thread, NULL, &thread_start, &g_philo[i])))
			thread_error(ERRNO_THREAD_CREATE, err);
		//if ((err = pthread_detach(*g_philo[i].thread)))
		//	thread_error(ERRNO_THREAD_DETACH, err);
		i++;
	}
	while (1)
	{
		if (g_datas.count >= 7)
			break;
	}
	// wait for thread 0 to end
	//if ((err = pthread_join(*g_philo[0].thread, NULL)))
	//	thread_error(ERRNO_THREAD_JOIN, err);
	return (0);
}
