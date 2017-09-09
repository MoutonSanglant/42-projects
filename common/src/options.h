/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouton </var/spool/mail/mouton>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 21:47:06 by mouton            #+#    #+#             */
/*   Updated: 2017/09/08 21:47:06 by mouton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIONS_H
# define OPTIONS_H

typedef		int (*option_fn)(char const *next_arg, void *user);

typedef struct	s_option
{
	char const	*name;
	char const	*token;
	option_fn	fn;
	int const	skip;
	void		*user;
}				t_option;

int		parse_options(int count, const char **args, const t_option *options);

#endif
