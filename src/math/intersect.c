#include "minirt.h"

double	ft_intersect_sphere(t_sphere sphere, t_ray ray)
{
	double	res;
	t_vec3	oc;
	double	a;
	double	b;
	double	c;

	oc = ft_vec3_minus(ray.ori, sphere.ori);
	a = ft_vec3_dot(ray.dir, ray.dir);
	b = ft_vec3_dot(ft_vec3_scal_prod(ray.dir, 2.0), oc);
	c = ft_vec3_dot(oc, oc) - pow(sphere.r, 2);
	c = b * b - 4 * a * c;
	if (c < 0 || a == 0)
		return (-1);
	res = (-b - sqrt(c)) / (2.0 * a);
	if (res > 0)
		return (res);
	return ((-b + sqrt(c)) / (2.0 * a));
}

/*
	brief: compute the intersection of a ray with a plane 
	and return the signed distance
*/
double	ft_intersect_plane(t_plane plane, t_ray ray)
{
	double	denom;
	double	numer;

	denom = ft_vec3_dot(ray.dir, plane.dir);
	if (denom == 0)
		return (-1);
	numer = ft_vec3_dot(
			ft_vec3_minus(plane.ori, ray.ori), plane.dir);
	return (numer / denom);
}

/*
	Checks if a ray intersects a cylinder centered at the origin
	and extending along the y axis
*/
double	ft_intersect_normalized_cylinder(t_cylinder cylinder, t_ray r)
{
	double	a;
	double	b;
	double	c;
	double	t;
	double	h;

	a = (r.dir.x * r.dir.x) + (r.dir.z * r.dir.z);
	b = 2 * ((r.ori.x * r.dir.x) + (r.ori.z * r.dir.z));
	c = (r.ori.x * r.ori.x) + (r.ori.z * r.ori.z) - (cylinder.r * cylinder.r);
	c = b * b - (4 * a * c);
	if (c <= 0)
		return (-1);
	t = (-b - sqrt(c)) / (2 * a);
	h = ft_ray_project(r, t).y;
	if (fabs(h) < cylinder.longueur / 2 && t > 0)
		return (t);
	t = (-b + sqrt(c)) / (2 * a);
	h = ft_ray_project(r, t).y;
	if (fabs(h) < cylinder.longueur / 2)
		return (t);
	return (-1);
}

double	ft_intersect_cylinder(t_cylinder cylinder, t_ray ray)
{
	t_ray	nray;
	double	t;

	nray = ft_ray_transform(ray, cylinder.inverse_transfrom, cylinder.ori);
	t = ft_intersect_normalized_cylinder(cylinder, nray);
	return (t);
}

double	ft_intersect_cone(t_cone cone, t_ray r)
{
	double			t;
	double			h;
	double			a;
	double			b;
	double			c;

	r = ft_ray_transform(r, cone.inverse_transfrom, cone.ori);
	t = tan(ft_deg_to_rad(cone.angle));
	a = r.dir.x * r.dir.x + r.dir.z * r.dir.z - t * t * r.dir.y * r.dir.y;
	b = 2 * (r.ori.x * r.dir.x + r.ori.z * r.dir.z - t * t * r.ori.y * r.dir.y);
	c = r.ori.x * r.ori.x + r.ori.z * r.ori.z - t * t * r.ori.y * r.ori.y;
	c = b * b - (4 * a * c);
	if (c <= 0)
		return (-1);
	t = (-b - sqrt(c)) / (2 * a);
	h = ft_ray_project(r, t).y;
	if (t > 0 && h > 0 && h < cone.h)
		return (t);
	t = (-b + sqrt(c)) / (2 * a);
	h = ft_ray_project(r, t).y;
	if (t > 0 && h > 0 && h < cone.h)
		return (t);
	return (-1);
}
