/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unescape.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/10 16:11:01 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/25 16:46:40 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static void		unescape_string(char *dst, char *src)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i] != '\\')
			dst[j++] = src[i];
		i++;
	}
}

static int		unescape_string_list(char **input_blocks)
{
	char	*string;
	int		count;
	int		i;
	int		j;

	i = 0;
	while (input_blocks[i])
	{
		j = 0;
		count = 0;
		while (input_blocks[i][j])
			if (input_blocks[i][j++] == '\\')
				count++;
		string = ft_strnew(ft_strlen(input_blocks[i]) - count);
		unescape_string(string, input_blocks[i]);
		ft_strdel(&input_blocks[i]);
		input_blocks[i] = string;
		i++;
	}
	return (i);
}

char			**unescape(char **input_blocks)
{
	char	**out;
	int		i;

	i = unescape_string_list(input_blocks);
	out = (char **)ft_memalloc(sizeof(char *) * (i + 1));
	while (input_blocks[i])
		ft_strdel(&input_blocks[i++]);
	i = 0;
	while (input_blocks[i])
	{
		out[i] = input_blocks[i];
		i++;
	}
	out[i] = NULL;
	ft_memdel((void **)&input_blocks);
	return (out);
}
