/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keybindings.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 15:32:11 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/08 15:32:11 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYBINDINGS_H
# define KEYBINDINGS_H

# define KEYPRESS		2
# define KEYRELEASE	3
# define MOTIONNOTIFY	6
# define DESTROYNOTIFY	17
# define KEYPRESSMASK		(1L<<0)
# define KEYRELEASEMASK	(1L<<1)
# define POINTERMOTIONMASK	(1L<<6)

# define KEY_ESCAPE	53
# define KEY_STAR		30
# define KEY_NUMPAD_MORE	69
# define KEY_NUMPAD_LESS	78
# define KEY_NUMPAD_STAR	67
# define KEY_NUMPAD_SLASH	75
# define KEY_NUMPAD_DOT	65
# define KEY_0		29
# define KEY_1		18
# define KEY_2		19
# define KEY_3		20
# define KEY_4		21
# define KEY_5		23
# define KEY_6		22
# define KEY_7		26
# define KEY_8		28
# define KEY_9		25
# define KEY_A		0
# define KEY_B		11
# define KEY_C		00000000
# define KEY_D		2
# define KEY_E		14
# define KEY_F		3
# define KEY_G		5
# define KEY_H		4
# define KEY_I		34
# define KEY_J		38
# define KEY_K		00000000
# define KEY_L		37
# define KEY_M		00000000
# define KEY_N		45
# define KEY_O		31
# define KEY_P		35
# define KEY_Q		12
# define KEY_R		15
# define KEY_S		1
# define KEY_T		00000000
# define KEY_U		00000000
# define KEY_V		00000000
# define KEY_W		13
# define KEY_X		00000000
# define KEY_Y		00000000
# define KEY_Z		6
# define KEY_SLASH	44
# define KEY_DOT	47
# define KEY_MORE	24
# define KEY_LESS	27
# define KEY_TAB	48
# define KEY_LEFT	123
# define KEY_RIGHT	124
# define KEY_UP	126
# define KEY_DOWN	125
# define KEY_PAGE_UP		116
# define KEY_PAGE_DOWN		121

# define KEY_LEFT_CTRL		256
# define KEY_LEFT_SHIFT	257
# define KEY_RIGHT_SHIFT	258
# define KEY_RIGHT_CTRL	269

# define MOUSE_CLICK_LEFT	1
# define MOUSE_CLICK_RIGHT	2
# define MOUSE_SCROLL_DOWN	4
# define MOUSE_SCROLL_UP	5

#endif
