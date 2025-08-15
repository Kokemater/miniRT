#include "minirt.h"

void	parse_ambient(t_state *state, char *line)
{
	++line;
	state->ambient.ratio = parse_range_float(state, &line, 0.0, 1.0);
	state->ambient.color = parse_color(state, &line);
}

void	parse_camera(t_state *state, char *line)
{
	++line;
	state->camera.pos = parse_vec3(state, &line);
	state->camera.fwd = parse_orientation(state, &line);
	state->camera.fov = parse_range_float(state, &line, 0.f, 180.f);
}

void	parse_light(t_state *state, char *line)
{
	++line;
	state->light.pos = parse_vec3(state, &line);
	state->light.brightness = parse_range_float(state, &line, 0.0, 1.0);
	state->light.color = parse_color(state, &line);
}

int	parse_file(t_state *state, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == 'A' && ft_isspace(line[1]))
			parse_ambient(state, line);
		else if (line[0] == 'C' && ft_isspace(line[1]))
			parse_camera(state, line);
		else if (line[0] == 'L' && ft_isspace(line[1]))
			parse_light(state, line);
		else if (line[0] == 's' && line[1] == 'p' && ft_isspace(line[2]))
			parse_sphere(state, line);
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

