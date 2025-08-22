/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutragu <jbutragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:54:07 by jbutragu          #+#    #+#             */
/*   Updated: 2025/08/22 16:08:01 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	minirt_cleanup(t_state *state)
{
	(void)state;
	if (state->spheres.arr)
		free(state->spheres.arr);
	if (state->planes.arr)
		free(state->planes.arr);
	if (state->cylinders.arr)
		free(state->cylinders.arr);
	if (state->lights.arr)
		free(state->lights.arr);
	if (state->fline)
		free(state->fline);
	if (state->img.handle)
		mlx_destroy_image(state->mlx, state->img.handle);
	if (state->win)
		mlx_destroy_window(state->mlx, state->win);
	if (!state->mlx)
		return ;
	mlx_destroy_display(state->mlx);
	free(state->mlx);
}

void	minirt_error(t_state *state, char *message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	minirt_cleanup(state);
	exit(1);
}
