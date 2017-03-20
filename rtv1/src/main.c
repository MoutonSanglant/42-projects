/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 18:18:01 by tdefresn          #+#    #+#             */
/*   Updated: 2017/03/20 22:16:32 by tdefresn         ###   ########.fr       */
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
/*
"#version 410\n"
"out gl_PerVertex {\n"
"	vec4 gl_Position;\n"
"};\n"
"layout(location = 0) out vec3 fragColor;\n"
"vec2 positions[3] = vec2[](vec2(0.0, -0.5), vec2(0.5, 0.5), vec2(-0.5, 0.5));\n"
"vec3 colors[3] = vec3[](vec3(1.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0), vec3(0.0, 0.0, 1.0));\n"

"void main()\n"
"{\n"
"    gl_Position = vec4(positions[gl_VertexID], 0.0, 1.0);\n"
"    fragColor = colors[gl_VertexID];\n"
"}\n";
*/
"#version 330\n"
"layout(location = 0) in vec2 point;\n"
"uniform float angle;\n"
"void main() {\n"
"    mat2 rotate = mat2(cos(angle), -sin(angle),\n"
"                      sin(angle), cos(angle));\n"
"    gl_Position = vec4(0.75 * rotate * point, 0.0, 1.0);\n"
"}\n";
//)
//"#version 130\n"
//"    gl_Position = vec4(VertexPosition, 1.0);\n"
//"positions[0] = vec2(0.0, -0.5);\n"
//"positions[1] = vec2(0.5, 0.5);\n"
//"positions[2] = vec2(-0.5, -0.5);\n"
//"    gl_Position = vec4(positions[gl_Vertex], 0.0, 1.0);\n"
//"uniform vec2 positions[3] = vec2[](vec2(0.0, -0.5), vec2(0.5, 0.5), vec2(-0.5, 0.5));\n"
//"uniform mat4 MVP;\n"
//"attribute vec3 vCol;\n"
//"attribute vec2 vPos;\n"
//"varying vec3 color;\n"
//"    color = vCol;\n"
//"    gl_Position = vec4(positions[gl_VertexIndex], 0.0, 1.0);\n"
//"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"

static const char* fragment_shader_text =
"#version 330\n"
"out vec4 color;\n"
"void main() {\n"
"    color = vec4(1, 0.15, 0.15, 0);\n"
"}\n";
/*
"#version 410\n"
"layout (location = 0) in vec3 fragColor;\n"
"layout (location = 0) out vec4 outColor;\n"
"void main()\n"
"{\n"
"    outColor = vec4(fragColor, 1.0);\n"
"}\n";
*/
//"    gl_FragColor = vec4(color, 1.0);\n"

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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	win = glfwCreateWindow(rt.width, rt.height, "RTv1", NULL, NULL);
	if (!win)
	{
		glfwTerminate();
		return (1);
	}
	glfwSetKeyCallback(win, key_callback);
	glfwMakeContextCurrent(win);

	init_glew();
	ft_printf("OpenGL %s\n", (char *)glGetString(GL_VERSION));

	glfwSwapInterval(1);
	glGenBuffers(1, &vertex_buffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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


	const float SQUARE[] = {
		-1.0f, 1.0f,
		-1.0f, -1.0f,
		1.0f, 1.0f,
		1.0f, -1.0f,
	};

	GLuint vao_pts;
	GLuint vbo_pts;

	glGenBuffers(1, &vbo_pts);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_pts);
	glBufferData(GL_ARRAY_BUFFER, sizeof(SQUARE), SQUARE, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &vao_pts);
	glBindVertexArray(vao_pts);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_pts);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(win))
	{
		float	ratio;

		t_mat4x4	m;
		t_mat4x4	p;
		t_mat4x4	mvp;
		t_camera	camera;

		//camera.angle_of_view = 90.f;
		//camera.aspect = 1.f;
		//camera.far = 100.f;
		//camera.near = 1.f;
		//camera.top = 1.f;
		//camera.bottom = -1.f;
		//camera.left = -1.f;
		//camera.right = 1.f;


		int	width;
		int	height;

		glfwGetFramebufferSize(win, &width, &height);
		ratio = width / (float)height;

		camera.top = 1.f;
		camera.bottom = -1.f;
		camera.left = -ratio;
		camera.right = ratio;
		camera.near = 1.f;
		camera.far = -1.f;

		(void)m;
		(void)p;
		(void)mvp;
		mat4x4_identity(&m);
		mat4x4_identity(&p);
		mat4x4_identity(&mvp);
		//mat4x4_rotate_Z(m, m, (float) glfwGetTime());
		mat4x4_rotate_Z(&m, (float) glfwGetTime());
		//mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		mat4x4_ortho(&p, &camera);
		mat4x4_mul(&mvp, &p, &m);

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);


		glUseProgram(program);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		//glBindVertexArray(0);
		glUseProgram(0);


		//glUseProgram(program);
		//glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat *)mvp);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(win);
		glfwPollEvents();
		//glfwWaitEvents();
	}
	glfwTerminate();
	return (0);
}
