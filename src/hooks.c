#include "minirt.h"

void	selec_light(void *param)
{
	t_data *data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_1))
	{
		data->selec.light = &data->light[0];
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_2))
	{
		if(data->L >= 2)
			data->selec.light = &data->light[0];
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_3))
	{
		if(data->L >= 3)
			data->selec.light = &data->light[0];
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_4))
	{
		if(data->L >= 4)
			data->selec.light = &data->light[0];
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_5))
	{
		if(data->L >= 5)
			data->selec.light = &data->light[0];
	}

}

void	ft_obj_prop(void *param)
{
	t_data *data;

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


void	ft_obj_trans(void *param)
{
	t_data *data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_B))
	{
		if(data->selec.obj->obj_type == OBJ_SPHERE)
			data->selec.obj->sphere.r += 0.1;
		else if(data->selec.obj->obj_type == OBJ_CYLINDER)
			data->selec.obj->cylinder.r += 0.1;
		else if(data->selec.obj->obj_type == OBJ_CONE)
		{
			if(data->selec.obj->cone.angle > 179.8)
				data->selec.obj->cone.angle += 0.1;
		}
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_V))
	{
		if(data->selec.obj->obj_type == OBJ_SPHERE)
		{
			if(data->selec.obj->sphere.r > 0.2)
				data->selec.obj->sphere.r -= 0.1;
		}
		else if(data->selec.obj->obj_type == OBJ_CYLINDER)
		{
			if(data->selec.obj->cylinder.r > 0.2)
				data->selec.obj->cylinder.r -= 0.1;
		}
		else if(data->selec.obj->obj_type == OBJ_CONE)
		{
			if(data->selec.obj->cone.angle > 0.2)
				data->selec.obj->cone.angle -= 0.1;
		}
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_M))
	{
		if(data->selec.obj->obj_type == OBJ_CYLINDER)
				data->selec.obj->cylinder.longueur += 0.1;
		else if(data->selec.obj->obj_type == OBJ_CONE)
				data->selec.obj->cone.h += 0.1;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_N))
	{
		if(data->selec.obj->obj_type == OBJ_CYLINDER)
		{
			if(data->selec.obj->cylinder.longueur > 0.2)
				data->selec.obj->cylinder.longueur -= 0.1;
		}
		else if(data->selec.obj->obj_type == OBJ_CONE)
		{
			if(data->selec.obj->cone.h > 0.2)
				data->selec.obj->cone.h -= 0.1;
		}
	}
}


t_vec3 ft_constrain_vertical_rot(t_cam *cam, t_vec3 axis, double theta)
{
	t_vec3 new_dir;
	const double THRESH = 0.99;
	double likeness;

	new_dir = ft_rodrigues_rotation(cam->dir, axis, theta);
	likeness = fabs(ft_vec3_dot(new_dir, cam->vup));
	if (likeness > THRESH)
		return (cam->dir);

	return (new_dir);
}



void ft_nav_cam_rotation(mlx_t *mlx, t_cam *cam)
{
	double theta;
	theta = ft_deg_to_rad(5);
	t_vec3 axis;

	axis = cam->vup;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		cam->dir = ft_rodrigues_rotation(cam->dir, axis, -theta);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		axis = cam->vup;
		cam->dir = ft_rodrigues_rotation(cam->dir, axis, theta);
	}

	axis = ft_vec3_cross_prod(cam->dir, cam->vup);
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		// TODO: limit up/down view range
		cam->dir = ft_constrain_vertical_rot(cam, axis, -theta);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		// TODO: limit up/down view range
		cam->dir = ft_constrain_vertical_rot(cam, axis, theta);
	}
}

void ft_nav_cam_translation(mlx_t *mlx, t_cam *cam)
{
	t_vec3 axis;
	const double EPS = 0.05;

	// Translate Camera
	// move left
	if (mlx_is_key_down(mlx, MLX_KEY_KP_4))
	{
		axis = ft_vec3_cross_prod(cam->dir, cam->vup);
		axis = ft_vec3_scal_prod(axis, 4 * EPS);
		cam->ori = ft_vec3_minus(cam->ori, axis);
	}
	// move right
	if (mlx_is_key_down(mlx, MLX_KEY_KP_6))
	{
		axis = ft_vec3_cross_prod(cam->dir, cam->vup);
		axis = ft_vec3_scal_prod(axis, 4 * EPS);
		cam->ori = ft_vec3_add(cam->ori, axis);
	}
	// move up
	if (mlx_is_key_down(mlx, MLX_KEY_KP_9))
	{
		axis = ft_vec3_scal_prod(cam->vup, 4 * EPS);
		cam->ori = ft_vec3_add(cam->ori, axis);
	}
	// move down
	if (mlx_is_key_down(mlx, MLX_KEY_KP_7))
	{
		axis = ft_vec3_scal_prod(cam->vup, 4 * EPS);
		cam->ori = ft_vec3_minus(cam->ori, axis);
	}
	// move forward
	if (mlx_is_key_down(mlx, MLX_KEY_KP_8))
	{
		axis = ft_vec3_scal_prod(cam->dir, 4 * EPS);
		cam->ori = ft_vec3_add(cam->ori, axis);
	}
	// move backward
	if (mlx_is_key_down(mlx, MLX_KEY_KP_5))
	{
		axis = ft_vec3_scal_prod(cam->dir, 4 * EPS);
		cam->ori = ft_vec3_minus(cam->ori, axis);
	}

}

/*
	brief: mlx loop hook for navigation control
*/
void ft_nav_hook(void *param)
{
	t_data *data;
	mlx_t *mlx;
	t_cam *cam;

	data = (t_data *)param;
	cam = &data->cam;
	mlx = data->mlx;
	// Quit minirt
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);

	// Camera Rotation
	ft_nav_cam_rotation(mlx, cam);
	// Camera Translation
	ft_nav_cam_translation(mlx, cam);
}

void ft_resize_hook(int32_t width, int32_t height, void* param)
{
	t_data *data = (t_data *)param;

	data->height = height;
	data->width = width;
	data->aspect_ratio = (float) data->width / data->height;
	mlx_delete_image(data->mlx, data->img);
	if (!(data->img = mlx_new_image(data->mlx, data->width, data->height)))
		ft_raise_error(data);
	ft_memset(data->img->pixels, 255, sizeof(int32_t) * data->height * data->width);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	instruction();
}

void ft_rotate_objects(t_obj *object_list, int object_count)
{
	const double EPS = 0.05;
	int i;
	t_vec3 rotation_axis;
	t_obj *obj;

	i = 0;
	rotation_axis = ft_vec3_create(0,1,0);
	while (i < object_count)
	{
		obj = &object_list[i];
		obj->ori = ft_rodrigues_rotation(obj->ori, rotation_axis, EPS);
		i++;
	}

}

/*
	brief: mlx loop hook for rendering
*/
void ft_render_hook(void *param)
{
	t_data *data;

	data = param;
	ft_rotate_objects(data->obj, data->object_count);
	ft_render_image(data);
}

void ft_mouse_select_object(void *param)
{
	t_data *data;
	mlx_t *mlx;
	t_ray ray;
	int32_t mousePos[2];

	data = (t_data *)param;
	mlx = data->mlx;
	if (mlx_is_mouse_down(mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		// Get mouse position
		mlx_get_mouse_pos(mlx, mousePos, mousePos + 1);

		// Create ray pointing at mouse
		ray = ft_compute_ray(data->cam, mousePos[1], mousePos[0]);

		// Compute the hit point in that pixel
		t_hit_point hit_pt = ft_get_closest_hitpoint(data->obj, data->object_count, ray);
		// TODO segfault when we click on the basckground;
		if(hit_pt.object->obj_type == 1)
			printf("sphere selected");
		if(hit_pt.object->obj_type == 2)
			printf("plane selected");
		if(hit_pt.object->obj_type == 3)
			printf("cylinder selected");
		if(hit_pt.object->obj_type == 4)
			printf("cone selected");
		data->selec.obj = hit_pt.object;
		printf("\n\n");
	}
}