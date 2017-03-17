/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 18:18:01 by tdefresn          #+#    #+#             */
/*   Updated: 2017/03/17 20:55:48 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		main(int argc, char **argv)
{
	if (argc < 1)
		return (1);
	(void)argv[0];
	if (!glfwInit())
		ft_printf("Cannot initialize GLFW\n");
	return (0);
}
