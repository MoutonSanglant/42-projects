#pragma OPENCL EXTENSION cl_khr_fp64 : enable

__attribute__((reqd_work_group_size(4, 4, 0)))

kernel void fill(int width, global double *in_x, global double *in_y, global double *out)
{
	size_t i = get_global_id(0);
	size_t j = get_global_id(1);

	int x = in_x[j * width + i];
	int y = in_y[j * width + i];

	out[j * width + i] = (depth != 0) ? depth * depth * depth : 0xff000000;
}
