/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutragu <jbutragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:39:52 by jbutragu          #+#    #+#             */
/*   Updated: 2025/08/22 16:04:27 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	parse_color(t_state *state, char **line)
{
	t_color	ret;

	while (**line == ' ')
		++(*line);
	if (!ft_isdigit(**line))
		minirt_error(state, "Invalid color format\n");
	ret.r = ft_atoc(line);
	if (**line != ',')
		minirt_error(state, "Invalid color format\n");
	++(*line);
	while (**line == ' ')
		++(*line);
	if (!ft_isdigit(**line))
		minirt_error(state, "Invalid color format\n");
	ret.g = ft_atoc(line);
	if (**line != ',')
		minirt_error(state, "Invalid color format\n");
	++(*line);
	while (**line == ' ')
		++(*line);
	if (!ft_isdigit(**line))
		minirt_error(state, "Invalid color format\n");
	ret.b = ft_atoc(line);
	return (ret);
}

t_vec3	parse_vec3(t_state *state, char **line)
{
	t_vec3	ret;

	ret.x = parse_range_float(state, line, -INFINITY, INFINITY);
	if (**line != ',')
		minirt_error(state, "Invalid vec3 format\n");
	++(*line);
	ret.y = parse_range_float(state, line, -INFINITY, INFINITY);
	if (**line != ',')
		minirt_error(state, "Invalid vec3 format\n");
	++(*line);
	ret.z = parse_range_float(state, line, -INFINITY, INFINITY);
	return (ret);
}

t_vec3	parse_orientation(t_state *state, char **line)
{
	t_vec3	ret;

	ret = parse_vec3(state, line);
	if (fabs(v3dot(ret, ret) - 1.f) > FLT_EPSILON)
		minirt_error(state, "Orientation is not normalized\n");
	return (ret);
}
