#include "minirt.h"

void	parse_ambient(t_state *state, char *line)
{
	if (state->flags & FLAG_AMBIENT_FOUND)
		minirt_error(state, "Ambient defined more than once\n");
	state->flags |= FLAG_AMBIENT_FOUND;
	++line;
	state->ambient.ratio = parse_range_float(state, &line, 0.0, 1.0);
	state->ambient.color = parse_color(state, &line);
}

void	parse_camera(t_state *state, char *line)
{
	if (state->flags & FLAG_CAMERA_FOUND)
		minirt_error(state, "Camera defined more than once\n");
	state->flags |= FLAG_CAMERA_FOUND;
	++line;
	state->camera.pos = parse_vec3(state, &line);
	state->camera.fwd = parse_orientation(state, &line);
	state->camera.fov = parse_range_float(state, &line, 0.f, 180.f)
			* PI / 180.f;
}

void	check_state(t_state *state)
{
	if (!(state->flags & FLAG_CAMERA_FOUND))
		minirt_error(state, "Camera not defined\n");
}

int	parse_file(t_state *state, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (ft_strncmp("A ", line, 2) == 0)
			parse_ambient(state, line);
		else if (ft_strncmp("C ", line, 2) == 0)
			parse_camera(state, line);
		else if (ft_strncmp("l ", line, 2) == 0)
			parse_light(state, line);
		else if (ft_strncmp("sp ", line, 3) == 0)
			parse_sphere(state, line);
		else if (ft_strncmp("pl ", line, 3) == 0)
			parse_plane(state, line);
		else if (ft_strncmp("cy ", line, 3) == 0)
			parse_cylinder(state, line);
		else if (*line == '#')
		{}
		else if (line[0] && line[0] != '\n')
		{
			free(line);
			minirt_error(state, "Invalid scene object\n");
		}
		free(line);
		line = get_next_line(fd);
	}
	return (1);
}

