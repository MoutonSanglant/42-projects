/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 17:56:03 by tdefresn          #+#    #+#             */
/*   Updated: 2019/09/28 18:45:50 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"

int		solve(t_term *terms_list, int degree) // Use a list of struct instead
{
	(void)terms_list;
	(void)degree;

	// X: indeterminate
	//
	// in "5*X + 4", "+4" is called a constant term
	// "x^0 = 1" so "4" is in fact "4 * x^0"
	// degree = 0
	// constant = 4

	ft_printf("Solution(s):\n");
	ft_printf("%i\n", 0);
	// for each ...
	return 0;
}
