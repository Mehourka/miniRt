#ifndef RENDER_H
# define RENDER_H

#include "minirt.h"

typedef struct s_viewport
{
	t_vec3	upper_left_corner;
	t_vec3	u;
	t_vec3	v;
	t_vec3	du;
	t_vec3	dv;
	t_vec3	focal_length;
}	t_viewport;

typedef struct s_amb_light
{
	double intensity;
	t_color color;
}	t_amb_light;

typedef struct s_light
{
	double	intensity;
	t_vec3	ori;
	t_color	color;
}	t_light;


int get_rgba(int r, int g, int b, int a);
int norm_rgba(float r, float g, float b, float a);
void draw_gradient(t_data *data);
void gen_p3_image(t_data *data);
void compute_viewport();

#endif