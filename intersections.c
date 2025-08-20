#include "minirt.h"

t_hit_result ray_plane(t_plane *p, t_ray *r)
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
	ret.n = p->normal;
	return (ret);
}

static void cylinder_quadratic(float ABC[3], t_cylinder *c, t_ray *r)
{
    t_vec3 w = v3sub(r->or, c->pos);
	t_vec3 v_perp;
	t_vec3 w_perp;

    v_perp = v3sub(r->dir, v3mulf(c->fwd, v3dot(r->dir, c->fwd)));
    w_perp = v3sub(w, v3mulf(c->fwd, v3dot(w, c->fwd)));
    ABC[0] = v3dot(v_perp, v_perp);
    ABC[1] = 2.f * v3dot(v_perp, w_perp);
    ABC[2] = v3dot(w_perp, w_perp) - c->r * c->r;
}

static t_hit_result ray_cylinder(t_cylinder *c, t_ray *r)
{
    t_hit_result ret;
	float ABC[3];
    float d;
	float h;

	ret.t = -1.f;
	cylinder_quadratic(ABC, c, r);
	d = ABC[1]*ABC[1] - 4.f*ABC[0]*ABC[2];
    if (d < 0.f || ABC[0] == 0.f)
        return ret;
    d = sqrtf(d);
    ret.t = (-ABC[1] - d) / (2.f*ABC[0]);
	ret.p = v3add(r->or, v3mulf(r->dir, ret.t));
	h= v3dot(v3sub(ret.p, c->pos), c->fwd);
	if (ret.t < 0.f || fabs(h) > c->h / 2.f)
	{
		ret.t = (-ABC[1] + d) / (2.f*ABC[0]);
		ret.p = v3add(r->or, v3mulf(r->dir, ret.t));
		h = v3dot(v3sub(ret.p, c->pos), c->fwd);
		if (ret.t < 0.f || fabs(h) > c->h / 2.f)
			return ((t_hit_result){.t = -1.f});
	}
    ret.n = v3normalize(v3sub(v3sub(ret.p, c->pos), v3mulf(c->fwd, h)));
    return ret;
}


t_hit_result ray_cap_cylinder(t_cylinder *c, t_ray *r)
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


t_hit_result ray_sphere(t_sphere *s, t_ray *r)
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
	return (ret);
}