#include "minirt.h"

/*
	brief: get the out normal of a sphere at given point pt;
*/
t_vec3	ft_get_sphere_normal(t_sphere sphere, t_pt3 pos)
{
	t_vec3	n;

	n = ft_vec3_scal_prod(
			ft_vec3_minus(pos, sphere.ori), 1 / sphere.r);
	return (n);
}

t_vec3	ft_get_plane_normal(t_plane plane, t_pt3 pos)
{
	(void) pos;
	return (plane.dir);
}

// TODO: actually compute normal
t_vec3 ft_get_cone_normal(t_cone cone, t_pt3 pos)
{
	// Vector from cylinder center to hitpoint
	t_pt3 OH = ft_vec3_minus(pos, cone.ori);
	// Compute cone surface normal
	// Compute projection of cone axis on OH
	t_pt3 p = ft_vec3_scal_prod(OH, ft_vec3_dot(OH, cone.dir) / ft_vec3_dot(OH, OH));

	return (ft_vec3_minus(p, cone.dir));
}

t_vec3 ft_get_cylinder_normal(t_cylinder cylinder, t_pt3 pos)
{
	t_pt3	oh;
	t_pt3	p;

	// Vector from cylinder center to hitpoint
	oh = ft_vec3_minus(pos, cylinder.ori);
	// Compute hitpoint projection on cylinder dir axis
	p = ft_vec3_scal_prod(cylinder.dir, ft_vec3_dot(cylinder.dir, oh));
	return (ft_vec3_minus(oh, p));
}

t_vec3	ft_get_obj_normal(t_obj obj, t_pt3 pos)
{
	if (OBJ_SPHERE == obj.obj_type)
	{
		return (ft_get_sphere_normal(obj.sphere, pos));
	}
	if (OBJ_PLANE == obj.obj_type)
	{
		return (ft_get_plane_normal(obj.plane, pos));
	}
	// TODO : Handle cylindre normal
	if (OBJ_CYLINDER == obj.obj_type)
	{
		return (ft_get_cylinder_normal(obj.cylinder, pos));
	}

	if (OBJ_CONE == obj.obj_type)
	{
		return (ft_get_cone_normal(obj.cone, pos));
	}
	return (ft_vec3_create(0, 0, 0));
}
