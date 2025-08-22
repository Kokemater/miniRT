#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <float.h>
# include <math.h>

# include "libs/minilibx-linux/mlx.h"
# include "libs/libft/libft.h"

# define WIN_WIDTH  1024
# define WIN_HEIGHT 1024

# define PI 3.14159265358979323846

# define KEY_ESC 65307

# define FLAG_CAMERA_FOUND (1 << 0)
# define FLAG_AMBIENT_FOUND (1 << 1)
# define FLAG_LIGHT_FOUND (1 << 2)

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
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;

typedef struct s_hit_result
{
	t_vec3	p;
	t_vec3	n;
	t_color c;
	float	t;
}	t_hit_result;

typedef struct s_ambient
{
	t_color	color;
	float	ratio;
}	t_ambient;

typedef struct s_camera
{
	t_vec3	pos;
	t_vec3	fwd;
	t_vec3	up;
	t_vec3	right;
	float	fov;
	float	vw;
	float	vh;
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
	float	r;
	t_color	color;
}	t_sphere;

typedef struct s_plane
{
	t_vec3	pos;
	t_vec3	normal;
	t_color	color;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3	pos;
	t_vec3	fwd;
	float	r;
	float	h;
	t_color	color;
}	t_cylinder;

typedef struct s_light_arr
{
	t_light		*arr;
	unsigned int	count;
	unsigned int	cap;
}	t_light_arr;

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

typedef struct s_cylinder_arr
{
	t_cylinder		*arr;
	unsigned int	count;
	unsigned int	cap;
}	t_cylinder_arr;

typedef struct s_image
{ void	*handle; char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_state
{
	t_ambient		ambient;
	t_camera		cam;
	t_light_arr		lights;
	t_sphere_arr		spheres;
	t_plane_arr		planes;
	t_cylinder_arr		cylinders;
	t_image    		img;
	void    		*mlx;
	void    		*win;
	unsigned int		flags;
	char			*fline;
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
void	check_state(t_state *state);

void	parse_sphere(t_state *state, char *line);
void	parse_plane(t_state *state, char *line);
void	parse_cylinder(t_state *state, char *line);

void	sphere_arr_add(t_state *s, t_sphere n);
void	plane_arr_add(t_state *s, t_plane n);
void	cylinder_arr_add(t_state *s, t_cylinder n);
void	light_arr_add(t_state *s, t_light n);

void	minirt_create_img(t_state *state);
void	img_put_pixel(t_image *img, unsigned int x, unsigned int y,
		t_color color);

float	v3dot(t_vec3 a, t_vec3 b);
t_vec3	v3cross(t_vec3 a, t_vec3 b);
t_vec3	v3norm(t_vec3 a);
t_vec3	v3sub(t_vec3 a, t_vec3 b);
t_vec3	v3add(t_vec3 a, t_vec3 b);
t_vec3	v3mulf(t_vec3 a, float f);
float	v3length2(t_vec3 a);

t_color	colormulf(t_color a, float f);
t_color	colormul(t_color a, t_color b);
t_color	coloradd(t_color a, t_color b);

t_hit_result	intersect_scene(t_ray *ray, t_state *state);
t_hit_result	ray_cap_cylinder(t_cylinder *c, t_ray *r);
t_hit_result	ray_plane(t_plane *p, t_ray *r);
t_hit_result	ray_sphere(t_sphere *s, t_ray *r);

t_color	ray_color(t_ray *ray, t_state *state);
t_color	lighting(t_state *state, t_hit_result hit);

#endif 
