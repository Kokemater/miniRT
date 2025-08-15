#include "libs/libft/libft.h"
#include "libs/minilibx-linux/mlx.h"
#include "minirt.h"

void	color_print(t_color c)
{
	printf("[c](%i, %i, %i)", c.r, c.g, c.b);
}

void	v3_print(t_vec3 v)
{
	printf("[v](%.2f, %.2f, %.2f)", v.x, v.y, v.z);
}

void	state_print(t_state *s)
{
	unsigned int	i;

	i = 0;
	printf("[AMBIENT]\n");
	printf("ratio: %f\n", s->ambient.ratio);
	printf("color: ");
	color_print(s->ambient.color);
	printf("\n\n[CAMERA]\n");
	printf("position: ");
	v3_print(s->camera.pos);
	printf("\norientation: ");
	v3_print(s->camera.fwd);
	printf("\nfov: %f", s->camera.fov);
	printf("\n\n[LIGHT]\n");
	printf("position: ");
	v3_print(s->light.pos);
	printf("\nbrightness: %f\n", s->light.brightness);
	printf("color: ");
	color_print(s->light.color);
	printf("\n\n[SPHERES]\n");
	while (i < s->spheres.count)
	{
		printf("%i:\n", i);
		printf("position: ");
		v3_print(s->spheres.arr[i].pos);
		printf("\ndiameter: %f\n", s->spheres.arr[i].d);
		printf("color: ");
		color_print(s->spheres.arr[i].color);
		printf("\n");
		++i;
	}
}

int loop(void *param)
{
    t_state *state = (t_state *)param;
	(void)state;
    return (0);
}

int main(int argc, char *argv[])
{
    t_state state;
	int		file;

	ft_bzero(&state, sizeof(t_state));
	if (argc != 2)
		minirt_error(&state, "Usage: ./miniRT <scene file>\n");

	file = open(argv[1], O_RDONLY);
	if (file < 0)
		minirt_error(&state, "Could not open scene file\n");
	parse_file(&state, file);
	state_print(&state);
	close(file);

    state.mlx = mlx_init();
    if (!state.mlx)
		minirt_error(&state, "Could not initialize minilibx\n");

    state.win = mlx_new_window(state.mlx, 800, 600, "miniRT");
    if (!state.win)
		minirt_error(&state, "Could not create window\n");

    mlx_loop_hook(state.mlx, loop, &state);
    mlx_loop(state.mlx);

    return (0);
}
