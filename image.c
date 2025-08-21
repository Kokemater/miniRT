/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbutragu <jbutragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:54:24 by jbutragu          #+#    #+#             */
/*   Updated: 2025/08/21 19:39:47 by dmoraled         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	minirt_create_img(t_state *state)
{
	state->img.data = malloc(sizeof(t_color) * WIN_WIDTH * WIN_HEIGHT);
	if (!state->img.data)
		minirt_error(state, "Out of memory");
	glCreateTextures(GL_TEXTURE_2D, 1, &state->img.handle);
	glTextureStorage2D(state->img.handle, 1, GL_RGB8, WIN_WIDTH, WIN_HEIGHT);

	glTextureParameteri(state->img.handle, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(state->img.handle, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void	img_put_pixel(t_image *img, unsigned int x, unsigned int y,
		t_color color)
{
	img->data[(WIN_HEIGHT - y - 1) * WIN_WIDTH + x] = color;
}
