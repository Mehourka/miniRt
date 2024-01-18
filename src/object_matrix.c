#include "matrix.h"
#include "objects.h"
#include "minirt.h"

void ft_compute_object_matrix(t_obj *obj)
{
	obj->transform_matrix = ft_ortho_normal_mat3(obj->dir);
	obj->inverse_transfrom = ft_mat3_inverse(obj->transform_matrix);
}

void ft_compute_obj_matrices(t_obj *object_list, int object_count)
{
	int		i;
	t_obj	*obj;

	i = 0;
	while (i < object_count)
	{
		obj = &object_list[i];
		obj->dir = ft_vec3_normalize(obj->dir);

		if (OBJ_CYLINDER == obj->obj_type
			|| OBJ_CONE == obj->obj_type)
		{
			ft_compute_object_matrix(obj);
		}

		//TODO: apply same methode for plans and spehres

		// if (OBJ_SPHERE == obj->obj_type)
		// {
		//	trans_mx =
		//	inv_mx =
		// }
		i++;
	}
}
