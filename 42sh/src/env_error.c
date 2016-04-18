/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/08 15:59:48 by tdefresn          #+#    #+#             */
/*   Updated: 2016/04/08 16:14:26 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		env_error(t_env_error err)
{
	if (err == ENVERR_VERB)
		ft_printf("env: verbose mode not implemented\n");
	if (err == ENVERR_PATH)
		ft_printf("env: alternate path not implemented\n");
	if (err == ENVERR_SPLIT)
		ft_printf("env: split not implemented\n");
	if (err == ENVERR_UNSET)
		ft_printf("env: unset not implemented\n");
	return (1);
}
