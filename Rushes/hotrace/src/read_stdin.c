/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_stdin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 20:57:49 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/22 22:53:15 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

int		look_for_eol(char *str)
{
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

char	*read_stdin()
{
	char	*output;
	char	buffer[BUFF_SIZE + 1];
	int		bcount;

	output = (char *)memalloc(1);
	output[0] = '\0';
	while ((bcount = read(0, buffer, BUFF_SIZE)) > 0)
	{
		buffer[bcount] = '\0';
		output = strjoin(output, buffer);
		if (look_for_eol(buffer))
			return (output);
	}
	if (bcount < 0)
		putstr("error\n");
	return (NULL);
}
