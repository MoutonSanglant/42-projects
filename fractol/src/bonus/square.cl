/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.cl                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 13:30:07 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/14 13:30:07 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Simple OpenCL kernel that squares an input array.
*/

kernel void square(global float *input, global float *ouput)
{
	size_t	i;

	i = get_global_id(0);
	ouput[i] = input[i] * input[i];
}
