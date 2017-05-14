#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
# include <OpenCL/opencl.h>
#else
# include <CL/cl.h>
#endif

//#define MEM_SIZE (128)
#define MEM_SIZE (1024)
#define MAX_SOURCE_SIZE (0x100000)

int main()
{
	cl_device_id device_id = NULL;
	cl_context context = NULL;
	cl_command_queue command_queue = NULL;
	cl_mem mem_in = NULL;
	cl_mem mem_out = NULL;
	cl_program program = NULL;
	cl_kernel kernel = NULL;
	cl_platform_id platform_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;
	cl_int ret;

	FILE *fp;
	char fileName[] = "./square.cl";
	char *source_str;
	size_t source_size;

	float data[MEM_SIZE];

	for (int i = 0; i < MEM_SIZE; i++)
		data[i] = (float)i;

	/* Load the source code containing the kernel*/
	fp = fopen(fileName, "r");
	if (!fp)
	{
		fprintf(stderr, "Failed to load kernel.\n");
		exit(1);
	}
	source_str = (char*)malloc(MAX_SOURCE_SIZE);
	source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
	fclose(fp);

	/* Get Platform and Device Info */
	ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);

	/* Create OpenCL context */
	context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);

	/* Create Command Queue */
	command_queue = clCreateCommandQueue(context, device_id, 0, &ret);

	/* Create Memory Buffer */
	mem_in = clCreateBuffer(context, CL_MEM_READ_ONLY,MEM_SIZE * sizeof(cl_float), NULL, &ret);
	mem_out = clCreateBuffer(context, CL_MEM_WRITE_ONLY,MEM_SIZE * sizeof(cl_float), NULL, &ret);

	/* Create Kernel Program from the source */
	program = clCreateProgramWithSource(context, 1, (const char **)&source_str,
		(const size_t *)&source_size, &ret);

	/* Build Kernel Program */
	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

	/* Create OpenCL Kernel */
	kernel = clCreateKernel(program, "square", &ret);

	size_t	local;
	size_t	global;

	int err;
	int count = MEM_SIZE;

	float results[MEM_SIZE];

	if (clEnqueueWriteBuffer(command_queue, mem_in, CL_TRUE, 0, MEM_SIZE * sizeof(float), data, 0, NULL, NULL))
	{
		printf ("error 3\n");
		exit (1);
	}

	/* Set OpenCL Kernel Parameters */
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&mem_in);
	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&mem_out);

	if (clGetKernelWorkGroupInfo(kernel, device_id, CL_KERNEL_WORK_GROUP_SIZE, sizeof(local), &local, NULL) != CL_SUCCESS)
	{
		printf ("error 2\n");
		exit (1);
	}

	global = count;
	printf("local: %i\nglobal: %i\n", local, global);

	/* Execute OpenCL Kernel */
	if ((err = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global, &local, 0, NULL, NULL)) != CL_SUCCESS)
	{
		printf ("error: %i\n", err);
		exit (1);
	}

	/* Semaphore */
	clFinish(command_queue);

	/* Copy results from the memory buffer */
	clEnqueueReadBuffer(command_queue, mem_out, CL_TRUE, 0, sizeof(float) * MEM_SIZE, results, 0, NULL, NULL);

	/* Display Result */
	for (int i = 0; i < 10; i++)
		printf("%i: %f\n", i, results[i]);

	/* Finalization */
	ret = clFlush(command_queue);
	ret = clFinish(command_queue);
	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);
	ret = clReleaseMemObject(mem_in);
	ret = clReleaseMemObject(mem_out);
	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);

	free(source_str);

	return 0;
}
