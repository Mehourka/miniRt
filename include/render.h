#ifndef RENDER_H
# define RENDER_H

#include "vectors.h"
#include "objects.h"

typedef struct s_viewport
{
	t_vec3	upper_left_corner;
	t_vec3	u;
	t_vec3	v;
	t_vec3	du;
	t_vec3	dv;
	t_vec3	focal_length;
}	t_viewport;

typedef struct s_hit_point
{
	int		f_valid;
	t_obj		*object;
	t_pt3		pos;
	t_vec3		normal;
	double		distance;
	int		f_inside;
	t_color3	color;
}	t_hit_point;

typedef struct s_cam
{
	t_vec3	ori;
	t_vec3	dir;
	t_vec3	vup;
	double	angle;

	// Viewport data
	t_vec3	du;
	t_vec3	dv;
	t_pt3	pixel00_pos;

}	t_cam;

int get_rgba(int r, int g, int b, int a);
int norm_rgba(float r, float g, float b, float a);
void draw_gradient();

t_ray	ft_compute_ray(t_cam cam, int row, int col);
t_hit_point ft_get_closest_hitpoint(t_obj *object_list, int object_count, t_ray ray);
t_color3 ft_get_shade(t_hit_point hpt);

#endif