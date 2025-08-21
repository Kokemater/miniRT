/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutragu <jbutragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:42:39 by jbutragu          #+#    #+#             */
/*   Updated: 2025/08/21 12:42:47 by jbutragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	shadow(t_state *state, t_vec3 p, t_light *l)
{
	t_ray			sr;
	float			lightt;
	t_hit_result	shadow;

	sr = (t_ray){.or = p, .dir = v3norm(v3sub(l->pos, p))};
	sr.or = v3add(sr.or, v3mulf(sr.dir, 0.001f));
	if (fabsf(sr.dir.x) >= fabsf(sr.dir.y)
		&& fabsf(sr.dir.x) >= fabsf(sr.dir.z))
		lightt = (l->pos.x - sr.or.x) / sr.dir.x;
	else if (fabsf(sr.dir.y) >= fabsf(sr.dir.z))
		lightt = (l->pos.y - sr.or.y) / sr.dir.y;
	else
		lightt = (l->pos.z - sr.or.z) / sr.dir.z;
	shadow = intersect_scene(&sr, state);
	return (shadow.t < lightt + 0.001f && shadow.t > 0);
}

t_color	lighting(t_state *state, t_hit_result hit)
{
	t_color			color;
	float			ndotl;
	unsigned int	i;

	i = 0;
	color = colormulf(state->ambient.color, state->ambient.ratio);
	while (i < state->lights.count)
	{
		if (shadow(state, hit.p, &state->lights.arr[i]))
			ndotl = 0;
		else
		{
			ndotl = v3dot(v3norm(
						v3sub(state->lights.arr[i].pos, hit.p)), hit.n);
			if (ndotl < 0)
				ndotl = 0;
		}
		color = coloradd(color, colormulf(
					hit.c, ndotl * state->lights.arr[i].brightness));
		++i;
	}
	return (color);
}

t_color	ray_color(t_ray *ray, t_state *state)
{
	t_hit_result	c;

	c = intersect_scene(ray, state);
	if (c.t > 0)
		return (lighting(state, c));
	return ((t_color){255, 0, 255});
}
