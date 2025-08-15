#include "minirt.h"

void	parse_sphere(t_state *state, char *line)
{
	t_sphere	sp;

	line += 2;
	sp.pos = parse_vec3(state, &line);
	sp.d = parse_range_float(state, &line, 0.0, INFINITY);
	sp.color = parse_color(state, &line);
	sphere_arr_add(state, sp);
}

