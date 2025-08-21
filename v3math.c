/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3math.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutragu <jbutragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:03:12 by jbutragu          #+#    #+#             */
/*   Updated: 2025/08/21 12:04:32 by jbutragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	v3dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	v3cross(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

t_vec3	v3mulf(t_vec3 a, float f)
{
	t_vec3	ret;

	ret.x = a.x * f;
	ret.y = a.y * f;
	ret.z = a.z * f;
	return (ret);
}
