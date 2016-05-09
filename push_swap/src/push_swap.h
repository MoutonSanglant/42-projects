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

void		sa (t_swap *s);
void		sb (t_swap *s);
void		ss (t_swap *s);
void		error();

#endif
