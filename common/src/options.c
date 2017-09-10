/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/12 18:29:50 by tdefresn          #+#    #+#             */
/*   Updated: 2017/09/11 00:30:08 by mouton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "options.h"

#define NULL 0

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

static int	find_token(const char token, const t_option *options)
{
	int		i;

	i = 0;
	while (options[i].token)
	{

		if (*options[i].token == token)
			return (i);
		i++;
	}
	return (-1);
}

static int	match_tokens(const char *arg, const char *next, const t_option *options, int *index)
{
	int		consume_next;
	int		ret;
	int		i;

	ret = 0;
	consume_next = 0;
	while (*arg)
	{
		if ((i = find_token(*arg, options)) >= 0)
		{
			consume_next |= (options[i].skip) ? 1 : 0;
			if (consume_next && !next)
				return (0);
			ret += options[i].fn((options[i].skip) ? next : NULL, options[i].user);
		}
		else
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
			if (options[i].skip && !next)
				return (0);
			*index += (options[i].skip) ? 1 : 0;
			return (options[i].fn((options[i].skip) ? next : NULL, options[i].user));
		}
		i++;
	}
	return (0);
}

int		parse_options(int count, const char **args, const t_option *options)
{
	int		i;

	i = 0;
	while (i < count)
	{
		if (args[i][0] == '-')
		{
			if (args[i][1] != '-')
			{
				if (!match_tokens(&args[i][1], args[i + 1], &options[1], &i))
					return (1);
			}
			else if (!match_name(&args[i][2], args[i + 1], &options[1], &i))
				return (1);
		}
		else
			options[0].fn(args[i], options[0].user);
		i++;
	}
	return (0);
}
