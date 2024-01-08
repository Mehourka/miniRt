#include "minirt.h"

void ft_mouse_select(void *param)
{
	t_data *data;
	mlx_t *mlx;
	t_ray ray;
	int32_t mousePos[2];

	data = (t_data *) param;
	mlx = data->mlx;
	if (mlx_is_mouse_down(mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		mlx_get_mouse_pos(mlx, mousePos, mousePos + 1);
		ray = ft_compute_ray(data->cam, mousePos[1], mousePos[0]);
		ft_print_ray(ray);
		t_hit_point hit_pt = ft_get_closest_hitpoint(data->obj, data->object_count, ray);
		ft_print_hitpt(hit_pt);
		printf("\n\n");
	}
}

void ft_nav_cam_rotation(mlx_t *mlx, t_data *data, t_cam *cam)
{
	double theta;
	theta = ft_deg_to_rad(5);
	t_vec3 axis;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		axis = cam->vup;
		cam->dir = ft_rodrigues_rotation(cam->dir, axis, -theta);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		axis = cam->vup;
		cam->dir = ft_rodrigues_rotation(cam->dir, axis, theta);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		// TODO: limit up/down view range
		axis = ft_vec3_cross_prod(cam->dir, cam->vup);
		cam->dir = ft_rodrigues_rotation(cam->dir, axis, -theta);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		// TODO: limit up/down view range
		axis = ft_vec3_cross_prod(cam->dir, cam->vup);
		cam->dir = ft_rodrigues_rotation(cam->dir, axis, theta);
	}
}

void ft_nav_cam_translation(mlx_t *mlx, t_data *data, t_cam *cam)
{
	t_vec3 axis;
	const double EPS = 0.05;

	// Translate Camera
	// move left
	if (mlx_is_key_down(mlx, MLX_KEY_H))
	{
		axis = ft_vec3_cross_prod(cam->dir, cam->vup);
		axis = ft_vec3_scal_prod(axis, 4 * EPS);
		cam->ori = ft_vec3_minus(cam->ori, axis);
	}
	// move right
	if (mlx_is_key_down(mlx, MLX_KEY_L))
	{
		axis = ft_vec3_cross_prod(cam->dir, cam->vup);
		axis = ft_vec3_scal_prod(axis, 4 * EPS);
		cam->ori = ft_vec3_add(cam->ori, axis);
	}
	// move up
	if (mlx_is_key_down(mlx, MLX_KEY_K))
	{
		axis = ft_vec3_scal_prod(cam->vup, 4 * EPS);
		cam->ori = ft_vec3_add(cam->ori, axis);
	}
	// move down
	if (mlx_is_key_down(mlx, MLX_KEY_J))
	{
		axis = ft_vec3_scal_prod(cam->vup, 4 * EPS);
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
	t_vec3 axis;
	t_cam *cam;

	data = (t_data*) param;
	cam = &data->cam;
	mlx = data->mlx;
	// Quit minirt
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);

	// change sphere radius
	double EPS = 0.05;
	t_cylinder *cylinder = &get_data()->obj[0].cylinder;
	if (mlx_is_key_down(mlx, MLX_KEY_PAGE_UP))
	{
		cylinder->ori = ft_vec3_add(cylinder->ori, (t_vec3){0, 0, +10 * EPS});
	}
	if (mlx_is_key_down(mlx, MLX_KEY_PAGE_DOWN))
	{
		cylinder->ori = ft_vec3_add(cylinder->ori, (t_vec3){0, 0, -10 * EPS});
	}

	// Camera Rotation
	ft_nav_cam_rotation(mlx, data, cam);
	// Camera Translation
	ft_nav_cam_translation(mlx, data, cam);
}


/*
	brief: mlx loop hook for rendering
*/
void ft_render_hook(void *param)
{
	t_data *data;

	data = param;
	ft_render_image(data);
}
