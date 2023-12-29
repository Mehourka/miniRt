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

typedef t_vec3 t_color3;
typedef struct s_ray
{
	t_pt3	orig;
	t_vec3	dir;
}	t_ray;

void	ft_vec3_print(t_vec3 u);
t_vec3	ft_vec3_create(double x, double y, double z);
t_vec3	ft_vec3_add(t_vec3 u, t_vec3 v);
t_vec3	ft_vec3_minus(t_vec3 u, t_vec3 v);
t_vec3	ft_vec3_add_scal(t_vec3 u, double k);
t_vec3	ft_vec3_scal_prod(t_vec3 u, double k);
t_vec3	ft_vec3_cross_prod(t_vec3 u, t_vec3 v);
t_vec3	ft_vec3_normalize(t_vec3 u);
double	ft_vec3_mod(t_vec3 u);
double	ft_vec3_dot(t_vec3 u, t_vec3 v);
double	ft_vec3_get_angle(t_vec3 u, t_vec3 v);

t_ray ft_ray_create(t_pt3 origine, t_vec3 direction);
t_pt3 ft_ray_project(t_ray ray, double t);

#endif