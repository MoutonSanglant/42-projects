/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouton </var/spool/mail/mouton>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 22:23:27 by mouton            #+#    #+#             */
/*   Updated: 2017/09/13 22:23:27 by mouton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# include <float.h>
# include <sys/time.h>
# include <limits.h>

# include <stdio.h>

# define CL_USE_DEPRECATED_OPENCL_1_2_APIS

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif

# include <libft.h>

# define FRACTOL_OPENCL

# define CL_STR_ERROR_PLATFORM_IDS "No platform avaible"
# define CL_STR_ERROR_DEVICE_IDS "No device avaible"
# define CL_STR_ERROR_CONTEXT "Cannot create context"
# define CL_STR_ERROR_BUFFER "Cannot create buffer"
# define CL_STR_ERROR_COMMAND_QUEUE "Cannot create command queue"
# define CL_STR_ERROR_CREATE_PROGRAM "Cannot create program"
# define CL_STR_ERROR_BUILD_PROGRAM "Cannot build program"
# define CL_STR_ERROR_OPEN "Cannot open kernel file"
# define CL_STR_ERROR_CREATE_KERNEL "Cannot create kernel"
# define CL_STR_ERROR_READBUFFER "Cannot allocate cl buffer"

# define CL_STR_OPENCL_KERNEL_MANDELBROT "./resources/kernels/mandelbrot.cl"
# define CL_STR_ERROR_KERNEL "Failed to load kernel.\n"

typedef struct	s_gpgpu
{
	cl_kernel			kernel;
	cl_program			program;
	cl_device_id		*devices;
	cl_platform_id		*platforms;
	cl_command_queue	command_queue;
	cl_context			context;
	cl_mem				input_x;
	cl_mem				input_y;
	cl_mem				output;
	double				*readbuffer;
	int					output_size;
}				t_gpgpu;

typedef t_gpgpu *t_gpgpu_handler;

//void	cl_init(t_gpgpu_handler *handler, int width, int height);
t_gpgpu_handler	cl_init(int width, int height);






void	cl_close(t_gpgpu_handler handler);
//void	cl_draw();
//void	cl_draw(t_gpgpu *gpgpu, int width, int height, double zoom, int max_depth);
//void	cl_draw(t_gpgpu *gpgpu, int width, int height, double zoom, double step_x, double step_y, int max_depth);
void	cl_draw(t_gpgpu_handler handler, int width, int height, double zoom, double step_x, double step_y, int max_depth, double *data_x, double *data_y);

#endif
