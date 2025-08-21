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

void	plane_arr_add(t_state *s, t_plane n)
{
	t_plane	*tmp;

	if (s->planes.count == s->planes.cap)
	{
		s->planes.cap = s->planes.cap * 2 + 1;
		tmp = malloc(sizeof(t_plane) * s->planes.cap);
		if (!tmp)
			minirt_error(s, "Out of memory\n");
		ft_memcpy(tmp, s->planes.arr, sizeof(t_plane) * s->planes.count);
		if (s->planes.arr)
			free(s->planes.arr);
		s->planes.arr = tmp;
	}
	s->planes.arr[s->planes.count] = n;
	++s->planes.count;
}

void	cylinder_arr_add(t_state *s, t_cylinder n)
{
	t_cylinder	*tmp;

	if (s->cylinders.count == s->cylinders.cap)
	{
		s->cylinders.cap = s->cylinders.cap * 2 + 1;
		tmp = malloc(sizeof(t_cylinder) * s->cylinders.cap);
		if (!tmp)
			minirt_error(s, "Out of memory\n");
		ft_memcpy(tmp, s->cylinders.arr, sizeof(t_cylinder) * s->cylinders.count);
		if (s->cylinders.arr)
			free(s->cylinders.arr);
		s->cylinders.arr = tmp;
	}
	s->cylinders.arr[s->cylinders.count] = n;
	++s->cylinders.count;
}

void	light_arr_add(t_state *s, t_light n)

{
	t_light	*tmp;

	if (s->lights.count == s->lights.cap)
	{
		s->lights.cap = s->lights.cap * 2 + 1;
		tmp = malloc(sizeof(t_light) * s->lights.cap);
		if (!tmp)
			minirt_error(s, "Out of memory\n");
		ft_memcpy(tmp, s->lights.arr, sizeof(t_light) * s->lights.count);
		if (s->lights.arr)
			free(s->lights.arr);
		s->lights.arr = tmp;
	}
	s->lights.arr[s->lights.count] = n;
	++s->lights.count;
}
