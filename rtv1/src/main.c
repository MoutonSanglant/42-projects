/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 18:18:01 by tdefresn          #+#    #+#             */
/*   Updated: 2017/03/21 05:23:55 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
"layout(location = 0) in vec2 point;\n"
"uniform mat4 MVP;\n"
"uniform vec3 vCol;\n"
"attribute vec2 vPos;\n"
"varying vec3 color;\n"

"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(point, 0.0, 1.0);\n"
"    color = vCol;\n"
"}\n";

static const char* fragment_shader_text =
"#version 330 core\n"
"varying vec3 color;\n"
"layout (location = 0) out vec4 outColor;\n"
"void main()\n"
"{\n"
"    outColor = vec4(color.r, 0.4f + color.g, color.b, 1.0);\n"
"}\n";

void	init_glew()
{
#ifdef LINUX
	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		ft_eprintf("Error: %s\n", glewGetErrorString(err));
		exit (1);
	}
	ft_printf("Using GLEW: %s\n", glewGetString(GLEW_VERSION));
#endif
}

int		main(int argc, char **argv)
{
	GLFWwindow	*win;
	t_rt		rt;
	GLuint		vertex_shader;
	GLuint		fragment_shader;
	GLuint		program;
	GLint		mvp_location;
	GLint		vcol_location;

	if (argc < 1)
		return (1);
	ft_bzero(&rt, sizeof(t_rt));
	rt.width = WIN_WIDTH;
	rt.height = WIN_HEIGHT;
	parse_arguments(argc - 1, &argv[1], &rt);

	glfwSetErrorCallback((GLFWerrorfun)error_glfw);

	if (!glfwInit())
		ft_printf("Cannot initialize GLFW\n");


	//glfwWindowHint(GLFW_SAMPLES, 4);
	//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	win = glfwCreateWindow(rt.width, rt.height, "RTv1", NULL, NULL);
	if (!win)
	{
		glfwTerminate();
		return (1);
	}

	glfwMakeContextCurrent(win);
	// if...
	init_glew();

	ft_printf("OpenGL %s\n", (char *)glGetString(GL_VERSION));
	glfwSwapInterval(1);

	// Compile vertex shader
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
	glCompileShader(vertex_shader);

	GLint success = 0;
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (success == GL_TRUE)
		ft_printf("vertex compile successful.\n");
	else
	{
		ft_printf("vertex compile failed.\n");
		GLint logsize;
		glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &logsize);

		GLchar *errorlog;
		errorlog = malloc(sizeof(GLchar) * logsize);
		glGetShaderInfoLog(vertex_shader, logsize, &logsize, errorlog);
		ft_printf("%s\n", errorlog);
		exit (1);
	}

	// Compile fragment shader
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
	glCompileShader(fragment_shader);

	success = 0;
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (success == GL_TRUE)
		ft_printf("fragment compile successful.\n");
	else
	{
		ft_printf("fragment compile failed.\n");
		GLint logsize;
		glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &logsize);

		GLchar *errorlog;
		errorlog = malloc(sizeof(GLchar) * logsize);
		glGetShaderInfoLog(fragment_shader, logsize, &logsize, errorlog);
		ft_printf("%s\n", errorlog);
		exit (1);
	}

	// Load shaders into program
	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	GLint param;

	glGetProgramiv(program, GL_LINK_STATUS, &param);
	if (!param)
	{
		GLchar log[4096];
		glGetProgramInfoLog(program, sizeof(log), NULL, log);
		ft_eprintf("error: link %s\n", (char *)log);
		exit(1);
	}
	else
		ft_printf("program load successful.\n");

	glDetachShader(program, vertex_shader);
	glDetachShader(program, fragment_shader);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	GLuint vao_pts;
	GLuint vbo_pts;

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

	glfwSetKeyCallback(win, key_callback);

	while (!glfwWindowShouldClose(win))
	{
		float	ratio;
		int	width;
		int	height;
		mat4x4	m;
		mat4x4	p;
		mat4x4	mvp;
		//t_camera	camera;

		glfwGetFramebufferSize(win, &width, &height);
		ratio = width / (float)height;

		glViewport(0, 0, width, height);


		//camera.top = 1.f;
		//camera.bottom = -1.f;
		//camera.left = -ratio;
		//camera.right = ratio;
		//camera.near = 1.f;
		//camera.far = -1.f;

		mat4x4_identity(m);
		//mat4x4_identity(p);
		//mat4x4_identity(mvp);
		mat4x4_rotate_Z(m, m, (float) glfwGetTime());
		//mat4x4_rotate_Z(m, (float) glfwGetTime());
		mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		//mat4x4_ortho(p, camera);
		mat4x4_mul(mvp, p, m);
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
	glfwTerminate();
	return (0);
}
