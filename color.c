#include "minirt.h"

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
