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

# include <pthread.h>

# define PGM_NAME "philo"

# define STR_USAGE "philo ...\n"

# define OPTIONS_COUNT 2

# define ERRNO_USAGE	0x1
# define ERRNO_THREAD_CREATE	0x2
# define ERRNO_THREAD_JOIN		0x3
# define ERRNO_THREAD_DETACH	0x4

# define ERR_THREAD_CREATE "cannot create thread"
# define ERR_THREAD_JOIN "cannot join thread"
# define ERR_THREAD_DETACH "cannot detach thread"
# define ERR_UNDEFINED "undefined error"

/*
**	Time in seconds
*/
# define MAX_LIFE	10
# define EAT_T		1
# define REST_T		1
# define THINK_T	1
# define TIMEOUT	60

typedef enum	e_flags
{
	FLAG_NONE = 0x0,
	FLAG_COLOR = 0x1,
	FLAG_TEST = 0x2
}				t_flags;

typedef struct	s_option
{
	char	*l;
	t_flags	f;
	char	s;
}				t_option;

typedef enum	e_pstate
{
	STATE_SLEEP,
	STATE_EAT,
	STATE_THINK
}				t_pstate;

typedef struct	s_philo
{
	pthread_t	thread;
	char		*name;
	t_pstate	state;
	int			hp;
}				t_philo;

typedef struct	s_data
{
	t_flags		flags;
	int			count;
}				t_data;


t_data				g_datas;
pthread_mutex_t		g_mutex;


/*
**		== arguments.c
*/

void		parse_arguments(int count, char **arguments, t_data *data);

/*
**		== options.c
*/

void		match_options(char *arg, t_flags *flags);

/*
**		== threads.c
*/

void		*thread_start(void *);

/*
**		== errors.c
*/

void		error(int error, const char *description);
void		thread_error(int error, int errno);

#endif
