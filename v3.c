/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutragu <jbutragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:32:31 by jbutragu          #+#    #+#             */
/*   Updated: 2025/08/21 12:33:37 by jbutragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	v3length2(t_vec3 a)
{
	return (v3dot(a, a));
}

t_vec3	v3add(t_vec3 a, t_vec3 b)
{
	t_vec3	ret;

	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;
	return (ret);
}

t_vec3	v3sub(t_vec3 a, t_vec3 b)
{
	t_vec3	ret;

	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;
	return (ret);
}

t_vec3	v3norm(t_vec3 a)
{
	return (v3mulf(a, 1 / sqrtf(v3length2(a))));
}
