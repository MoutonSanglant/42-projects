/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 15:04:08 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/08 15:28:14 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		help(void)
{
	ft_printf("%s, version %s\n\n", PROGRAM_NAME, PROGRAM_VERSION);
	ft_printf("%s\n\n", USAGE_MSG);
	ft_printf("%s\n%s\n", HELP_LINE1, HELP_LINE2);
	return (0);
}
