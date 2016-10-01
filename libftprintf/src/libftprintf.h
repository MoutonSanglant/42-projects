/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 21:31:35 by tdefresn          #+#    #+#             */
/*   Updated: 2016/10/01 21:31:35 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <wchar.h>
# include <stdarg.h>

int				ft_printf(const char *restrict format, ...);
int				ft_eprintf(const char *restrict format, ...);
int				ft_dprintf(int fd, const char *restrict format, ...);
char			*ft_sprintf(const char *restrict format, ...);
char			*ft_snprintf(size_t size, const char *restrict format, ...);

int				ft_vprintf(const char *restrict format, va_list *ap);
int				ft_veprintf(const char *restrict format, va_list *ap);
int				ft_vdprintf(int fd, const char *restrict format, va_list *ap);
char			*ft_vsprintf(const char *restrict format, va_list *ap);
char			*ft_vsnprintf(size_t size, const char *restrict format,
																va_list *ap);


# ifdef FORBIDDEN

int				ft_fprintf(FILE *stream, const char *restrict format, ...);
int				ft_vfprintf(FILE *stream, const char *restrict format,
																va_list *ap);
# endif


#endif
