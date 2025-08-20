#include "minirt.h"

static t_hit_result ray_plane(t_plane *p, t_ray *r)
{
	t_hit_result	ret;
	float			ddotn;

	ddotn = v3dot(r->dir, p->normal);
	ret.t = -1.f;
	if (fabs(ddotn) < FLT_EPSILON)
		return (ret);
	ret.t = (v3dot(p->pos, p->normal) - v3dot(r->or, p->normal)) / ddotn;
	if (ret.t < 0)
		return (ret);
	ret.p = v3add(r->or, v3mulf(r->dir, ret.t));
	if (v3dot(r->dir, p->normal) < 0)
		ret.n = p->normal;
	else
		ret.n = v3mulf(p->normal, -1.f);
	return (ret);
}

static t_hit_result ray_cylinder(t_cylinder *c, t_ray *r)
{
    t_hit_result ret;
    ret.t = -1.f;

    t_vec3 w = v3sub(r->or, c->pos);
    t_vec3 u = c->fwd;
    t_vec3 v = r->dir;

    t_vec3 v_perp = v3sub(v, v3mulf(u, v3dot(v, u)));
    t_vec3 w_perp = v3sub(w, v3mulf(u, v3dot(w, u)));

    float A = v3dot(v_perp, v_perp);
    float B = 2.f * v3dot(v_perp, w_perp);
    float C = v3dot(w_perp, w_perp) - c->r * c->r;

    float discr = B*B - 4.f*A*C;
    if (discr < 0.f || A == 0.f)
        return ret;

    float sqrt_discr = sqrtf(discr);
	
    ret.t = (-B - sqrt_discr) / (2.f*A);
	ret.p = v3add(r->or, v3mulf(r->dir, ret.t));
	float h = v3dot(v3sub(ret.p, c->pos), c->fwd);
	if (ret.t < 0.f || fabs(h) > c->h / 2.f)
	{
		ret.t = (-B + sqrt_discr) / (2.f*A);
		ret.p = v3add(r->or, v3mulf(r->dir, ret.t));
		h = v3dot(v3sub(ret.p, c->pos), c->fwd);
		if (ret.t < 0.f || fabs(h) > c->h / 2.f)
			return ((t_hit_result){.t = -1.f});
	}

    ret.n = v3normalize(v3sub(v3sub(ret.p, c->pos), v3mulf(c->fwd, h)));
	if (v3dot(ret.n, r->dir) > 0)
		ret.n = v3mulf(ret.n, -1.f);
    return ret;
}


t_hit_result ray_tapered_cyl(t_cylinder *c, t_ray *r)
{
	float	d2;
	t_hit_result res = ray_cylinder(c, r);
	t_vec3 ppos = v3add(c->pos, v3mulf(c->fwd, c->h / 2.f));
	t_hit_result p1 = ray_plane(&(t_plane){
		.color = c->color,
		.normal = c->fwd,
		.pos = ppos,
	}, r);
	d2 = v3length2(v3cross(c->fwd, v3sub(p1.p, c->pos)));
	
	
	if (p1.t > 0 && d2 < c->r * c->r && (p1.t < res.t || res.t < 0))
		res = p1;

	p1 = ray_plane(&(t_plane){
		.color = c->color,
		.normal = c->fwd,
		.pos = v3add(c->pos, v3mulf(c->fwd, -c->h / 2.f))
	}, r);
	d2 = v3length2(v3cross(c->fwd, v3sub(p1.p, c->pos)));
	if (p1.t > 0 && d2 < c->r * c->r && (p1.t < res.t || res.t < 0))
		res = p1;
	return (res);
}


static t_hit_result ray_sphere(t_sphere *s, t_ray *r)
{
	t_hit_result ret;
	t_vec3 c_q = v3sub(s->pos, r->or);
	float abc[3];
	abc[0] = v3dot(r->dir, r->dir);
	abc[1] = v3dot(v3mulf(r->dir, -2.0), c_q);
	abc[2] = v3dot(c_q, c_q) - s->r *s->r;
	ret.t = -1;
	float discriminant = abc[1]*abc[1] - 4*abc[0]*abc[2];
	if (discriminant < 0)
		return (ret);
	ret.t =  (-abc[1] - sqrtf(discriminant) ) / (2.0*abc[0]);
	if (ret.t < 0)
	{
		ret.t = (-abc[1] + sqrtf(discriminant) ) / (2.0*abc[0]);
		if (ret.t < 0)
			return (ret);
	}
	ret.p = v3add(r->or ,v3mulf(r->dir, ret.t));
	ret.n = v3normalize(v3sub(ret.p, s->pos));
	if (v3dot(ret.n, r->dir) > 0)
		ret.n = v3mulf(ret.n, -1.f);
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
		r = ray_tapered_cyl(&state->cylinders.arr[i], ray);
		r.c = state->cylinders.arr[i].color;
		if ((r.t > 0 && r.t < c.t) || c.t < 0)
			c = r;
		++i;
	}
	return (c);
}

