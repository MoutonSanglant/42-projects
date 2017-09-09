/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 18:18:01 by tdefresn          #+#    #+#             */
/*   Updated: 2017/09/10 00:31:33 by mouton           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

#include "glfw/glfw.h"

static const struct
{
	float	x;
	float	y;
}			vertices[3] =
{
	{ -0.6f, -0.4f },
	{ 0.6f, -0.4f },
	{ 0.f, 0.6f }
};

static const struct
{
	float	r;
	float	g;
	float	b;
}	col[3] =
{
	{ 1.f, 0.f, 0.f },
	{ 0.f, 1.f, 0.f },
	{ 0.f, 0.f, 1.f }
};


static const char * vertex_shader_text =
"#version 330\n"
"layout (location = 0) in vec2 point;\n"
"out vec3 color;\n"
"out vec2 pos;\n"
"uniform mat4 MVP;\n"
"uniform vec3 vCol;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(point, 0.0, 1.0);\n"
"    color = vCol;\n"
"	if (point.x < -0.1)\n"
"	color = vec3(1, 0, 0);\n"
"	if (point.x > 0.1)\n"
"	color = vec3(1, 0, 1);\n"
"	if (point.y > 0.1 )\n"
"	color = vec3(0, 1, 1);\n"
"	pos = point;"
"}\n";

static const char* fragment_shader_text =
"#version 330 core\n"
"out vec4 outColor;\n"
"in vec3 color;\n"
"in vec2 pos;\n"
"void main()\n"
"{\n"
"    outColor = vec4(color.r, 0.4f + color.g, color.b, 1.0);\n"
"	if (pos.x < 0.2 && pos.x > - 0.2 && pos.y < 0.2 && pos.y > -0.2)\n"
"	discard;\n"

"}\n";

GLuint	compile_shader(GLenum type, const char *text)
{
	GLuint	shader;
	GLint	success;
	GLint	logsize;
	GLchar	errorlog[4096];
	char	*type_str;

	type_str = NULL;
	if (GL_FRAGMENT_SHADER)
		type_str = "fragment";
	else
		type_str = "vertex";

	// Compile vertex shader
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &text, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (success != GL_TRUE)
	{
		ft_printf("%s compile failed.\n", type_str);
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logsize);
		glGetShaderInfoLog(shader, 4096, &logsize, errorlog);
		ft_printf("%s\n", errorlog);
		exit (1);
	}
	else
		ft_printf("%s compile successful.\n", type_str);
	return (shader);
}

GLuint	link_program(GLuint vert_shader, GLuint frag_shader)
{
	GLuint	program;
	GLint	param;
	GLchar	log[4096];

	program = glCreateProgram();
	glAttachShader(program, vert_shader);
	glAttachShader(program, frag_shader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &param);
	if (!param)
	{
		glGetProgramInfoLog(program, sizeof(log), NULL, log);
		ft_eprintf("error: link %s\n", (char *)log);
		exit(1);
	}
	else
		ft_printf("program load successful.\n");
	glDetachShader(program, vert_shader);
	glDetachShader(program, frag_shader);
	glDeleteShader(vert_shader);
	glDeleteShader(frag_shader);
	return (program);
}

void	init_glew()
{
	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		ft_eprintf("Error: %s\n", glewGetErrorString(err));
		exit (1);
	}
	ft_printf("GLEW %s\n", glewGetString(GLEW_VERSION));
}

void	gl_render(GLFWwindow *win)
{
	GLuint		vertex_shader;
	GLuint		fragment_shader;
	GLuint		program;
	GLint		mvp_location;
	GLint		vcol_location;
	GLuint		vao_pts;
	GLuint		vbo_pts;

	return ;

	vertex_shader = compile_shader(GL_VERTEX_SHADER, vertex_shader_text);
	fragment_shader = compile_shader(GL_FRAGMENT_SHADER, fragment_shader_text);

	// Load shaders into program
	program = link_program(vertex_shader, fragment_shader);

	// Vertex buffer object
	glGenBuffers(1, &vbo_pts);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_pts);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Vertex array object
	glGenVertexArrays(1, &vao_pts);
	glBindVertexArray(vao_pts);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_pts);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	mvp_location = glGetUniformLocation(program, "MVP");
	vcol_location = glGetUniformLocation(program, "vCol");

	while (!glfwWindowShouldClose(win))
	{
		float		ratio;
		int			width;
		int			height;
		t_mat4x4	c;
		t_mat4x4	m;
		t_mat4x4	p;
		t_mat4x4	mvp;
		t_camera	camera;

		glfwGetFramebufferSize(win, &width, &height);
		ratio = width / (float)height;

		glViewport(0, 0, width, height);

		camera.top = 1.f;
		camera.bottom = -1.f;
		camera.left = -ratio;
		camera.right = ratio;
		camera.near = 1.f;
		camera.far = -1.f;

		mat4x4_identity(m);
		//mat4x4_identity(p);
		//mat4x4_identity(mvp);
		//mat4x4_rotate_Z(m, m, (float) glfwGetTime());
		mat4x4_rotate_z(m, (float)cos((float) glfwGetTime()) * 4);
		mat4x4_copy(c, m);
		mat4x4_multiply(m, c, m);
		mat4x4_copy(c, m);
		mat4x4_rotate_x(m, (float)sin((float)glfwGetTime()) * 3);
		mat4x4_multiply(m, c, m);
		//mat4x4_rotate_X(m, (float)sin((float) glfwGetTime()) * 3);
		//mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		mat4x4_ortho(p, &camera);
		mat4x4_multiply(mvp, p, m);
		//camera.angle_of_view = 90.f;
		//camera.aspect = 1.f;
		//camera.far = 100.f;
		//camera.near = 1.f;
		//camera.top = 1.f;
		//camera.bottom = -1.f;
		//camera.left = -1.f;
		//camera.right = 1.f;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(program);

		glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat *)mvp);
		glUniform3fv(vcol_location, 1, (const GLfloat *)col);
		glBindVertexArray(vao_pts);
		//glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		glUseProgram(0);

		glfwSwapBuffers(win);
		glfwPollEvents();
		//glfwWaitEvents();
	}
}

// Si
// Shadow rays
// - sent toward light sources
// - determine if ray intersect objects
// Ri
// Reflected rays
// - if surface is reflective, ray is projected as reflected ray
// Ti
// Transmitted rays
//
// ray live until scene end or max recursion level reached
//
// ray:
// R0: origin
// Rd: direction
typedef struct	s_ray
{
	t_vec3f	origin;
	t_vec3f	direction;

}				t_ray;

// solution of Quadratic equation:
// normal way:
// x = [-b (+/-)(b2 - 4ac).5]/2a
// may give numerical error if a or c is small
// better way:
// q = -0.5 [b + sgn(b) (b2 - 4ac).5]
// then x1 = q/a; x2 =c/q;

// * ray generated for each pixel
//


void	rt_render(GLFWwindow *win)
{
	// We are loading the scene after the graphic libary is loaded
	// since we will load scene dynamicaly
	// Load the scene
	load_scene(FILE_SCENE_EXAMPLE);
	// Set the scene

	while (!glfwWindowShouldClose(win))
	{
		int			width;
		int			height;

		glfwGetFramebufferSize(win, &width, &height);

		// Trace rays
		// t_ray

		glfwSwapBuffers(win);
		glfwWaitEvents();
	}
}

int		main(int argc, const char **argv)
{
	GLFWwindow	*win;
	const char	*version;
	t_context	context;

	ft_bzero(&context, sizeof(t_context));
	context.size.x = WINDOW_WIDTH;
	context.size.y = WINDOW_HEIGHT;

	if (argc < 1 || get_arguments(argc, argv, &context))
		return (1);
	if (!(win = glfw_window_init(context.size.x, context.size.y, WINDOW_TITLE)))
		return (1);

	version = glfwGetVersionString();
	ft_printf("GLFW %s\n", version);
	//glfwWindowHint(GLFW_SAMPLES, 4);
	//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	glfwMakeContextCurrent(win);
	init_glew();

	ft_printf("OpenGL %s\n", (char *)glGetString(GL_VERSION));
	glfwSwapInterval(1);

	glfwSetKeyCallback(win, key_callback);
	gl_render(win);
	rt_render(win);

	glfwTerminate();
	return (0);
}
