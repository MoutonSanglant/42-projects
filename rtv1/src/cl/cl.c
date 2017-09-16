/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 19:17:05 by tdefresn          #+#    #+#             */
/*   Updated: 2017/09/17 00:35:41 by mouton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl.h"

// TODO
// replace MAX_SOURCE_SIZE
#define MAX_SOURCE_SIZE 4096

void cl_check(const char *msg, cl_int errcode)
{
	if (errcode != CL_SUCCESS)
	{
		printf ("Error %i: %s\n", errcode, msg);
		exit(1);
	}
}

t_gpgpu *cl_memalloc(int mem_size)
{
	t_gpgpu *gpgpu;

	gpgpu = (t_gpgpu *)ft_memalloc(sizeof(t_gpgpu));
	gpgpu->output_size = mem_size;
	printf("memory size: %i\n", mem_size);

	return (gpgpu);
}

/*
** Find best OpenCL device
*/
void	cl_get_device(t_gpgpu *gpgpu)
{
	cl_uint	platforms_count;
	cl_uint	devices_count;
	cl_uint i;
	cl_int errcode;

	i = 0;
	clGetPlatformIDs(5, NULL, &platforms_count);
	gpgpu->platforms = (cl_platform_id *)malloc(sizeof(cl_platform_id) * platforms_count);
	errcode = clGetPlatformIDs(platforms_count, gpgpu->platforms, NULL);
	cl_check(CL_STR_ERROR_PLATFORM_IDS, errcode);
	while (i < platforms_count)
	{
		clGetDeviceIDs(gpgpu->platforms[i], CL_DEVICE_TYPE_GPU, 0, NULL, &devices_count);
		gpgpu->devices = (cl_device_id *)malloc(sizeof(cl_device_id) * devices_count);
		errcode = clGetDeviceIDs(gpgpu->platforms[i], CL_DEVICE_TYPE_GPU, devices_count, gpgpu->devices, NULL);
		cl_check(CL_STR_ERROR_DEVICE_IDS, errcode);
		if (1)
			break;
		i++;
	}
}

/*
** Create an OpenCL context
*/
cl_context cl_create_context(const cl_device_id *devices)
{
	cl_context context;
	cl_int errcode;

	//context = clCreateContext(NULL, 1, &gpgpu->device_id, NULL, NULL, &err_code);
	context = clCreateContext(NULL, 1, devices, NULL, NULL, &errcode);
	cl_check (CL_STR_ERROR_CONTEXT, errcode);
	return (context);
}

/*
** Create Input/Output Buffers
*/
void cl_create_buffers(t_gpgpu *gpgpu, cl_context context, size_t size)
{
	cl_int	errcode;

	gpgpu->input_x = clCreateBuffer(context, CL_MEM_READ_ONLY, size * 2, NULL, &errcode);
	cl_check(CL_STR_ERROR_BUFFER, errcode);
	gpgpu->input_y = clCreateBuffer(context, CL_MEM_READ_ONLY, size * 2, NULL, &errcode);
	cl_check(CL_STR_ERROR_BUFFER, errcode);
	gpgpu->output = clCreateBuffer(context, CL_MEM_WRITE_ONLY, size, NULL, &errcode);
	cl_check(CL_STR_ERROR_BUFFER, errcode);
}

/*
** - Read source file into text strings
** - Create a program object for context from text strings
** - Build (compile & link) a program executable
** - Create OpenCl kernel
*/
void cl_kernel_from_file(t_gpgpu *gpgpu, const char *filename)
{
	size_t	lengths[1];
	char	*strings[1];
	FILE	*file;
	cl_int	errcode;

	if (!(file = fopen(filename, "r")))
		cl_check(CL_STR_ERROR_OPEN, -1);
	*strings = ft_strnew(MAX_SOURCE_SIZE);
	//char	attr[1024];
	//ft_memcpy(strings, attr, ft_strlen(attr));
	lengths[0] = fread(*strings, 1, MAX_SOURCE_SIZE, file);
	printf("Source is %zu bytes long.\n%s\n", *lengths, *strings);
	gpgpu->program = clCreateProgramWithSource(gpgpu->context, 1, (const char **)strings,
		(const size_t *)lengths, &errcode);
	cl_check(CL_STR_ERROR_CREATE_PROGRAM, errcode);
	errcode = clBuildProgram(gpgpu->program, 1, gpgpu->devices, NULL, NULL, NULL);
	cl_check(CL_STR_ERROR_BUILD_PROGRAM, errcode);
	gpgpu->kernel = clCreateKernel(gpgpu->program, "mandelbrot", &errcode);
	cl_check(CL_STR_ERROR_CREATE_KERNEL, errcode);
	ft_strdel(strings);
	fclose(file);
}

t_gpgpu	*cl_init(int width, int height)
{
	t_gpgpu *gpgpu;
	cl_int	errcode;
	int		mem_size;

	mem_size = width * height;
	gpgpu = cl_memalloc(mem_size);
	cl_get_device(gpgpu);
	gpgpu->context = cl_create_context(gpgpu->devices);
	gpgpu->command_queue = clCreateCommandQueue(gpgpu->context, *gpgpu->devices, 0, &errcode);
	cl_check(CL_STR_ERROR_COMMAND_QUEUE, errcode);
	cl_create_buffers(gpgpu, gpgpu->context, mem_size * sizeof(cl_double));
	cl_kernel_from_file(gpgpu, CL_STR_OPENCL_KERNEL_MANDELBROT);

	if (!(gpgpu->readbuffer = (double *)ft_memalloc(sizeof(double) * mem_size)))
		cl_check(CL_STR_ERROR_BUFFER, -1);

	//free(gpgpu->devices);
	free(gpgpu->platforms);

	return(gpgpu);
}

void	cl_close(t_gpgpu *gpgpu)
{
	clFlush(gpgpu->command_queue);
	clFinish(gpgpu->command_queue);
	clReleaseKernel(gpgpu->kernel);
	clReleaseProgram(gpgpu->program);
	clReleaseMemObject(gpgpu->input_x);
	clReleaseMemObject(gpgpu->input_y);
	clReleaseMemObject(gpgpu->output);
	clReleaseCommandQueue(gpgpu->command_queue);
	clReleaseContext(gpgpu->context);
	ft_memdel((void **)&gpgpu->readbuffer);
	ft_memdel((void **)&gpgpu);
}

void	cl_draw(t_gpgpu *gpgpu, int width, int height, double zoom, double step_x, double step_y, int max_depth, double *data_x, double *data_y)
//void	cl_draw(t_gpgpu *gpgpu, int width, int height, double zoom, double min_x, double max_x, double min_y, double max_y, double step_x, double step_y, int max_depth)
{
	cl_kernel kernel = gpgpu->kernel;
	size_t	local;
	size_t	global;

	int err;

	if (clEnqueueWriteBuffer(gpgpu->command_queue, gpgpu->input_x, CL_TRUE, 0, width * height * sizeof(double), data_x, 0, NULL, NULL))
	{
		printf ("error 3\n");
		exit (1);
	}
	if (clEnqueueWriteBuffer(gpgpu->command_queue, gpgpu->input_y, CL_TRUE, 0, width * height * sizeof(double), data_y, 0, NULL, NULL))
	{
		printf ("error 3\n");
		exit (1);
	}

	/* Set OpenCL Kernel Parameters */
	err = clSetKernelArg(gpgpu->kernel, 0, sizeof(cl_int), &width);
	if (err != CL_SUCCESS)
	{
		printf("CL_INVALID_KERNEL: %i\n", CL_INVALID_KERNEL);
		printf("CL_INVALID_ARG_INDEX: %i\n", CL_INVALID_ARG_INDEX);
		printf("CL_INVALID_ARG_VALUE: %i\n", CL_INVALID_ARG_VALUE);
		printf("CL_INVALID_MEM_OBJECT: %i\n", CL_INVALID_MEM_OBJECT);
		printf("CL_INVALID_SAMPLER: %i\n", CL_INVALID_SAMPLER);
		printf("CL_INVALID_ARG_SIZE: %i\n", CL_INVALID_ARG_SIZE);
		printf ("error A: %i\n", err);
		exit (1);
	}
	err = clSetKernelArg(gpgpu->kernel, 1, sizeof(cl_double), &zoom);
	if (err != CL_SUCCESS)
	{
		printf ("error B\n");
		exit (1);
	}
	err = clSetKernelArg(gpgpu->kernel, 2, sizeof(cl_int), &max_depth);
	if (err != CL_SUCCESS)
	{
		printf ("error C\n");
		exit (1);
	}
	err = clSetKernelArg(gpgpu->kernel, 3, sizeof(cl_double), &step_x);
	err = clSetKernelArg(gpgpu->kernel, 4, sizeof(cl_double), &step_y);
	err = clSetKernelArg(gpgpu->kernel, 5, sizeof(cl_mem), &gpgpu->input_x);
	err = clSetKernelArg(gpgpu->kernel, 6, sizeof(cl_mem), &gpgpu->input_y);
	err = clSetKernelArg(gpgpu->kernel, 7, sizeof(cl_mem), &gpgpu->output);

	if (err != CL_SUCCESS)
	{
		printf("CL_INVALID_KERNEL: %i\n", CL_INVALID_KERNEL);
		printf("CL_INVALID_ARG_INDEX: %i\n", CL_INVALID_ARG_INDEX);
		printf("CL_INVALID_ARG_VALUE: %i\n", CL_INVALID_ARG_VALUE);
		printf("CL_INVALID_MEM_OBJECT: %i\n", CL_INVALID_MEM_OBJECT);
		printf("CL_INVALID_SAMPLER: %i\n", CL_INVALID_SAMPLER);
		printf("CL_INVALID_ARG_SIZE: %i\n", CL_INVALID_ARG_SIZE);
		printf ("error D: %i\n", err);
		exit (1);
	}

	//ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&mem_in);
	//ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&mem_out);

	//if (clGetKernelWorkGroupInfo(kernel, gpgpu->device_id, CL_KERNEL_WORK_GROUP_SIZE, sizeof(local), &local, NULL) != CL_SUCCESS)
	(void)local;
	size_t locals[3];
	if (clGetKernelWorkGroupInfo(kernel, *gpgpu->devices, CL_KERNEL_COMPILE_WORK_GROUP_SIZE, sizeof(locals), &locals, NULL) != CL_SUCCESS)
	{
		printf ("error 2\n");
		exit (1);
	}

	// local work size multiple de 32
	// global work size plus grand que necessaire

	//locals[0] = 32;
	//locals[1] = 32;
	size_t global_work_size[] = { width, height, 0 };

	printf ("CL_DEVICE_MAX_WORK_GROUP_SIZE: %i\n", CL_DEVICE_MAX_WORK_GROUP_SIZE);
	printf ("CL_DEVICE_MAX_WORK_ITEM_SIZES: %i\n", CL_DEVICE_MAX_WORK_ITEM_SIZES);
	if (locals[0] * locals[1] > CL_DEVICE_MAX_WORK_GROUP_SIZE)
	{
		printf("error max work group size %zu > %i !!!\n", locals[0] * locals[1], CL_DEVICE_MAX_WORK_GROUP_SIZE);
		exit (1);
	}
	if (locals[0] > CL_DEVICE_MAX_WORK_ITEM_SIZES)
	{
		printf("error max work item size %zu > %i !!!\n", locals[0], CL_DEVICE_MAX_WORK_ITEM_SIZES);
		exit (1);
	}
	if (locals[1] > CL_DEVICE_MAX_WORK_ITEM_SIZES)
	{
		printf("error max work item size %zu > %i !!!\n", locals[1], CL_DEVICE_MAX_WORK_ITEM_SIZES);
		exit (1);
	}

	global = locals[0] * locals[1];
	printf("global_work_size: %zu\n", global);
	printf("global_work_size: (%zu, %zu)\n", global_work_size[0], global_work_size[1]);
	printf("local_work_size: (%zu, %zu, %zu)\n", locals[0], locals[1], locals[2]);

	/* Execute OpenCL Kernel */
	if ((err = clEnqueueNDRangeKernel(gpgpu->command_queue, kernel, 2, NULL, global_work_size, locals, 0, NULL, NULL)) != CL_SUCCESS)
	{
		printf ("error: %i\n", err);
		exit (1);
	}

	/* Semaphore */
	clFinish(gpgpu->command_queue);

	/* Copy results from the memory buffer */
	clEnqueueReadBuffer(gpgpu->command_queue, gpgpu->output, CL_TRUE, 0, sizeof(double) * gpgpu->output_size, gpgpu->readbuffer, 0, NULL, NULL);
}
