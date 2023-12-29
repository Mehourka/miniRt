#include "minirt.h"

/*
	brief: get the out normal of a sphere at given point pt;
*/
t_vec3 ft_get_sphere_normal(t_sphere sphere, t_pt3 pos)
{
	t_vec3 n;

	n = ft_vec3_scal_prod(
		ft_vec3_minus(
			pos,
			sphere.ori),
		1 / sphere.r);
	return (n);
}

t_vec3 ft_get_plane_normal(t_plane plane, t_pt3 pos)
{
	return (plane.dir);
}

t_vec3 ft_get_obj_normal(t_obj obj, t_pt3 pos)
{
	if (OBJ_SPHERE == obj.obj_type)
	{
		return ft_get_sphere_normal(obj.sphere, pos);
	}
	if (OBJ_PLANE == obj.obj_type)
	{
		return (ft_get_plane_normal(obj.plane, pos));
	}
	// TODO : Handle cylindre normal
	return (ft_vec3_create(0, 0, 0));
}