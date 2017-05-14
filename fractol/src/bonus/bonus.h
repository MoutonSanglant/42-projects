/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 15:09:13 by tdefresn          #+#    #+#             */
/*   Updated: 2016/11/08 15:09:13 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# include <float.h>
# include <sys/time.h>
# include <limits.h>

# include <stdio.h>

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif

# define FRACTOL_OPENCL

# define BONUS_STR_OPENCL_KERNEL_MANDELBROT "./mandelbrot.cl"
# define BONUS_STR_ERROR_KERNEL "Failed to load kernel.\n"

typedef struct	s_gpgpu
{
	cl_kernel			kernel;
	cl_program			program;
	cl_device_id		device_id;
	cl_platform_id		platform_id;
	cl_command_queue	command_queue;
	cl_context			context;
	cl_mem				input;
	cl_mem				output;
	cl_uint				ret_num_devices;
	cl_uint				ret_num_platforms;
}				t_gpgpu;

void	cl_init(t_gpgpu *gpgpu);
void	cl_close(t_gpgpu *gpgpu);
void	cl_draw();

#endif
