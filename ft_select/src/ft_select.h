/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 16:44:22 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/12 16:44:22 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <term.h>

# include <libft.h>
# include <libftprintf.h>

# define PROGRAM_NAME "ft_select"

typedef struct	s_tty
{
	int		fd;
	char	*name;
}				t_tty;

typedef struct	s_termios
{
	int				fd;
	struct termios	raw;
	struct termios	original;
}				t_termios;

typedef struct	s_select
{
	t_tty	tty;
	char	**list;
	t_list	*selected;
	int		cursor_idx;
	int		cursor_x;
	int		cursor_y;
	int		wcount;
	int		nb_elem;
	int		col_width;
	int		num_row;
	int		row_size;
}				t_select;

// signals.c
void	init_signals();
void	sig_handler(int signo);

// ft_select.c
int		ft_put(int c);

// list.c
void	clear(t_select *select);
void	refresh(t_select *select);
void	display_list(t_select *select);
void	select_element(t_select *select);
void	remove_element(t_select *select);
void	print_list (t_select *select);

// termios.c
void	*termios_if(void *(*fn)(t_termios *));
void	*termios_get(t_termios *termios);
void	*termios_raw(t_termios *termios);
void	*termios_release(t_termios *termios);
void	*termios_suspend(t_termios *termios);

// inputs.c
void	listen_input(t_select *select);

// cursor.c
void	get_cursor_position(int *x, int *y);

// move.c
void	move_prev_row();
void	move_next_row();
void	move_prev_col();
void	move_next_col();

// errors.c
void	quit(void);
void	fatal(char *format, ...);

#endif
