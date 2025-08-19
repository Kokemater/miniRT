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
	ret.p = v3add(p->pos, v3mulf(r->dir, ret.t));
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
	
    float t0 = (-B - sqrt_discr) / (2.f*A);
    float t1 = (-B + sqrt_discr) / (2.f*A);

    // choose nearest positive t
    float t_hit = (t0 > 0.f) ? t0 : ((t1 > 0.f) ? t1 : -1.f);
    if (t_hit < 0.f)
        return ret; // both behind the ray

    ret.t = t_hit;
    ret.p = v3add(r->or, v3mulf(r->dir, t_hit));

	t_vec3 p0 = v3add(r->or, v3mulf(r->dir, t0));
	t_vec3 p1 = v3add(r->or, v3mulf(r->dir, t1));
    t_vec3 hit0 = v3sub(p0, c->pos);
    float h0 = v3dot(hit0, u);
	t_vec3 hit1 = v3sub(p1, c->pos);
    float h1 = v3dot(hit1, u);

	if ((fabs(h0) > c->h/2.f && fabs(h1) > c->h/2.f) || (t0 < 0) || (t1 < 0))
	{
	}


	if (fabs(h0) > c->h/2.f && fabs(h1) < c->h/2.f)
	{
		t_plane p;
		p.color = c->color;
		p.normal = c->fwd;
		if (h0 > 0)
			p.pos = v3add(c->pos, v3mulf(c->fwd, c->h /2.f));
		else
			p.pos = v3add(c->pos, v3mulf(c->fwd, -c->h /2.f));
		return (ray_plane(&p, r));
	}

    t_vec3 hit_to_axis = v3sub(ret.p, c->pos);
    float h = v3dot(hit_to_axis, u);
    t_vec3 proj_on_axis = v3mulf(u, h);
    ret.n = v3normalize(v3sub(hit_to_axis, proj_on_axis));
	if (v3dot(ret.n, r->dir) > 0)
		ret.n = v3mulf(ret.n, -1.f);
    return ret;
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
		r = ray_cylinder(&state->cylinders.arr[i], ray);
		r.c = state->cylinders.arr[i].color;
		if ((r.t > 0 && r.t < c.t) || c.t < 0)
			c = r;
		++i;
	}
	return (c);
}

