#include "options.h"

#include <stdio.h>

int color(const char *arg, void *user)
{
	static int guard = 0;

	(void)user;
	if (guard++ > 0)
	{
		printf("\033[31mcolor multiple times !!\033[0m\n");
		return (0);
	}

	printf("\033[34mcolor callback: %s\033[0m\n", arg);
	return (1);
}

int test(const char *arg, void *user)
{
	(void)user;
	printf("\033[33mtest callback: %s\033[0m\n", arg);
	return (1);
}

int fallback(const char *arg, void *user)
{
	(void)user;
	printf("\033[32m'%s' fallback\033[0m\n", arg);
	return (0);
}

void TEST_options(int argc, const char **argv)
{
	const t_option	options[] = {
		{ .name = NULL, .token = NULL, .fn = &fallback, .skip = 0 },
		{ .name = "color", .token = "c", .fn = &color, .skip = 0 },
		{ .name = "test", .token = "t", .fn = &test, .skip = 1 },
		{ .token = NULL, .name = NULL }
	};

	if (parse_options(argc - 1, &argv[1], options))
		printf("\033[31mERROR USAGE !!\033[0m\n");
}

#include "math/vector.h"

void TEST_vector()
{
	t_vec2	vec2	= { -2, -1 };
	t_vec2u vec2u	= { 2, 1 };
	t_vec2f vec2f	= { -2.4f, -1.2f };
	t_vec3	vec3	= { -3, -2, -1 };
	t_vec3u vec3u	= { 3, 2, 1 };
	t_vec3f vec3f	= { -3.6f, -2.4f, -1.2f };
	t_vec4	vec4	= { -4, -3, -2, -1 };
	t_vec4u vec4u	= { 4, 3, 2, 1 };
	t_vec4f vec4f	= { -4.8f, -3.6f, -2.4f, -1.2f };

	printf("vec2  (%i, %i)\n", vec2.x, vec2.y);
	printf("vec2u (%u, %u)\n", vec2u.x, vec2u.y);
	printf("vec2f (%f, %f)\n", vec2f.x, vec2f.y);
	printf("vec3  (%i, %i, %i)\n", vec3.x, vec3.y, vec3.z);
	printf("vec3u (%u, %u, %u)\n", vec3u.x, vec3u.y, vec3u.z);
	printf("vec3f (%f, %f, %f)\n", vec3f.x, vec3f.y, vec3f.z);
	printf("vec4  (%i, %i, %i, %i)\n", vec4.x, vec4.y, vec4.z, vec4.w);
	printf("vec4u (%u, %u, %u, %u)\n", vec4u.x, vec4u.y, vec4u.z, vec4u.w);
	printf("vec4f (%f, %f, %f, %f)\n", vec4f.x, vec4f.y, vec4f.z, vec4f.w);
}

#include "math/matrix.h"

void TEST_matrix()
{
	t_mat4x4 mat4x4 = { 0 };
	t_vec3f vec3f = { 0, 0, 0 };
	t_camera camera;
	float alpha = 0.1f;

	mat4x4_translate(mat4x4, vec3f);
	mat4x4_identity(mat4x4);
	mat4x4_inverse(mat4x4, mat4x4);

	mat4x4_copy(mat4x4, mat4x4);
	mat4x4_ortho(mat4x4, &camera);

	mat4x4_translate(mat4x4, vec3f);
	mat4x4_scale(mat4x4, vec3f);

	mat4x4_rotate_x(mat4x4, alpha);
	mat4x4_rotate_y(mat4x4, alpha);
	mat4x4_rotate_z(mat4x4, alpha);

	mat4x4_transpose(mat4x4);
	mat4x4_multiply(mat4x4, mat4x4, mat4x4);
	mat4x4_apply(vec3f, mat4x4);
}

int main(int argc, const char **argv)
{
	TEST_options(argc, argv);
	TEST_vector();
	TEST_matrix();

	return (0);
}
