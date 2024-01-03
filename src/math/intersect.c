#include "minirt.h"

double ft_intersect_sphere(t_sphere sphere, t_ray ray)
{
	static int i = 0;
	double res;

	t_vec3 oc = ft_vec3_minus(ray.orig, sphere.ori);

	// TODO: optimize by replacing dot products with len*len
	double a = ft_vec3_dot(ray.dir, ray.dir);
	double b = ft_vec3_dot(
		ft_vec3_scal_prod(ray.dir, 2.0),
		oc);
	double c =	ft_vec3_dot(oc, oc) - pow(sphere.r, 2);
	double discriminant = b*b - 4*a*c;
	if (discriminant < 0 || a == 0)
		return (-1);
	res = (-b - sqrt(discriminant)) / (2.0 * a);
	if (res > 0)
		return (res);
	return (-b + sqrt(discriminant)) / (2.0 * a);
}

/*
	brief: compute the intersection of a ray with a plane and return the signed distance
*/
double ft_intersect_plane(t_plane plane, t_ray ray)
{
	double denom = ft_vec3_dot(ray.dir, plane.dir);
	// If no intersection or line inside plane, do not render
	if (denom == 0)
		return (-1);
	double numer = ft_vec3_dot(
		ft_vec3_minus(plane.ori, ray.orig),
		plane.dir
	);
	return (numer / denom);
}

double ft_intersect_cylinder(t_cylinder cylinder, t_ray ray)
{
	return (-1);
}

double ft_hit_object(t_obj obj, t_ray ray)
{
	if (OBJ_SPHERE == obj.obj_type)
	{
		return (ft_intersect_sphere(obj.sphere, ray));
	}
	if (OBJ_PLANE == obj.obj_type)
	{
		return (ft_intersect_plane(obj.plane, ray));
	}
	if (OBJ_CYLINDER == obj.obj_type)
	{
		return (ft_intersect_cylinder(obj.cylinder, ray));
	}

	return (-1);
}