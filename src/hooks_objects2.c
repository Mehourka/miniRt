#include "minirt.h"

void	minus_radius(double *r)
{
	if (*r > 0.2)
		*r -= 0.1;
}

void	change_radius(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_B))
	{
		if (data->selec.obj->obj_type == OBJ_SPHERE)
			data->selec.obj->sphere.r += 0.1;
		else if (data->selec.obj->obj_type == OBJ_CYLINDER)
			data->selec.obj->cylinder.r += 0.1;
		else if (data->selec.obj->obj_type == OBJ_CONE)
		{
			if (data->selec.obj->cone.angle < 179.8)
				data->selec.obj->cone.angle += 0.1;
		}
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_V))
	{
		if (data->selec.obj->obj_type == OBJ_SPHERE)
			minus_radius(&data->selec.obj->sphere.r);
		else if (data->selec.obj->obj_type == OBJ_CYLINDER)
			minus_radius(&data->selec.obj->cylinder.r);
		else if (data->selec.obj->obj_type == OBJ_CONE)
			minus_radius(&data->selec.obj->cone.angle);
	}
}

void	change_height(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_M))
	{
		if (data->selec.obj->obj_type == OBJ_CYLINDER)
			data->selec.obj->cylinder.longueur += 0.1;
		else if (data->selec.obj->obj_type == OBJ_CONE)
			data->selec.obj->cone.h += 0.1;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_N))
	{
		if (data->selec.obj->obj_type == OBJ_CYLINDER)
		{
			if (data->selec.obj->cylinder.longueur > 0.2)
				data->selec.obj->cylinder.longueur -= 0.1;
		}
		else if (data->selec.obj->obj_type == OBJ_CONE)
		{
			if (data->selec.obj->cone.h > 0.2)
				data->selec.obj->cone.h -= 0.1;
		}
	}
}

void	ft_obj_prop(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	change_radius(data);
	change_height(data);
}
