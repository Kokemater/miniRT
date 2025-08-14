#include <stdio.h>
#include <math.h>
#include "../minirt.h"

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

float v3dot(t_vec3 a, t_vec3 b)
{
    return (a.x * b.x + a.y *b.y + a.z *b.z);
}
float v3lenght(t_vec3 a)
{

    return (sqrtf(v3dot(a,a)));
}

t_vec3 v3normalize(t_vec3 a)
{
    return (v3mulf(a, 1/(v3lenght(a))));
}

t_hit_result ray_sphere(t_sphere *s, t_ray *r)
{
    t_hit_result ret;
    t_vec3 c_q = v3sub(s->center, r->or);
    float abc[3];
    float abc[0] = v3dot(r->dir, r->dir);
    float abc[1] = v3dot(v3mulf(r->dir, -2.0), c_q);
    float abc[2] = v3dot(c_q, c_q) * v3dot(c_q, c_q) - s->r *s->r;
    float discriminant = abc[1]*abc[1] - 4*abc[0]*abc[2];
    if (discriminant < 0)
    {
        ret.t = -1;
    } else
    {
        ret.t =  (-abc[1] - sqrtf(discriminant) ) / (2.0*abc[0]);
        ret.p = v3add(r->or ,v3mulf(r->dir, ret.t));
        ret.n = v3normalize(v3sub(ret.p, s->center));
    }
    return (ret);
}


int main() {
    // Sphere center and radius
    double cx = 0.0, cy = 0.0, cz = 0.0;
    double r = 5.0;

    return 0;
}
