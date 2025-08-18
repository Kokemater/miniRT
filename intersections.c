#include "minirt.h"

static t_hit_result ray_plane(t_plane *p, t_ray *r)
{
	(void)p;
	(void)r;
	t_hit_result	ret;

	ret.t = -1.f;
	return (ret);
}

static t_hit_result ray_cylinder(t_cylinder *c, t_ray *r)
{
	(void)c;
	(void)r;
	t_hit_result	ret;

	ret.t = -1.f;
	return (ret);
}

static t_hit_result ray_sphere(t_sphere *s, t_ray *r)
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

t_hit_result	intersect_scene(t_ray *ray, t_state *state)
{
	unsigned int	i;
	t_hit_result c;
	t_hit_result r;

	i = 0;
	c.t = -1;
	while (i < state->spheres.count)
	{
		r = ray_sphere(&state->spheres.arr[i], ray);
		r.c = state->spheres.arr[i].color;
		if ((r.t > 0 && r.t < c.t) || c.t < 0)
			c = r;
		++i;
	}
	i = 0;
	while (i < state->planes.count)
	{
		r = ray_plane(&state->planes.arr[i], ray);
		r.c = state->planes.arr[i].color;
		if ((r.t > 0 && r.t < c.t) || c.t < 0)
			c = r;
		++i;
	}
	i = 0;
	while (i < state->cylinders.count)
	{
		r = ray_cylinder(&state->cylinders.arr[i], ray);
		r.c = state->cylinders.arr[i].color;
		if ((r.t > 0 && r.t < c.t) || c.t < 0)
			c = r;
		++i;
	}
	return (c);
}

