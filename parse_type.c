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

float	ft_atof(char **s)
{
	float	r;
	int		p;
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
	p = 1;
	while (ft_isdigit(**s))
	{
		r = (r * 10.0) + (**s - '0');
		++(*s);
	}
	if (**s == '.')
	{
		++(*s);
		while (ft_isdigit(**s))
		{
			p *= 10;
			r += (**s - '0') * (1 / (float)p);
			++(*s);
		}
	}
	return (r * sign);
}

float	parse_range_float(t_state *state, char **line, float min, float max)
{
	float	f;

	f = ft_atof(line);
	if (f < min - FLT_EPSILON)
		minirt_error(state, "Float out of range\n");
	if (f > max + FLT_EPSILON)
		minirt_error(state, "Float out of range\n");
	return (f);
}

