#include "minirt.h"

static void	intersect_spheres(t_ray *ray, t_state *state, t_hit_result *closest)
{
	unsigned int	i;
	t_hit_result	r;

	i = 0;
	while (i < state->spheres.count)
	{
		r = ray_sphere(&state->spheres.arr[i], ray);
		r.c = state->spheres.arr[i].color;
		if ((r.t > 0 && r.t < closest->t) || closest->t < 0)
			*closest = r;
		++i;
	}
}

static void	intersect_planes(t_ray *ray, t_state *state, t_hit_result *closest)
{
	unsigned int	i;
	t_hit_result	r;

	i = 0;
	while (i < state->planes.count)
	{
		r = ray_plane(&state->planes.arr[i], ray);
		r.c = state->planes.arr[i].color;
		if ((r.t > 0 && r.t < closest->t) || closest->t < 0)
			*closest = r;
		++i;
	}
}

static void	intersect_cylinders(t_ray *ray, t_state *state, t_hit_result *closest)
{
	unsigned int	i;
	t_hit_result	r;

	i = 0;
	while (i < state->cylinders.count)
	{
		r = ray_cap_cylinder(&state->cylinders.arr[i], ray);
		r.c = state->cylinders.arr[i].color;
		if ((r.t > 0 && r.t < closest->t) || closest->t < 0)
			*closest = r;
		++i;
	}
}

t_hit_result	intersect_scene(t_ray *ray, t_state *state)
{
	t_hit_result	c;

	c.t = -1;
	intersect_spheres(ray, state, &c);
	intersect_planes(ray, state, &c);
	intersect_cylinders(ray, state, &c);
	if (v3dot(c.n, ray->dir) > 0)
		c.n = v3mulf(c.n, -1.f);
	return (c);
}