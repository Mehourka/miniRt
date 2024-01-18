#include "minirt.h"

t_vec3	ft_constrain_vertical_rot(t_cam *cam, t_vec3 axis, double theta)
{
	t_vec3			new_dir;
	const double	thresh = 0.99;
	double			likeness;

	new_dir = ft_rodrigues_rotation(cam->dir, axis, theta);
	likeness = fabs(ft_vec3_dot(new_dir, cam->vup));
	if (likeness > thresh)
		return (cam->dir);
	return (new_dir);
}

void	ft_nav_cam_rotation(mlx_t *mlx, t_cam *cam)
{
	double	theta;
	t_vec3	axis;

	theta = ft_deg_to_rad(5);
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

void	ft_nav_cam_translation(mlx_t *mlx, t_cam *cam)
{
	t_vec3			axis;
	const double	eps = 0.05;

	// Translate Camera
	// move left
	if (mlx_is_key_down(mlx, MLX_KEY_KP_4))
	{
		axis = ft_vec3_cross_prod(cam->dir, cam->vup);
		axis = ft_vec3_scal_prod(axis, 4 * eps);
		cam->ori = ft_vec3_minus(cam->ori, axis);
	}
	// move right
	if (mlx_is_key_down(mlx, MLX_KEY_KP_6))
	{
		axis = ft_vec3_cross_prod(cam->dir, cam->vup);
		axis = ft_vec3_scal_prod(axis, 4 * eps);
		cam->ori = ft_vec3_add(cam->ori, axis);
	}
	// move up
	if (mlx_is_key_down(mlx, MLX_KEY_KP_9))
	{
		axis = ft_vec3_scal_prod(cam->vup, 4 * eps);
		cam->ori = ft_vec3_add(cam->ori, axis);
	}
	// move down
	if (mlx_is_key_down(mlx, MLX_KEY_KP_7))
	{
		axis = ft_vec3_scal_prod(cam->vup, 4 * eps);
		cam->ori = ft_vec3_minus(cam->ori, axis);
	}
	// move forward
	if (mlx_is_key_down(mlx, MLX_KEY_KP_8))
	{
		axis = ft_vec3_scal_prod(cam->dir, 4 * eps);
		cam->ori = ft_vec3_add(cam->ori, axis);
	}
	// move backward
	if (mlx_is_key_down(mlx, MLX_KEY_KP_5))
	{
		axis = ft_vec3_scal_prod(cam->dir, 4 * eps);
		cam->ori = ft_vec3_minus(cam->ori, axis);
	}
}

/*
	brief: mlx loop hook for navigation control
*/
void	ft_nav_hook(void *param)
{
	t_data	*data;
	mlx_t	*mlx;
	t_cam	*cam;

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