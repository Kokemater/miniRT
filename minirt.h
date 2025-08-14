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

typedef struct s_ray
{
	t_vec3	or;
	t_vec3	dir;
}	t_ray;

typedef struct s_color
{
	char	r;
	char	g;
	char	b;
}	t_color;

typedef struct s_sphere
{
	t_vec3 center;
	t_color color;
	float	r;
} t_sphere;

typedef struct s_plane
{
	t_vec3 norm;
	t_vec3 p;
	t_color color;
} t_plane;

typedef struct s_cylinder
{
	t_vec3 center;
	t_vec3 dir;
	t_color color;
	float	height;
	float	r;
} t_cylinder;


typedef struct s_hit_result
{
	t_vec3 p;
	t_vec3 n;
	float	t;
} t_hit_result;
#endif 
