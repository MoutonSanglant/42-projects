/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 12:59:44 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/11 12:59:44 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>

# define PGM_NAME "philo"
# define ERR_THREAD_CREATE "cannot create thread"
# define ERR_THREAD_JOIN "cannot join thread"
# define ERR_THREAD_DETACH "cannot detach thread"

/*
**	Time in secondes
*/
# define MAX_LIFE	10
# define EAT_T		1
# define REST_T		1
# define THINK_T	1
# define TIMEOUT	60

typedef enum	e_flags
{
	FLAG_COLOR = 0x1,
	FLAG_TEST = 0x2
}				t_flags;

typedef struct	s_args
{
	char	*string;
	t_flags	flag;
	char	c;
}				t_args;

typedef enum	e_pstate
{
	STATE_SLEEP,
	STATE_EAT,
	STATE_THINK
}				t_pstate;

typedef struct	s_philo
{
	pthread_t	*thread;
	char		*name;
	t_pstate	state;
	int			hp;
}				t_philo;

/*
**			arguments.c
*/
int			parse_arguments(int count, char **arguments, t_flags *flags);

/*
**			threads.c
*/
void		*thread_start(void *);

/*
**			errors.c
*/
void		error(char *str, int err);

#endif
