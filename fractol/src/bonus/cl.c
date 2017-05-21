/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 19:17:05 by tdefresn          #+#    #+#             */
/*   Updated: 2017/05/21 18:47:53 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

// TODO
// replace MAX_SOURCE_SIZE

#define MAX_SOURCE_SIZE 4096

void	cl_init(t_gpgpu *gpgpu, int width, int height)
{
	int		ret;
	FILE	*fp;
	char	*source_str;
	size_t	source_size;
	int		mem_size;

	char	attr[1024];
	//sprintf(attr, "__attribute__((reqd_work_group_size(%i, %i, 0)))   \n", width, height);

	mem_size = width * height;
	gpgpu->output_size = mem_size;
	printf("memory size: %i\n", mem_size);
	if (!(fp = fopen(BONUS_STR_OPENCL_KERNEL_MANDELBROT, "r")))
	{
		fprintf(stderr, BONUS_STR_ERROR_OPEN);
		fprintf(stderr, "file: %s\n", BONUS_STR_OPENCL_KERNEL_MANDELBROT);
		exit(1);
	}
	source_str = ft_strnew(MAX_SOURCE_SIZE);
	ft_memcpy(source_str, attr, ft_strlen(attr));
	source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
	fclose(fp);

	char *a = ft_strstr(source_str, "__width__");
	ft_memcpy(a, "         ", 9);
	char *b = ft_itoa(width);
	ft_memcpy(a, b, ft_strlen(b));

	a = ft_strstr(source_str, "__height__");
	ft_memcpy(a, "          ", 10);
	b = ft_itoa(height);
	ft_memcpy(a, b, ft_strlen(b));
	printf("%s\n", source_str);

	/* Get Platform and Device Info */
	ret = clGetPlatformIDs(1, &gpgpu->platform_id, &gpgpu->ret_num_platforms);
	ret = clGetDeviceIDs(gpgpu->platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &gpgpu->device_id, &gpgpu->ret_num_devices);

	/* Create OpenCL context */
	gpgpu->context = clCreateContext(NULL, 1, &gpgpu->device_id, NULL, NULL, &ret);
	if (ret != CL_SUCCESS)
	{
		printf ("error: Cannot create context\n");
		exit (1);
	}

	/* Create Command Queue */
	gpgpu->command_queue = clCreateCommandQueue(gpgpu->context, gpgpu->device_id, 0, &ret);
	if (ret != CL_SUCCESS)
	{
		printf ("error: Cannot create command queue\n");
		exit (1);
	}

	/* Create Memory Buffer */
	gpgpu->input_x = clCreateBuffer(gpgpu->context, CL_MEM_READ_ONLY, mem_size * sizeof(cl_double) * 2, NULL, &ret);
	gpgpu->input_y = clCreateBuffer(gpgpu->context, CL_MEM_READ_ONLY, mem_size * sizeof(cl_double) * 2, NULL, &ret);
	gpgpu->output = clCreateBuffer(gpgpu->context, CL_MEM_WRITE_ONLY, mem_size * sizeof(cl_double), NULL, &ret);
	if (ret != CL_SUCCESS)
	{
		printf ("error: Cannot create buffer\n");
		exit (1);
	}

	/* Create Kernel Program from the source */
	gpgpu->program = clCreateProgramWithSource(gpgpu->context, 1, (const char **)&source_str,
		(const size_t *)&source_size, &ret);
	if (ret != CL_SUCCESS)
	{
		printf ("error: Cannot create kernel program\n");
		exit (1);
	}

	/* Build Kernel Program */
	ret = clBuildProgram(gpgpu->program, 1, &gpgpu->device_id, NULL, NULL, NULL);
	if (ret != CL_SUCCESS)
	{
		printf("CL_INVALID_PROGRAM: %i\n", CL_INVALID_PROGRAM);
		printf("CL_INVALID_VALUE: %i\n", CL_INVALID_VALUE);
		printf("CL_INVALID_DEVICE: %i\n", CL_INVALID_DEVICE);
		printf("CL_INVALID_BINARY: %i\n", CL_INVALID_BINARY);
		printf("CL_INVALID_BUILD_OPTIONS: %i\n", CL_INVALID_BUILD_OPTIONS);
		printf("CL_INVALID_OPERATION: %i\n", CL_INVALID_OPERATION);
		printf("CL_COMPILER_NOT_AVAILABLE: %i\n", CL_COMPILER_NOT_AVAILABLE);
		printf("CL_BUILD_PROGRAM_FAILURE: %i\n", CL_BUILD_PROGRAM_FAILURE);
		printf("CL_OUT_OF_HOST_MEMORY: %i\n", CL_OUT_OF_HOST_MEMORY);
		printf ("error: Cannot build program: %i\n", ret);
		exit (1);
	}

	/* Create OpenCL Kernel */
	gpgpu->kernel = clCreateKernel(gpgpu->program, "mandelbrot", &ret);
	if (ret != CL_SUCCESS)
	{
		printf("CL_INVALID_PROGRAM: %i\n", CL_INVALID_PROGRAM);
		printf("CL_INVALID_PROGRAM_EXECUTABLE: %i\n", CL_INVALID_PROGRAM_EXECUTABLE);
		printf("CL_INVALID_KERNEL_NAME: %i\n", CL_INVALID_KERNEL_NAME);
		printf("CL_INVALID_KERNEL_DEFINITION: %i\n", CL_INVALID_KERNEL_DEFINITION);
		printf("CL_INVALID_VALUE: %i\n", CL_INVALID_VALUE);
		printf("CL_OUT_OF_HOST_MEMORY: %i\n", CL_OUT_OF_HOST_MEMORY);
		printf ("error: Cannot create kernel: %i\n", ret);
		exit (1);
	}

	gpgpu->buffer = ft_memalloc(sizeof(double) * mem_size);
	if (!gpgpu->buffer)
	{
		printf ("error: Cannot allocate buffer\n");
		exit (1);
	}

	ft_strdel(&source_str);
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
	ft_memdel((void **)&gpgpu->buffer);
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
	if (clGetKernelWorkGroupInfo(kernel, gpgpu->device_id, CL_KERNEL_COMPILE_WORK_GROUP_SIZE, sizeof(locals), &locals, NULL) != CL_SUCCESS)
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
	clEnqueueReadBuffer(gpgpu->command_queue, gpgpu->output, CL_TRUE, 0, sizeof(double) * gpgpu->output_size, gpgpu->buffer, 0, NULL, NULL);
}
