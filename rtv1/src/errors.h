/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouton </var/spool/mail/mouton>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 00:03:34 by mouton            #+#    #+#             */
/*   Updated: 2017/09/10 00:03:34 by mouton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H


typedef enum e_errno
{
	ERRNO_USAGE	= 0x1,
	ERRNO_MEMORY,
	ERRNO_OPEN,
	ERRNO_READ,
	ERRNO_MULTIPLE_WIDTH,
	ERRNO_MULTIPLE_HEIGHT,
	ERRNO_UNDEFINED
}			t_errno;

# define ERR_MEMORY "memory allocation error (%s)"
# define ERR_OPEN "cannot open file '%s'"
# define ERR_READ "read error"
# define ERR_MULTIPLE_WIDTH "multiple widths specified"
# define ERR_MULTIPLE_HEIGHT "multiple heights specified"
# define ERR_UNDEFINED "undefined error"

# define STR_USAGE "rtv1 [-w width] [-h height]"


void		error(t_errno errno, const char *description);

#endif
