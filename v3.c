#include "minirt.h"

float v3lenght(t_vec3 a)
{

    return (sqrtf(v3dot(a,a)));
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

t_vec3 v3normalize(t_vec3 a)
{
    return (v3mulf(a, 1/(v3lenght(a))));
}
