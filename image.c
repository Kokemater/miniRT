#include "minirt.h"

void	minirt_create_img(t_state *state)
{
	state->img.handle = mlx_new_image(state->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!state->img.handle)
		minirt_error(state, "Could not create image\n");
	state->img.addr = mlx_get_data_addr(state->img.handle,
			&state->img.bpp,
			&state->img.line_length,
			&state->img.endian);
	if (!state->img.addr)
		minirt_error(state, "Could not get image data address\n");
}

void	img_put_pixel(t_image *img, unsigned int x, unsigned int y,
		t_color color)
{
	char			*dst;
	unsigned int	c;

	c = (color.r << 16) + (color.g << 8) + color.b;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = c;
}
