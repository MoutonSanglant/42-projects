/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_window.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouton </var/spool/mail/mouton>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 23:53:54 by mouton            #+#    #+#             */
/*   Updated: 2017/09/10 00:30:42 by mouton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "errors.h"

int	parse_argument_width(const char *arg, void *user_data)
{
	static int	guard = 0;
	int			*width;

	if (guard++ > 0)
		error(ERRNO_MULTIPLE_WIDTH, NULL);
	width = (int *)user_data;
	*width = ft_atoi(arg);
	return (1);
}

int	parse_argument_height(const char *arg, void *user_data)
{
	static int	guard = 0;
	int *height;

	if (guard++ > 0)
		error(ERRNO_MULTIPLE_HEIGHT, NULL);
	height = (int *)user_data;
	*height = ft_atoi(arg);
	return (1);
}
