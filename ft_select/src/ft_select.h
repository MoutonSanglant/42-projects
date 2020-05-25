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

# include <signal.h>
# include <term.h>

# include <libft.h>
# include <libftprintf.h>

# define PROGRAM_NAME "ft_select"

# define ERR_TERM_NOT_DEFINED "Specify a terminal type with `setenv TERM ...`."
# define ERR_NO_TERM_DB "Could not access the termcap data base."
# define ERR_TERM_TYPE_UNDEFINED "Terminal type '%s' is not defined."

# define MSG_SCREEN_TOO_SMALL "Terminal screen is too small."

typedef enum	e_flags
{
	FLAG_INLINE = 0x1,
	FLAG_COLUMNS = 0x1
}				t_flags;

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
	int		nb_elem;
	int		col_width;
	int		num_row;
	int		row_size;
	int		stop;
	t_flags	flags;
}				t_select;

/*
** arguments.c
*/
int				parse_arguments(int count, char **arguments, t_select *select);

/*
** signals.c
*/
void			init_signals();
void			sig_handler(int signo);

/*
** ft_select.c
*/
int				ft_put(int c);

/*
** selection.c
*/
int				is_selected(t_select *select, char *el);

/*
** display.c
*/
void			clear(t_select *select);
void			refresh(t_select *select);
void			display_list(t_select *select, char **list);

/*
** list.c
*/
void			select_element(t_select *select);
void			remove_element(t_select *select);
int				print_element(int fd, char *el);

void			print_list (t_select *select);

/*
** termios.c
*/
void			*termios_if(void *(*fn)(t_termios *));
void			*termios_get(t_termios *termios);
void			*termios_raw(t_termios *termios);
void			*termios_release(t_termios *termios);
void			*termios_suspend(t_termios *termios);

/*
** inputs.c
*/
void			listen_input(t_select *select);

/*
** cursor.c
*/
void			push_cursor(int i);
void			get_cursor_position(int *x, int *y);

/*
** move.c
*/
void			move_prev_row();
void			move_next_row();
void			move_prev_col();
void			move_next_col();

/*
** errors.c
*/
void			quit(void);
void			fatal(char *format, ...);

#endif
