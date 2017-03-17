/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 18:38:45 by tdefresn          #+#    #+#             */
/*   Updated: 2017/01/18 16:21:02 by tdefresn         ###   ########.fr       */
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

/*
** 3 globales MAX autorisées !
** -
** 7 philosophes (_p)
** 1 thread / _p_
** 1 baguette à <-- de / _p_ (7 baguettes)
** seul les baguettes adjacentes peuvent être utilisées
** 1 baguette ne peut être utilisée en même temps par 2 _p_
** ETAPES:
** - EAT Mange (nécessite 2 baguettes)
** - REST Repos (0 baguette)
** - THINK Réfléchit (1 baguette ??)
** après l'état REST, un _p_ peut passer dans l'état 'EAT' ou 'THINK'
** un _p_ qui n'est pas dans l'état 'EAT' perd 1PV / secondes
*/

int		main(int argc, char **argv)
{
	t_flags		flags;
	int			err;
	int			i;

	flags = 0;
	parse_arguments(argc, argv, &flags);
	ft_putendl("== arguments:");
	ft_printf("flags: %x\n", flags);
	if (flags & FLAG_COLOR)
		ft_putendl("colors");
	if (flags & FLAG_TEST)
		ft_putendl("test");
	i = 0;
	while (i < 7)
	{
		if ((err = pthread_create(g_philo[i].thread, NULL, &thread_start, &g_philo[i])))
			error(ERR_THREAD_CREATE, err);
		if ((err = pthread_join(*g_philo[i].thread, NULL)))
			error(ERR_THREAD_JOIN, err);
		if ((err = pthread_detach(*g_philo[i].thread)))
			error(ERR_THREAD_DETACH, err);
		i++;
	}
	return (0);
}
