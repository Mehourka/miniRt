#ifndef RENDER_H
# define RENDER_H

#include "minirt.h"

int get_rgba(int r, int g, int b, int a);
int norm_rgba(float r, float g, float b, float a);
void draw_gradient(t_data *data);
void gen_p3_image(t_data *data);

#endif