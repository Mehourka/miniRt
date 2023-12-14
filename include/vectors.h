#ifndef VECTORS_H
#define VECTORS_H

typedef union s_vec3
{
		struct {
			double x;
			double y;
			double z;
		};
		double cord[3];
} t_vec3;

typedef t_vec3 t_pt3;

t_vec3 *ft_vec3_create(double x, double y, double z);
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