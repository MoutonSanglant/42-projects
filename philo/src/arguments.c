/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 23:20:52 by tdefresn          #+#    #+#             */
/*   Updated: 2016/12/11 12:59:18 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include "philo.h"

static int	parse_arg(char *arg, const t_args *arg_list, t_flags *flags)
{
	int		i;

	i = 0;
	if (arg[0] != '-')
		return (1);
	while (i < 2)
	{
		if (arg[1] != '-' && ft_strchr(arg, arg_list[i].c))
			*flags |= arg_list[i].flag;
		else if (ft_strequ(&arg[2], arg_list[i].string))
			*flags |= arg_list[i].flag;
		i++;
	}
	return (0);
}

static int	parse(int argc, char **argv, t_flags *flags, const t_args *arg_list)
{
	int		count;
	int		i;

	i = 0;
	count = 1;
	while (++i < argc)
	{
		if (parse_arg(argv[i], arg_list, flags))
			break ;
		count++;
	}
	return (count);

}

int			parse_arguments(int argc, char **argv, t_flags *flags)
{
	static const t_args	arg_list[2] =
	{
		{ .c = 'c', .string = "colors", .flag = FLAG_COLOR },
		{ .c = 't', .string = "test", .flag = FLAG_TEST }
	};

	return (parse(argc, argv, flags, arg_list));
}
