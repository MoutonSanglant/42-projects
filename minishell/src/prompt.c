/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/04 19:32:16 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/05 21:22:12 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_prompt(t_sh_datas *sh_datas)
{
	char		*cwd;
	char		buf[1024];

	cwd = getcwd(buf, 1024);
	cwd = ft_strjoin(cwd, "\x1B[0m $> ");
	sh_datas->prompt = ft_strjoin("\x1B[32m", cwd);
	ft_strdel(&cwd);
}
