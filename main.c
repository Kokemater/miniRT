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
		printf("\ndiameter: %f", s->cylinders.arr[i].d);
		printf("\nheight: %f", s->cylinders.arr[i].h);
		printf("\ncolor: ");
		color_print(s->cylinders.arr[i].color);
		printf("\n");
		++i;
	}
}

t_vec3 v3add(t_vec3 a, t_vec3 b)
{
    t_vec3 ret;

    ret.x = a.x + b.x;
    ret.y = a.y + b.y;
    ret.z = a.z + b.z;
    return (ret);
}

t_vec3 v3sub(t_vec3 a, t_vec3 b)
{
    t_vec3 ret;

    ret.x = a.x - b.x;
    ret.y = a.y - b.y;
    ret.z = a.z - b.z;
    return (ret);
}

t_vec3 v3mulf(t_vec3 a, float f)
{
    t_vec3 ret;

    ret.x = a.x * f;
    ret.y = a.y * f;
    ret.z = a.z * f;
    return (ret);
}


t_color colormulf(t_color a, float f)
{
    t_color ret;

    ret.r = a.r * f;
    ret.g = a.g * f;
    ret.b = a.b * f;
    return (ret);
}

t_color coloradd(t_color a, t_color b)
{
    t_color ret;

    ret.r = a.r + b.r;
    ret.g = a.g + b.g;
    ret.b = a.b + b.b;
    return (ret);
}

float v3lenght(t_vec3 a)
{

    return (sqrtf(v3dot(a,a)));
}

t_vec3 v3normalize(t_vec3 a)
{
    return (v3mulf(a, 1/(v3lenght(a))));
}
t_vec3	v3cross(t_vec3 a, t_vec3 b)
{
	t_vec3 result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return result;
}

t_hit_result ray_sphere(t_sphere *s, t_ray *r)
{
    t_hit_result ret;
    t_vec3 c_q = v3sub(s->pos, r->or);
    float abc[3];
    abc[0] = v3dot(r->dir, r->dir);
    abc[1] = v3dot(v3mulf(r->dir, -2.0), c_q);
    abc[2] = v3dot(c_q, c_q) - s->r *s->r;
    float discriminant = abc[1]*abc[1] - 4*abc[0]*abc[2];
    if (discriminant < 0)
    {
        ret.t = -1;
    } else
    {
        ret.t =  (-abc[1] - sqrtf(discriminant) ) / (2.0*abc[0]);
		if ((ret.t < 0))
			return (ret);
        ret.p = v3add(r->or ,v3mulf(r->dir, ret.t));
        ret.n = v3normalize(v3sub(ret.p, s->pos));
    }
    return (ret);
}

t_color ray_color(t_ray *ray, t_state *state)
{
	(void) ray;
	(void) state;
	t_hit_result r = ray_sphere(&state->spheres.arr[0], ray);
	if (r.t > 0)
	{
		float intensity = v3dot(v3normalize(v3sub(state->light.pos, r.p)), r.n) * state->light.brightness;
		if (intensity < 0)
			intensity = 0;
		t_color color = coloradd(
			colormulf(state->spheres.arr[0].color, intensity),
			colormulf(state->ambient.color, state->ambient.ratio)
		);
		return color;
	}
	return ((t_color){0, 0, 0});
}

int loop(void *param)
{
    t_state *s = (t_state *)param;

	t_color c;
	t_ray	r;

	// cuidado con paralelo up y forward !
	//s->angle += 0.1f;
	//s->camera.fwd = (t_vec3){cosf(s->angle), 0.f, -sinf(s->angle)};
	t_vec3 up;
	t_vec3 right;
	t_vec3 current;
	

	right = v3cross((t_vec3){0, 1, 0},s->camera.fwd);
	up  = v3cross(right,s->camera.fwd);
	float width = 2 * tanf(s->camera.fov / 2.f);
	float height = width / ((float) WIN_WIDTH / (float) WIN_HEIGHT);
	t_vec3 q = v3add(
		s->camera.pos, 
		v3add(
			s->camera.fwd,
			v3add (
				v3mulf(up, -height/2.f),
				v3mulf(right, -width/2.f)
			))
		);
	for (int y = 0; y < WIN_HEIGHT; ++y)
	{
		t_vec3 dy = v3mulf(up, height / (float) WIN_HEIGHT * y);
		for (int x = 0; x < WIN_WIDTH; ++x)
		{
			t_vec3 dx = v3mulf(right, width / (float) WIN_WIDTH * x);
			current = v3add(q, v3add(dx, dy));
			r.or = s->camera.pos;
			r.dir = v3normalize(v3sub(current, r.or));
			c = ray_color(&r, s);
			img_put_pixel(&s->img, x, y, c);
		}
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
    mlx_loop(state.mlx);

	minirt_cleanup(&state);
    return (0);
}
