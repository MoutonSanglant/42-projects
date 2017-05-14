/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 19:17:05 by tdefresn          #+#    #+#             */
/*   Updated: 2017/05/14 20:27:07 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

// TODO
// replace MAX_SOURCE_SIZE

#define MAX_SOURCE_SIZE 4096
#define MEM_SIZE	1024

void	cl_init(t_gpgpu *gpgpu)
{
	int		ret;
	FILE	*fp;
	char	*source_str;
	size_t	source_size;

	if (!(fp = fopen(BONUS_STR_OPENCL_KERNEL_MANDELBROT, "r")))
	{
		fprintf(stderr, BONUS_STR_ERROR_KERNEL);
		exit(1);
	}
	source_str = (char*)malloc(MAX_SOURCE_SIZE);
	source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
	fclose(fp);

	/* Get Platform and Device Info */
	ret = clGetPlatformIDs(1, &gpgpu->platform_id, &gpgpu->ret_num_platforms);
	ret = clGetDeviceIDs(gpgpu->platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &gpgpu->device_id, &gpgpu->ret_num_devices);

	/* Create OpenCL context */
	gpgpu->context = clCreateContext(NULL, 1, &gpgpu->device_id, NULL, NULL, &ret);

	/* Create Command Queue */
	gpgpu->command_queue = clCreateCommandQueue(gpgpu->context, gpgpu->device_id, 0, &ret);

	/* Create Memory Buffer */
	gpgpu->input = clCreateBuffer(gpgpu->context, CL_MEM_READ_ONLY, MEM_SIZE * sizeof(cl_float), NULL, &ret);
	gpgpu->output = clCreateBuffer(gpgpu->context, CL_MEM_WRITE_ONLY, MEM_SIZE * sizeof(cl_float), NULL, &ret);

	/* Create Kernel Program from the source */
	gpgpu->program = clCreateProgramWithSource(gpgpu->context, 1, (const char **)&source_str,
		(const size_t *)&source_size, &ret);

	/* Build Kernel Program */
	ret = clBuildProgram(gpgpu->program, 1, &gpgpu->device_id, NULL, NULL, NULL);

	/* Create OpenCL Kernel */
	gpgpu->kernel = clCreateKernel(gpgpu->program, "mandelbrot", &ret);

}

void	cl_close(t_gpgpu *gpgpu)
{
	clFlush(gpgpu->command_queue);
	clFinish(gpgpu->command_queue);
	clReleaseKernel(gpgpu->kernel);
	clReleaseProgram(gpgpu->program);
	clReleaseMemObject(gpgpu->input);
	clReleaseMemObject(gpgpu->output);
	clReleaseCommandQueue(gpgpu->command_queue);
	clReleaseContext(gpgpu->context);
}

void	cl_draw()
{
}
