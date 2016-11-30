/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_macros.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 00:05:40 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/17 00:05:40 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TERMCAP_MACROS_H
# define TERMCAP_MACROS_H

# define TERM_SCREEN_WIDTH(put_fn) tgetnum("co")
//# define TERM_SCREEN_WIDTH(put_fn) ioctl(1, TIOCGWINSZ)
# define TERM_SCREEN_HEIGHT(put_fn) tgetnum("li")

# define TERM_CURSOR_HIDE(put_fn) tputs(tgetstr("vi", 0), 1, put_fn)
# define TERM_CURSOR_SHOW(put_fn) tputs(tgetstr("ve", 0), 1, put_fn)

# define TERM_CURSOR_UP(put_fn) tputs(tgetstr("up", 0), 1, put_fn)
# define TERM_CURSOR_DOWN(put_fn) tputs(tgetstr("do", 0), 1, put_fn)
# define TERM_CURSOR_LINE_BEGIN(put_fn) tputs(tgetstr("cr", 0), 1, put_fn)

# define TERM_STANDOUT_START(put_fn) tputs(tgetstr("so", 0), 1, put_fn)
# define TERM_STANDOUT_END(put_fn) tputs(tgetstr("se", 0), 1, put_fn)
# define TERM_UNDERLINE_START(put_fn) tputs(tgetstr("us", 0), 1, put_fn)
# define TERM_UNDERLINE_END(put_fn) tputs(tgetstr("ue", 0), 1, put_fn)

# define TERM_CLEAR_DOWN(put_fn) tputs(tgetstr("ce", 0), 1, put_fn)
# define TERM_CLEAR_LINE(put_fn) tputs(tgetstr("ce", 0), 1, put_fn)
# define TERM_DELETE_LINE(put_fn) tputs(tgetstr("dl", 0), 1, put_fn)

# define TERM_GOTO(put_fn, x, y) tputs(tgoto(tgetstr("cm", 0), x, y), 1, put_fn)

#endif
