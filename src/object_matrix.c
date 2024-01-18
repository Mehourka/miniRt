#include "matrix.h"
#include "objects.h"
#include "minirt.h"

void ft_compute_obj_matrices(t_obj *object_list, int object_count)
{
	int		i;
	t_obj	*obj;
	t_mat3	trans_mx;
	t_mat3	inv_mx;

	i = 0;
	while (i < object_count)
	{
		obj = &object_list[i];
		if (OBJ_CYLINDER == obj->obj_type)
		{
			obj->dir = ft_vec3_normalize(obj->cylinder.dir);
			ft_compute_object_matrix(obj);
		}

		//TODO: apply same methode for plans and spehres

		// if (OBJ_SPHERE == obj->obj_type)
		// {
		//	trans_mx =
		//	inv_mx =
		// }
		if (OBJ_PLANE == obj->obj_type)
		{
			obj->plane.dir = ft_vec3_normalize(obj->plane.dir);
		}
		i++;
	}
}
