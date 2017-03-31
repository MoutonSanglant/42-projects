/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:36:56 by tdefresn          #+#    #+#             */
/*   Updated: 2017/03/29 19:34:45 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	NOTE
**	This is not the standard "ft_putnbr" since
**	it returns a value when it shouldn't.
**	===================================
**	void	ft_putnbr(int n)
*/

static void		printnbr(int n, int *bcount)
{
	char	c;

	if (n >= 10)
		printnbr(n / 10, bcount);
	c = (n % 10) + '0';
	write(1, &c, 1);
	(*bcount)++;
}

static void		print_min(int64_t n, int *bcount)
{
	char	c;

	n = -n;
	if (n >= 10)
		printnbr(n / 10, bcount);
	c = (n % 10) + '0';
	write(1, &c, 1);
	(*bcount)++;
}

void			ft_putnbr(int n)
{
	int bcount;

	bcount = 0;
	if (n < 0)
	{
		write(1, "-", 1);
		if (n == INT_MIN)
			print_min((int64_t)n, &bcount);
		else
			printnbr(-n, &bcount);
		return ;
	}
	printnbr(n, &bcount);
}
