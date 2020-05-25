/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 17:43:10 by tdefresn          #+#    #+#             */
/*   Updated: 2019/09/28 18:43:28 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "computor.h"

int		main(int argc, char **argv)
{
	t_term	terms_list[3];
	int		degree;

	if (argc < 2)
	{
		ft_printf("usage: %s <equation>\n", argv[0]);
		return (1);
	}

	degree = parse_terms(argv[1], terms_list);
	return solve(terms_list, degree);
}
