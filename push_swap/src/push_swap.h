/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 21:04:39 by tdefresn          #+#    #+#             */
/*   Updated: 2016/05/07 21:04:39 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <libft.h>

typedef struct	s_swap
{
	t_stack		*a;
	t_stack		*b;
}				t_swap;

void		print_swap(t_swap *s);

void		basic_sort(t_swap *s);
char		*store_unsorted(t_swap *swap, char *str, int min, int max);
char		*insert(t_swap *swap, char *str);

char		*pa (t_swap *s);
char		*pb (t_swap *s);

char		*sa (t_swap *s);
char		*sb (t_swap *s);
char		*ss (t_swap *s);

char		*ra (t_swap *s);
char		*rb (t_swap *s);
char		*rr (t_swap *s);

char		*rra (t_swap *s);
char		*rrb (t_swap *s);
char		*rrr (t_swap *s);

void		error();

#endif
