/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutragu <jbutragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:06:04 by jbutragu          #+#    #+#             */
/*   Updated: 2025/08/21 19:40:10 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs/libft/libft.h"
#include "libs/minilibx-linux/mlx.h"
#include "minirt.h"
#include <GLFW/glfw3.h>

int	loop(t_state *s)
{
	int		x;
	int		y;
	t_vec3	q;
	t_vec3	dy;
	t_vec3	dx;

	q = v3add(s->cam.pos, s->cam.fwd);
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		dy = v3mulf(s->cam.up, s->cam.vh * (y / (float)WIN_HEIGHT - .5f));
		while (x < WIN_WIDTH)
		{
			dx = v3mulf(s->cam.right, s->cam.vw * (x / (float)WIN_WIDTH - .5f));
			img_put_pixel(&s->img, x, y, ray_color(&(t_ray){
					.or = s->cam.pos,
					.dir = v3norm(v3sub(v3add(q, v3add(dx, dy)), s->cam.pos))
				}, s));
			++x;
		}
		++y;
	}
	// mlx_put_image_to_window(s->mlx, s->win, s->img.handle, 0, 0);
	return (0);
}

void	close_event(GLFWwindow *w)
{
	t_state	*s = glfwGetWindowUserPointer(w);
	minirt_cleanup(s);
	exit(0);
}

void	key_event(GLFWwindow *w, int key, int scancode, int action, int mods)
{
	t_state	*s = glfwGetWindowUserPointer(w);
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		minirt_cleanup(s);
		exit(0);
	}
}

void	minirt_init(t_state *state)
{
	if (!glfwInit())
		minirt_error(state, "Could not initialize glfw\n");
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	state->win = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "miniRT", 0, 0);
	if (!state->win)
		minirt_error(state, "Could not create window\n");
	glfwSetWindowUserPointer(state->win, state);
	glfwSetWindowCloseCallback(state->win, close_event);
	glfwSetKeyCallback(state->win, key_event);
	glfwMakeContextCurrent(state->win);
	if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
		minirt_error(state, "Could not load gl\n");
	minirt_create_img(state);

    const char* vertexShaderSource = R"(
        #version 460 core
        out vec2 TexCoord;
        void main() {
            vec2 vertices[3] = vec2[3](
                vec2(-1.0, -1.0),
                vec2(3.0, -1.0),
                vec2(-1.0, 3.0)
            );
            vec2 texCoords[3] = vec2[3](
                vec2(0.0, 0.0),
                vec2(2.0, 0.0),
                vec2(0.0, 2.0)
            );
            gl_Position = vec4(vertices[gl_VertexID], 0.0, 1.0);
            TexCoord = texCoords[gl_VertexID];
        }
    )";

    const char* fragmentShaderSource = R"(
        #version 460 core
        out vec4 FragColor;
        in vec2 TexCoord;
        uniform sampler2D rayTraceTexture;
        void main() {
            vec2 uv = clamp(TexCoord, 0.0, 1.0);
            FragColor = texture(rayTraceTexture, uv);
        }
    )";
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    state->shader = glCreateProgram();
    glAttachShader(state->shader, vertexShader);
    glAttachShader(state->shader, fragmentShader);
    glLinkProgram(state->shader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

	glCreateVertexArrays(1, &state->vao);
	state->cam.vw = 2 * tanf(state->cam.fov / 2.f);
	state->cam.vh = state->cam.vw / ((float) WIN_WIDTH / (float) WIN_HEIGHT);
	state->cam.right = v3cross((t_vec3){0, 1, 0}, state->cam.fwd);
	state->cam.up = v3cross(state->cam.right, state->cam.fwd);
}

void	minirt_loop(t_state *state)
{
	while (!glfwWindowShouldClose(state->win))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		loop(state);
		glTextureSubImage2D(state->img.handle, 0, 0, 0, WIN_WIDTH, WIN_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, state->img.data);
		glUseProgram(state->shader);
		glBindTextureUnit(0, state->img.handle);
		glBindVertexArray(state->vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(state->win);
		glfwPollEvents();
	}
}

int	main(int argc, char *argv[])
{
	t_state	state;
	int		file;

	ft_bzero(&state, sizeof(t_state));
	if (argc != 2)
		minirt_error(&state, "Usage: ./miniRT <scene file>\n");
	file = open(argv[1], O_RDONLY);
	if (file < 0)
		minirt_error(&state, "Could not open scene file\n");
	parse_file(&state, file);
	check_state(&state);
	close(file);
	minirt_init(&state);
	minirt_loop(&state);
	minirt_cleanup(&state);
	return (0);
}
