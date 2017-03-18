/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 18:18:01 by tdefresn          #+#    #+#             */
/*   Updated: 2017/03/18 16:34:41 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static const struct
{
	float	x;
	float	y;
	float	r;
	float	g;
	float	b;
}			vertices[3] =
{
	{ -0.6f, -0.4f, 1.f, 0.f, 0.f },
	{ 0.6f, -0.4f, 0.f, 1.f, 0.f },
	{ 0.f, 0.6f, 0.f, 0.f, 1.f }
};

static const char * vertex_shader_text =
"uniform mat4 MVP;\n"
"attribute vec3 vCol;\n"
"atribute vec2 vPos;\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
"    color = vCol;\n"
"}\n";

static const char* fragment_shader_text =
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(color, 1.0);\n"
"}\n";

int		main(int argc, char **argv)
{
	GLFWwindow	*win;
	t_rt		rt;
	GLuint		vertex_buffer;
	GLuint		vertex_shader;
	GLuint		fragment_shader;
	GLuint		program;
	GLint		mvp_location;
	GLint		vpos_location;
	GLint		vcol_location;

	if (argc < 1)
		return (1);
	ft_bzero(&rt, sizeof(t_rt));
	rt.width = WIN_WIDTH;
	rt.height = WIN_HEIGHT;
	parse_arguments(argc - 1, &argv[1], &rt);
	if (!glfwInit())
		ft_printf("Cannot initialize GLFW\n");
	glfwSetErrorCallback((GLFWerrorfun)error_glfw);
	win = glfwCreateWindow(rt.width, rt.height, "RTv1", NULL, NULL);
	if (!win)
	{
		glfwTerminate();
		return (1);
	}
	glfwSetKeyCallback(win, key_callback);
	glfwMakeContextCurrent(win);
	glfwSwapInterval(1);
	glGenBuffers(1, &vertex_buffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
	glCompileShader(vertex_shader);

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
	glCompileShader(fragment_shader);

	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	mvp_location = glGetUniformLocation(program, "MVP");
	vpos_location = glGetUniformLocation(program, "vPos");
	vcol_location = glGetUniformLocation(program, "vCol");

	glEnableVertexAttribArray(vpos_location);
	glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void *)0);
	glEnableVertexAttribArray(vcol_location);
	glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void *)(sizeof(float) * 2));
	while (!glfwWindowShouldClose(win))
	{
		float	ratio;
		/*
		mat4x4	m;
		mat4x4	p;
		mat4x4	mvp;
		*/

		int	width;
		int	height;

		glfwGetFramebufferSize(win, &width, &height);
		ratio = width / (float)height;

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		/*
		mat4x4_identity(m);
		mat4x4_rotate_Z(m, m, (float) glfwGetTime());
		mat_4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		mat4x4_mul(mvp, p, m);
		*/

		glUseProgram(program);
		//glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat *)mvp);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(win);
		glfwPollEvents();
		//glfwWaitEvents();
	}
	glfwTerminate();
	return (0);
}
