/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 17:45:24 by tdefresn          #+#    #+#             */
/*   Updated: 2019/09/28 17:45:24 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPUTOR_H
# define COMPUTOR_H

# include <libft.h>
# include <libftprintf.h>

typedef struct s_term	t_term;

struct	s_term
{
	int degree;
	int constant;
};

int		parse_terms(char *equation, t_term *terms_list);
int		solve(t_term *terms_list, int degree);

#endif
