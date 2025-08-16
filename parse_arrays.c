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

void	parse_plane(t_state *state, char *line)
{
	t_plane	pl;

	line += 2;
	pl.pos = parse_vec3(state, &line);
	pl.normal = parse_orientation(state, &line);
	pl.color = parse_color(state, &line);
	plane_arr_add(state, pl);
}

void	parse_cylinder(t_state *state, char *line)
{
	t_cylinder	cy;

	line += 2;
	cy.pos = parse_vec3(state, &line);
	cy.fwd = parse_orientation(state, &line);
	cy.d = parse_range_float(state, &line, 0.f, INFINITY);
	cy.h = parse_range_float(state, &line, 0.f, INFINITY);
	cy.color = parse_color(state, &line);
	cylinder_arr_add(state, cy);
}
