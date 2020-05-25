/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 18:00:22 by tdefresn          #+#    #+#             */
/*   Updated: 2019/09/29 21:22:13 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"

static int		parse_term(char *str, t_term *term)
{
	char *cursor;

	cursor = str;

	ft_bzero(term, sizeof(t_term));

	term->constant = ft_atoi(cursor);

	cursor = ft_strchr(cursor, '^');
	cursor++;

	term->degree = ft_atoi(cursor);
	
	cursor = ft_strchr(cursor, '+');
	cursor++;

	// Corectly formated:
	// c * X^d
	//
	


	// First, the constant,
	// Then 

	// Look for "X" ...
	// Then look for sign
	// If sign breaks term (+/-)
	// Exit function
	// Else
	// Continue

	return cursor - str;
}

int				parse_terms(char *equation, t_term *terms_list)
{
	t_term	current_term;
	int		largest_degree;
	size_t	i;
	size_t	len;

	largest_degree = 0;
	i = 0;
	len = ft_strlen(equation);

	while(i < len)
	{
		i += parse_term(&equation[i], &current_term);
		terms_list->constant = current_term.constant;
		terms_list->degree = current_term.degree;
		terms_list++;
		largest_degree = (current_term.degree > largest_degree) ? current_term.degree : largest_degree;
	}

	ft_printf("Polynomial degree: %i\n", largest_degree);
	return largest_degree;
}
