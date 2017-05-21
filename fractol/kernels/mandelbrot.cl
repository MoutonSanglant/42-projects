#pragma OPENCL EXTENSION cl_khr_fp64 : enable

/*__attribute__((reqd_work_group_size(__width__, __height__, 0)))*/
__attribute__((reqd_work_group_size(4, 4, 0)))

#define ESCAPE_RADIUS 4.0

/*kernel void mandelbrot(int width, double zoom_level, int max_depth, double step_x, double step_y, global double *out)*/
kernel void mandelbrot(int width, double zoom_level, int max_depth, double step_x, double step_y, global double *in_x, global double *in_y, global double *out)
{
	double		xy;
	double		xx;
	double		yy;
	double		x;
	double		y;
	double		cx;
	double		cy;
	size_t		i;
	size_t		j;
	int			depth;

	i = get_global_id(0);
	j = get_global_id(1);

	cx = in_x[j * width + i];
	cy = in_y[j * width + i];

	x = 0;
	y = 0;

	xx = 0;
	xy = 0;
	yy = 0;
	depth = max_depth;
	while (depth-- && xx + yy < ESCAPE_RADIUS)
	{
		xy = x * y;
		xx = x * x;
		yy = y * y;
		x = xx - yy + cx;
		y = xy + xy + cy;
	}
	out[j * width + i] = (depth != 0) ? depth * depth * depth : 0xff000000;
	/*out[cy * width + cx] = max_depth - depth;*/
	/*out[j * width + i] = cx * cy;*/
}
