/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutragu <jbutragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:53:22 by jbutragu          #+#    #+#             */
/*   Updated: 2025/08/22 16:19:28 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	colormulf(t_color a, float f)
{
	t_color	ret;

	ret.r = a.r * f;
	ret.g = a.g * f;
	ret.b = a.b * f;
	return (ret);
}

static unsigned char	cclamp(unsigned int c)
{
	if (c > 255)
		return (255);
	return (c);
}

t_color	colormul(t_color a, t_color b)
{
	t_color	ret;

	ret.r = cclamp(a.r * (b.r / (float)255));
	ret.g = cclamp(a.g * (b.g / (float)255));
	ret.b = cclamp(a.b * (b.b / (float)255));
	return (ret);
}

t_color	coloradd(t_color a, t_color b)
{
	t_color	ret;

	ret.r = cclamp(a.r + b.r);
	ret.g = cclamp(a.g + b.g);
	ret.b = cclamp(a.b + b.b);
	return (ret);
}
