/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 18:29:50 by tdefresn          #+#    #+#             */
/*   Updated: 2017/03/18 14:31:01 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	match_short(const t_option *options, char *arg, t_flags *flags)
{
	t_option	opt;
	int			len;
	int			i;
	int			j;

	i = 0;
	len = (int)ft_strlen(arg);
	while (i < len)
	{
		j = 0;
		while (j < OPTIONS_COUNT)
		{
			opt = options[j];
			if (arg[i] == opt.s)
			{
				*flags |= opt.f;
				break ;
			}
			j++;
		}
		if (j >= OPTIONS_COUNT)
			error(ERRNO_USAGE, NULL);
		i++;
	}
}

static void	match_long(const t_option *options, char *arg, t_flags *flags)
{
	t_option	opt;
	int			i;

	i = 0;
	while (i < OPTIONS_COUNT)
	{
		opt = options[i];
		if (ft_strequ(arg, opt.l))
		{
			*flags |= opt.f;
			break ;
		}
		i++;
	}
	if (i >= OPTIONS_COUNT)
		error(ERRNO_USAGE, NULL);
}

void		match_options(char *arg, t_flags *flags)
{
	static const t_option	options[OPTIONS_COUNT] = {
		{ .s = 'w', .l = "width", .f = FLAG_WIDTH },
		{ .s = 'h', .l = "height", .f = FLAG_HEIGHT }
	};

	if (arg[1] == '-')
		match_long(options, &arg[2], flags);
	else
		match_short(options, &arg[1], flags);
}
