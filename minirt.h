#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <float.h>
# include <math.h>

# include "libs/minilibx-linux/mlx.h"
# include "libs/libft/libft.h"

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;


typedef struct s_ambient
{
	t_color	color;
	float	ratio;
}	t_ambient;

typedef struct s_camera
{
	t_vec3	pos;
	t_vec3	fwd;
	float	fov;
}	t_camera;

typedef struct s_light
{
	t_vec3	pos;
	t_color	color;
	float	brightness;
}	t_light;

typedef struct s_sphere
{
	t_vec3	pos;
	float	d;
	t_color	color;
}	t_sphere;

typedef struct s_plane
{
	t_vec3	pos;
	t_vec3	normal;
	t_color	color;
}	t_plane;

typedef struct s_sphere_arr
{
	t_sphere		*arr;
	unsigned int	count;
	unsigned int	cap;
}	t_sphere_arr;

typedef struct s_plane_arr
{
	t_plane			*arr;
	unsigned int	count;
	unsigned int	cap;
}	t_plane_arr;

typedef struct s_state
{
	t_ambient		ambient;
	t_camera		camera;
	t_light			light;
	t_sphere_arr	spheres;
	t_plane_arr		planes;
    void    		*mlx;
    void    		*win;
}   t_state;


void	minirt_cleanup(t_state *state);
void	minirt_error(t_state *state, char *message);

char	ft_atoc(char **s);
float	ft_atof(char **s);
float	parse_range_float(t_state *state, char **line, float min, float max);

t_color	parse_color(t_state *state, char **line);
t_vec3	parse_vec3(t_state *state, char **line);
t_vec3	parse_orientation(t_state *state, char **line);

int		parse_file(t_state *state, int fd);
void	parse_ambient(t_state *state, char *line);
void	parse_camera(t_state *state, char *line);
void	parse_light(t_state *state, char *line);

void	parse_sphere(t_state *state, char *line);
void	parse_plane(t_state *state, char *line);

void	sphere_arr_add(t_state *s, t_sphere n);
void	plane_arr_add(t_state *s, t_plane n);

float	v3dot(t_vec3 a, t_vec3 b);

#endif 
