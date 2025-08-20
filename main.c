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
	i = 0;
	while (i < s->spheres.count)
	{
		printf("%i:\n", i);
		printf("position: ");
		v3_print(s->spheres.arr[i].pos);
		printf("\nradius: %f\n", s->spheres.arr[i].r);
		printf("color: ");
		color_print(s->spheres.arr[i].color);
		printf("\n");
		++i;
	}
	printf("\n[PLANES]\n");
	i = 0;
	while (i < s->planes.count)
	{
		printf("%i:\n", i);
		printf("position: ");
		v3_print(s->planes.arr[i].pos);
		printf("\nnormal: ");
		v3_print(s->planes.arr[i].normal);
		printf("\ncolor: ");
		color_print(s->planes.arr[i].color);
		printf("\n");
		++i;
	}
	printf("\n[CYLINDERS]\n");
	i = 0;
	while (i < s->cylinders.count)
	{
		printf("%i:\n", i);
		printf("position: ");
		v3_print(s->cylinders.arr[i].pos);
		printf("\nforward: ");
		v3_print(s->cylinders.arr[i].fwd);
		printf("\nradius: %f", s->cylinders.arr[i].r);
		printf("\nheight: %f", s->cylinders.arr[i].h);
		printf("\ncolor: ");
		color_print(s->cylinders.arr[i].color);
		printf("\n");
		++i;
	}
}

t_color ray_color(t_ray *ray, t_state *state)
{
	float		ndotl; t_hit_result	c;

	c = intersect_scene(ray, state);
	if (c.t > 0)
	{
		ndotl = v3dot(v3normalize(v3sub(state->light.pos, c.p)), c.n);
		if (ndotl < 0)
			ndotl = 0;
		t_color color = coloradd(
			colormulf(c.c, ndotl * state->light.brightness),
			colormulf(state->ambient.color, state->ambient.ratio)
		);
		return color;
	}
	return ((t_color){255, 0, 255});
}

int loop(t_state *s)
{
	int	x;
	int	y;
	t_vec3	q;
	
	q = v3add(s->camera.pos, s->camera.fwd);
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		t_vec3 dy = v3mulf(s->camera.up, s->camera.vh * (y / (float)WIN_HEIGHT - .5f));
		while (x < WIN_WIDTH)
		{
			t_vec3 dx = v3mulf(s->camera.right, s->camera.vw * (x / (float)WIN_WIDTH - .5f));
			img_put_pixel(&s->img, x, y, ray_color(&(t_ray){
					.or  = s->camera.pos,
					.dir = v3normalize(v3sub(v3add(q, v3add(dx, dy)), s->camera.pos))
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

	state.win = mlx_new_window(state.mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	if (!state.win)
		minirt_error(&state, "Could not create window\n");

	minirt_create_img(&state);

	mlx_hook(state.win, 17, 0, close_event, &state);
	mlx_key_hook(state.win, key_event, &state);

	mlx_loop_hook(state.mlx, loop, &state);

	state.camera.vw = 2 * tanf(state.camera.fov / 2.f);
	state.camera.vh = state.camera.vw / ((float) WIN_WIDTH / (float) WIN_HEIGHT);
	state.camera.right = v3cross((t_vec3){0, 1, 0}, state.camera.fwd);
	state.camera.up  = v3cross(state.camera.right, state.camera.fwd);
	mlx_loop(state.mlx);

	minirt_cleanup(&state);
	return (0);
}
