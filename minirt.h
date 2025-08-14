#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

# include "libs/minilibx-linux/mlx.h"
# include "libs/libft/libft.h"

typedef struct s_state
{
    void    *mlx;
    void    *win;
    int     counter;
}   t_state;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_color
{
	char	r;
	char	g;
	char	b;
}	t_color;


#endif 
