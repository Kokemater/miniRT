/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutragu <jbutragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:40:05 by jbutragu          #+#    #+#             */
/*   Updated: 2025/08/22 16:08:00 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	state->cam.pos = parse_vec3(state, &line);
	state->cam.fwd = parse_orientation(state, &line);
	state->cam.fov = parse_range_float(state, &line, 0.f, 180.f)
		* PI / 180.f;
}

void	parse_light(t_state *state, char *line)
{
	t_light	l;

	if (state->flags & FLAG_LIGHT_FOUND)
		minirt_error(state, "Light defined more than once\n");
	state->flags |= FLAG_LIGHT_FOUND;
	++line;
	l.pos = parse_vec3(state, &line);
	l.brightness = parse_range_float(state, &line, 0.0, 1.0);
	l.color = parse_color(state, &line);
	light_arr_add(state, l);
}

void	check_state(t_state *state)
{
	if (!(state->flags & FLAG_CAMERA_FOUND))
		minirt_error(state, "Camera not defined\n");
}

int	parse_file(t_state *s, int fd)
{
	s->fline = get_next_line(fd);
	while (s->fline)
	{
		if (ft_strncmp("A ", s->fline, 2) == 0)
			parse_ambient(s, s->fline);
		else if (ft_strncmp("C ", s->fline, 2) == 0)
			parse_camera(s, s->fline);
		else if (ft_strncmp("L ", s->fline, 2) == 0
			|| ft_strncmp("l ", s->fline, 2) == 0)
			parse_light(s, s->fline);
		else if (ft_strncmp("sp ", s->fline, 3) == 0)
			parse_sphere(s, s->fline);
		else if (ft_strncmp("pl ", s->fline, 3) == 0)
			parse_plane(s, s->fline);
		else if (ft_strncmp("cy ", s->fline, 3) == 0)
			parse_cylinder(s, s->fline);
		else if (s->fline[0] && s->fline[0] != '\n')
			minirt_error(s, "Invalid scene object\n");
		free(s->fline);
		s->fline = get_next_line(fd);
	}
	return (1);
}
