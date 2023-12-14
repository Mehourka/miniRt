#ifndef HEADER_H
#define HEADER_H

#include "libft.h"
#include "math.h"
#include "stdio.h"
#include <MLX42/MLX42.h>

#define WIDTH 256
#define HEIGHT 256

typedef union s_vec3
{
		struct {
			double x;
			double y;
			double z;
		};
		double cord[3];
} t_vec3;

typedef union u_color
{
	struct {
		short r;
		short g;
		short b;
	};
	int val;
}	t_color;

typedef struct s_data
{
	mlx_t *mlx;
	mlx_image_t *image;
} t_data;

t_data *get_data();

t_vec3 *ft_create_vec3(double x, double y, double z);
t_vec3 *ft_vec3_add(t_vec3 *u, t_vec3 *v);
t_vec3 *ft_vec3_minus(t_vec3 *u, t_vec3 *v);
t_vec3 *ft_vec3_scal_prod(t_vec3 *u, double k);
double ft_vec3_mod(t_vec3 *u);
t_vec3 *ft_vec3_normalize(t_vec3 *u);
void ft_vec3_print(t_vec3 *u);
double ft_vec3_dot(t_vec3 *u, t_vec3 *v);
t_vec3 *ft_vec3_cross_prod(t_vec3 *u, t_vec3 *v);
double ft_vec3_get_angle(t_vec3 *u, t_vec3 *v);

#endif