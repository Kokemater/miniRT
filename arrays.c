#include "minirt.h"

void	sphere_arr_add(t_state *s, t_sphere n)
{
	t_sphere	*tmp;

	if (s->spheres.count == s->spheres.cap)
	{
		s->spheres.cap = s->spheres.cap * 2 + 1;
		tmp = malloc(sizeof(t_sphere) * s->spheres.cap);
		if (!tmp)
			minirt_error(s, "Out of memory\n");
		ft_memcpy(tmp, s->spheres.arr, sizeof(t_sphere) * s->spheres.count);
		if (s->spheres.arr)
			free(s->spheres.arr);
		s->spheres.arr = tmp;
	}
	s->spheres.arr[s->spheres.count] = n;
	++s->spheres.count;
}

