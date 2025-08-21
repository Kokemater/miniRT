/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutragu <jbutragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:33:52 by jbutragu          #+#    #+#             */
/*   Updated: 2025/08/21 13:23:47 by jbutragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	ft_atoc(char **s)
{
	char	r;

	r = 0;
	while (**s == ' ')
		++(*s);
	while (ft_isdigit(**s))
	{
		r = (r * 10) + (**s - '0');
		++(*s);
	}
	return (r);
}

static float	ft_atof_mantissa(char **s)
{
	float	r;
	int		p;

	r = 0;
	p = 1;
	if (!ft_isdigit(**s))
		return (NAN);
	while (ft_isdigit(**s))
	{
		p *= 10;
		r += (**s - '0') * (1 / (float)p);
		++(*s);
	}
	return (r);
}

float	ft_atof(char **s)
{
	float	r;
	char	sign;

	while (**s == ' ')
		++(*s);
	sign = 1;
	if (**s == '-')
	{
		++(*s);
		sign = -1;
	}
	r = 0;
	if (!ft_isdigit(**s) && **s != '.')
		return (NAN);
	while (ft_isdigit(**s))
	{
		r = (r * 10.0) + (**s - '0');
		++(*s);
	}
	if (**s == '.')
	{
		++(*s);
		r += ft_atof_mantissa(s);
	}
	return (r * sign);
}

float	parse_range_float(t_state *state, char **line, float min, float max)
{
	float	f;

	f = ft_atof(line);
	if (isnan(f))
		minirt_error(state, "Invalid float format\n");
	if (f < min - FLT_EPSILON)
		minirt_error(state, "Float out of range\n");
	if (f > max + FLT_EPSILON)
		minirt_error(state, "Float out of range\n");
	return (f);
}
