/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 19:23:43 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/15 19:31:54 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include "philo.h"

void	error(char *str, int err)
{
	ft_putstr_fd(PGM_NAME, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" (error: ", 2);
	ft_putnbr_fd(err, 2);
	ft_putendl_fd(")", 2);
	exit (err);
}
