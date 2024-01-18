#include "minirt.h"

void	ft_obj_trans(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		data->selec.obj->ori.x += 0.1;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		data->selec.obj->ori.x -= 0.1;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		data->selec.obj->ori.y += 0.1;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		data->selec.obj->ori.y -= 0.1;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_Q))
		data->selec.obj->ori.z += 0.1;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_E))
		data->selec.obj->ori.z -= 0.1;
}

/*void	ft_rotate_objects(t_obj *object_list, int object_count)
{
	const double	eps = 0.05;
	int				i;
	t_vec3			rotation_axis;
	t_obj			*obj;

	i = 0;
	rotation_axis = ft_vec3_create(0, 1, 0);
	while (i < object_count)
	{
		obj = &object_list[i];
		obj->ori = ft_rodrigues_rotation(obj->ori, rotation_axis, eps);
		i++;
	}
}*/

void	ft_mouse_select_object(void *param)
{
	t_data		*data;
	mlx_t		*mlx;
	t_ray		ray;
	int32_t		mousepos[2];
	t_hit_point	hit_pt;

	data = (t_data *)param;
	mlx = data->mlx;
	if (mlx_is_mouse_down(mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		mlx_get_mouse_pos(mlx, mousepos, mousepos + 1);
		ray = ft_compute_ray(data->cam, mousepos[1], mousepos[0]);
		hit_pt = ft_get_closest_hitpoint(data->obj, data->object_count, ray);
		if (hit_pt.f_valid == true)
			data->selec.obj = hit_pt.object;
		printf("\n\n");
	}
}

void	ft_rotation2(t_vec3 *dir, t_data *data, double theta)
{
	t_vec3	x_axis;
	t_vec3	y_axis;
	t_vec3	z_axis;

	x_axis = ft_vec3_create(1, 0, 0);
	y_axis = ft_vec3_create(0, 1, 0);
	z_axis = ft_vec3_create(0, 0, 1);
	if (mlx_is_key_down(data->mlx, MLX_KEY_F))
		*dir = ft_rodrigues_rotation(*dir, x_axis, -theta);
	if (mlx_is_key_down(data->mlx, MLX_KEY_H))
		*dir = ft_rodrigues_rotation(*dir, x_axis, theta);
	if (mlx_is_key_down(data->mlx, MLX_KEY_T))
		*dir = ft_rodrigues_rotation(*dir, y_axis, theta);
	if (mlx_is_key_down(data->mlx, MLX_KEY_G))
		*dir = ft_rodrigues_rotation(*dir, y_axis, theta);
	if (mlx_is_key_down(data->mlx, MLX_KEY_R))
		*dir = ft_rodrigues_rotation(*dir, z_axis, theta);
	if (mlx_is_key_down(data->mlx, MLX_KEY_Y))
		*dir = ft_rodrigues_rotation(*dir, z_axis, theta);
	// ft_print_vec3(*dir);
}

void	ft_obj_rotation(void *param)
{
	double	theta;
	t_data	*data;

	data = (t_data *)param;
	theta = ft_deg_to_rad(5);
	if (data->selec.obj->obj_type == OBJ_CONE)
	{
		ft_rotation2(&data->selec.obj->cone.dir, data, theta);
		ft_compute_object_matrix(data->selec.obj);

	}
	else if (data->selec.obj->obj_type == OBJ_CYLINDER)
	{
		ft_rotation2(&data->selec.obj->cylinder.dir, data, theta);
		ft_compute_object_matrix(data->selec.obj);

	}
	else if (data->selec.obj->obj_type == OBJ_PLANE)
		ft_rotation2(&data->selec.obj->plane.dir, data, theta);
}
