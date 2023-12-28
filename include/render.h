#ifndef RENDER_H
# define RENDER_H

#include "vectors.h"

typedef struct s_viewport
{
	t_vec3	upper_left_corner;
	t_vec3	u;
	t_vec3	v;
	t_vec3	du;
	t_vec3	dv;
	t_vec3	focal_length;
}	t_viewport;

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
void gen_p3_image();
void compute_viewport();
void	ft_render_image();

#endif