/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutragu <jbutragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:54:07 by jbutragu          #+#    #+#             */
/*   Updated: 2025/08/21 19:39:57 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <GLFW/glfw3.h>

void	minirt_cleanup(t_state *state)
{
	if (state->spheres.arr)
		free(state->spheres.arr);
	if (state->planes.arr)
		free(state->planes.arr);
	if (state->cylinders.arr)
		free(state->cylinders.arr);
	if (state->lights.arr)
		free(state->lights.arr);
	// if (state->img.handle)
	// 	mlx_destroy_image(state->mlx, state->img.handle);
	if (state->img.data)
		free(state->img.data);
	if (state->img.handle)
		glDeleteTextures(1, &state->img.handle);
	if (state->shader)
		glDeleteShader(state->shader);
	if (state->vao)
		glDeleteVertexArrays(1, &state->vao);
	if (state->win)
		glfwDestroyWindow(state->win);
	glfwTerminate();
}

void	minirt_error(t_state *state, char *message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	minirt_cleanup(state);
	exit(1);
}
