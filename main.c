/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutragu <jbutragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:06:04 by jbutragu          #+#    #+#             */
/*   Updated: 2025/08/21 12:36:44 by jbutragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs/libft/libft.h"
#include "libs/minilibx-linux/mlx.h"
#include "minirt.h"

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
	mlx_put_image_to_window(s->mlx, s->win, s->img.handle, 0, 0);
	return (0);
}

int	close_event(void *param)
{
	minirt_cleanup((t_state *)param);
	exit(0);
}

int	key_event(int keycode, void *param)
{
	if (keycode == KEY_ESC)
	{
		minirt_cleanup((t_state *)param);
		exit(0);
	}
	return (0);
}

void	minirt_init(t_state *state)
{
	state->mlx = mlx_init();
	if (!state->mlx)
		minirt_error(state, "Could not initialize minilibx\n");
	state->win = mlx_new_window(state->mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	if (!state->win)
		minirt_error(state, "Could not create window\n");
	minirt_create_img(state);
	mlx_hook(state->win, 17, 0, close_event, state);
	mlx_key_hook(state->win, key_event, state);
	mlx_loop_hook(state->mlx, loop, state);
	state->cam.vw = 2 * tanf(state->cam.fov / 2.f);
	state->cam.vh = state->cam.vw / ((float) WIN_WIDTH / (float) WIN_HEIGHT);
	state->cam.right = v3cross((t_vec3){0, 1, 0}, state->cam.fwd);
	state->cam.up = v3cross(state->cam.right, state->cam.fwd);
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
	mlx_loop(state.mlx);
	minirt_cleanup(&state);
	return (0);
}
