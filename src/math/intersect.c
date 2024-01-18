#include "minirt.h"

double	ft_intersect_sphere(t_sphere sphere, t_ray ray)
{
	double	res;
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	oc = ft_vec3_minus(ray.ori, sphere.ori);
	// TODO: optimize by replacing dot products with len*len
	a = ft_vec3_dot(ray.dir, ray.dir);
	b = ft_vec3_dot(ft_vec3_scal_prod(ray.dir, 2.0), oc);
	c = ft_vec3_dot(oc, oc) - pow(sphere.r, 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0 || a == 0)
		return (-1);
	res = (-b - sqrt(discriminant)) / (2.0 * a);
	if (res > 0)
		return (res);
	return ((-b + sqrt(discriminant)) / (2.0 * a));
}

/*
	brief: compute the intersection of a ray with a plane and return the signed distance
*/
double	ft_intersect_plane(t_plane plane, t_ray ray)
{
	double	denom;
	double	numer;

	denom = ft_vec3_dot(ray.dir, plane.dir);
	// If no intersection or line inside plane, do not render
	if (denom == 0)
		return (-1);
	numer = ft_vec3_dot(
			ft_vec3_minus(plane.ori, ray.ori), plane.dir);
	return (numer / denom);
}

/*Checks if a ray intersects a cylinder centered at the origin, and extending along the y axis*/
double	ft_intersect_normalized_cylinder(t_cylinder cylinder, t_ray r)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t1;
	double	t2;
	double	h1;
	double	h2;

	a = (r.dir.x * r.dir.x) + (r.dir.z * r.dir.z);
	b = 2 * ((r.ori.x * r.dir.x) + (r.ori.z * r.dir.z));
	c = (r.ori.x * r.ori.x) + (r.ori.z * r.ori.z) - (cylinder.r * cylinder.r);
	//ft_print_vec3(r.dir);
	//ft_print_vec3(r.ori);
	discriminant = b * b - (4 * a * c);
	if (discriminant <= 0)
		return (-1);
	t1 = (-b - sqrt(discriminant)) / (2 * a);
	t2 = (-b + sqrt(discriminant)) / (2 * a);
	// Check if intersection is within cylinde height
	h1 = ft_ray_project(r, t1).y;
	h2 = ft_ray_project(r, t2).y;
	if (fabs(h1) < cylinder.longueur / 2 && t1 > 0)
		return (t1);
	else if (fabs(h2) < cylinder.longueur / 2)
		return (t2);
	return (-1);
}

double	ft_intersect_cylinder(t_cylinder cylinder, t_ray ray)
{
	t_ray	nray;
	double	t;
	// Create transform matrix
	// Cylinder basis as a matrix
	// Project the ray into the cylinder local coordinates
	nray = ft_ray_transform(ray, cylinder.inverse_transfrom, cylinder.ori); //mets tout a 0
	// check if reprojected ray intersects the normalized cyliinder
	t = ft_intersect_normalized_cylinder(cylinder, nray);
	return (t);
}

double	ft_hit_object(t_obj obj, t_ray ray)
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
