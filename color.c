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
    int     r;
    int     g;
    int     bl;

    r = a.r + b.r;
    if (r > 255)
        r = 255;
    g = a.g + b.g;
    if (g > 255)
        g = 255;
    bl = a.b + b.b;
    if (bl > 255)
        bl = 255;
    ret.r = r;
    ret.g = g;
    ret.b = bl;
    return (ret);
}
