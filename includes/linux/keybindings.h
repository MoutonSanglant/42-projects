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

# define KEYPRESS		KeyPress
# define KEYRELEASE	KeyRelease
# define MOTIONNOTIFY	MotionNotify
# define DESTROYNOTIFY	DestroyNotify
# define KEYPRESSMASK		KeyPressMask
# define KEYRELEASEMASK	KeyReleaseMask
# define POINTERMOTIONMASK	PointerMotionMask

# define KEY_ESCAPE	65307
# define KEY_STAR		30
# define KEY_NUMPAD_MORE	65451
# define KEY_NUMPAD_LESS	65453
# define KEY_NUMPAD_STAR	65450
# define KEY_NUMPAD_SLASH	65455
# define KEY_NUMPAD_DOT	0000000
# define KEY_0		224
# define KEY_1		38
# define KEY_2		233
# define KEY_3		34
# define KEY_4		39
# define KEY_5		40
# define KEY_6		45
# define KEY_7		232
# define KEY_8		95
# define KEY_9		231
# define KEY_A		113
# define KEY_B		98
# define KEY_C		00000000
# define KEY_D		100
# define KEY_E		101
# define KEY_F		102
# define KEY_G		103
# define KEY_H		104
# define KEY_I		105
# define KEY_J		00000000
# define KEY_K		00000000
# define KEY_L		108
# define KEY_M		00000000
# define KEY_N		00000000
# define KEY_O		111
# define KEY_P		112
# define KEY_Q		97
# define KEY_R		114
# define KEY_S		115
# define KEY_T		00000000
# define KEY_U		00000000
# define KEY_V		00000000
# define KEY_W		122
# define KEY_X		00000000
# define KEY_Y		00000000
# define KEY_Z		119
# define KEY_MORE	00000000
# define KEY_LESS	00000000
# define KEY_SLASH	00000000
# define KEY_DOT	00000000
# define KEY_TAB	65289
# define KEY_LEFT	65361
# define KEY_RIGHT	65363
# define KEY_UP	65362
# define KEY_DOWN	65364
# define KEY_PAGE_UP	65365
# define KEY_PAGE_DOWN	65366

# define KEY_LEFT_CTRL		25600
# define KEY_LEFT_SHIFT	25700
# define KEY_RIGHT_SHIFT	25800
# define KEY_RIGHT_CTRL	26900

# define MOUSE_CLICK_LEFT	1
# define MOUSE_CLICK_RIGHT	2
# define MOUSE_SCROLL_DOWN	4
# define MOUSE_SCROLL_UP	5

typedef enum	e_key_mod
{
	KEY_MODIFIER_SHIFT = 0x1,
	KEY_MODIFIER_CTRL = 0x2
}				t_key_mod;

#endif
