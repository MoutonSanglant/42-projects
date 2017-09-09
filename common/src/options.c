/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 18:29:50 by tdefresn          #+#    #+#             */
/*   Updated: 2017/09/09 11:35:14 by mouton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "options.h"

#include <stdio.h>

static int	find_name(const char *s1, const char *s2)
{
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
			return (0);
		s1++;
		s2++;
	}
	return (1);
}

static int	match_tokens(const char *arg, const char *next, const t_option *options, int *index)
{
	int		i;
	int		ret;
	int		consume_next;

	consume_next = 0;
	ret = 0;
	i = 0;
	while (*arg)
	{
		i = 0;
		while (options[i].token)
		{
			if (*arg == *options[i].token)
			{
				consume_next += (options[i].arg) ? 1 : 0;
				ret += options[i].fn((options[i].arg) ? next : NULL);
				break;
			}
			i++;
		}
		if (!options[i].token)
			return (0);
		arg++;
	}
	*index += consume_next;
	return (ret);
}

static int	match_name(const char *arg, const char *next, const t_option *options, int *index)
{
	int		i;

	i = 0;
	while (options[i].name != NULL)
	{
		if (find_name(arg, options[i].name))
		{
			*index += (options[i].arg) ? 1 : 0;
			return (options[i].fn((options[i].arg) ? next : NULL));
		}
		i++;
	}
	return (0);
}

int		parse_options(int count, const char **args, const t_option *options, option_fn fallback)
{
	int		i;

	i = 0;
	while (i < count)
	{
		if (args[i][0] == '-')
		{
			if (args[i][1] != '-')
			{
				if (!match_tokens(&args[i][1], args[i + 1], options, &i))
					return (1);
			}
			else if (!match_name(&args[i][2], args[i + 1], options, &i))
				return (1);
		}
		else
			fallback(args[i]);
		i++;
	}
	return (0);
}
