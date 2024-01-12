#include "minirt.h"

t_vec3 ft_vec3_create(double x, double y, double z)
{
	t_vec3 new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_vec3 ft_vec3_add(t_vec3 u, t_vec3 v)
{
	t_vec3 new;

	new.x = u.x + v.x;
	new.y = u.y + v.y;
	new.z = u.z + v.z;
	return (new);
}

t_vec3 ft_vec3_minus(t_vec3 u, t_vec3 v)
{
	t_vec3 new;

	new.x = u.x - v.x;
	new.y = u.y - v.y;
	new.z = u.z - v.z;
	return (new);
}

/*
	brief: element-wise multiplication of vector components
*/
t_vec3 ft_vec3_elem_mult(t_vec3 u, t_vec3 v)
{
	t_vec3 w;

	w.x = u.x * v.x;
	w.y = u.y * v.y;
	w.z = u.z * v.z;
	return (w);
}

t_vec3 ft_vec3_scal_prod(t_vec3 u, double k)
{
	t_vec3 new;

	new.x = u.x *k;
	new.y = u.y *k;
	new.z = u.z *k;
	return (new);
}

double ft_vec3_mod(t_vec3 u)
{
	return (sqrt((u.x * u.x) + (u.y * u.y) + (u.z * u.z)));
}

t_vec3 ft_vec3_normalize(t_vec3 u)
{
	double mod;

	mod = ft_vec3_mod(u);
	if (mod)
		return (ft_vec3_scal_prod(u, 1 / mod));
	return (u);
}

double ft_vec3_dot(t_vec3 u, t_vec3 v)
{
	double res;

	res = (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
	return (res);
}

t_vec3 ft_vec3_cross_prod(t_vec3 u, t_vec3 v)
{
	double i;
	double j;
	double k;

	i = u.y * v.z - u.z * v.y;
	j = u.z * v.x - u.x * v.z;
	k = u.x * v.y - u.y * v.x;
	return (ft_vec3_create(i, j, k));
}

double ft_vec3_get_angle(t_vec3 u, t_vec3 v)
{
	double num;
	double denom;

	num = ft_vec3_dot(u, v);
	denom = ft_vec3_mod(u) * ft_vec3_mod(v);
	if (denom == 0)
		return (0);
	return (acos(num / denom));
}


t_ray ft_ray_create(t_pt3 origine, t_vec3 direction)
{
	t_ray ray;

	ray.ori = origine;
	ray.dir = direction;
	return (ray);
}

t_pt3 ft_ray_project(t_ray ray, double t)
{
	return (ft_vec3_add(
		ray.ori,
		ft_vec3_scal_prod(ray.dir, t)));
}

t_vec3 ft_vec3_add_scal(t_vec3 u, double k)
{
	t_vec3 new;

	new.x = u.x + k;
	new.y = u.y + k;
	new.z = u.z + k;
	return (new);
}

/*
	brief: Scales the values of a vector between 0 and 1;
*/
t_vec3 ft_vec3_cap01(t_vec3 u)
{
	// return (
		// ft_vec3_scal_prod(
			// ft_vec3_add_scal(ft_vec3_normalize(u), 1),
		//  0.5));
	u.x = ft_cap01(u.x);
	u.y = ft_cap01(u.y);
	u.z = ft_cap01(u.z);
	return (u);
}