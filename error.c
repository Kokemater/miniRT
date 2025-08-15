#include "minirt.h"

void	minirt_cleanup(t_state *state)
{
	if (!state->mlx)
		return ;
	if (state->win)
		mlx_destroy_window(state->mlx, state->win);
	mlx_destroy_display(state->mlx);
	if (state->spheres.arr)
		free(state->spheres.arr);
	free(state->mlx);
}

void	minirt_error(t_state *state, char *message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	minirt_cleanup(state);
	exit(1);
}

