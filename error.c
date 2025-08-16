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
	if (!state->mlx)
		return ;
	if (state->img.handle)
		mlx_destroy_image(state->mlx, state->img.handle);
	if (state->win)
		mlx_destroy_window(state->mlx, state->win);
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

