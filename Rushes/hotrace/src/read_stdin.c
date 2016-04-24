/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_stdin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 20:57:49 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/24 20:38:54 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

char	*look_for_eol(char *str)
{
	while (*str)
	{
		if (*str == '\n')
			return (str);
		str++;
	}
	return (NULL);
}

char	*get_line(char *str, char *eol, size_t *i)
{
	char		*out;
	char		*dst;
	size_t		len;

	len = eol - str;
	*i = *i + len + 1;
	out = (char *)memalloc(sizeof(char) * (len + 2));
	dst = out;
	while (str != eol)
	{
		*dst = *str;
		str++;
		dst++;
	}
	*dst++ = '\n';
	*dst = '\0';
	return (out);
}

char	*get_last_line(char *str)
{
	char		*out;
	char		*dst;
	size_t		len;

	len = str_len(str);
	out = (char *)memalloc(sizeof(char) * (len + 2));
	dst = out;
	while (*str)
	{
		*dst = *str;
		str++;
		dst++;
	}
	*dst++ = '\n';
	*dst = '\0';
	return (out);
}

char	*read_from_file(char **output, char **eol, size_t *idx)
{
	char	*tmp;
	char	buffer[BUFF_SIZE + 1];
	int		bcount;

	while ((bcount = read(0, buffer, BUFF_SIZE)) > 0)
	{
		buffer[bcount] = '\0';
		tmp = *output;
		*output = strjoin(*output, buffer);
		memdel((void **)&tmp);
		if ((*eol = look_for_eol(*output)))
			return (get_line(*output, *eol, idx));
	}
	if (bcount < 0)
		return (NULL);
	return (get_last_line(*output));
}

char	*read_stdin(void)
{
	static char		*output = NULL;
	static char		*eol = NULL;
	static size_t	idx = 0;
	char			*tmp;

	if (output)
	{
		if ((eol = look_for_eol(&output[idx])))
			return (get_line(&output[idx], eol, &idx));
		tmp = str_dup(&output[idx]);
		memdel((void **)&output);
		output = tmp;
		idx = 0;
	}
	else
	{
		output = (char *)memalloc(sizeof(char));
		output[0] = '\0';
	}
	return (read_from_file(&output, &eol, &idx));
}
