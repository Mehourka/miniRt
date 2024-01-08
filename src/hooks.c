#include "minirt.h"
#include "render.h"

double ft_deg_to_rad(double deg)
{
	return (deg * M_PI / 180);
}

/*
	brief: Rodrigues' rotation of vector v around the given axis

	param: v target vector
	param: axis rotation axis, has to be normalized
	param: theta rotation angle in radians
	returns: the rotated axis
*/
t_vec3 ft_rodrigues_rotation(t_vec3 v, t_vec3 axis, double theta)
{
	t_vec3 t1;
	t_vec3 t2;
	t_vec3 t3;

	// normalize axis
	axis = ft_vec3_normalize(axis);

	// comput the three terms
	t1 = ft_vec3_scal_prod(v, cos(theta));
	t2 = ft_vec3_scal_prod(
		axis,
		ft_vec3_dot(v, axis) * (1 - cos(theta))
	);
	t3 = ft_vec3_scal_prod(
		ft_vec3_cross_prod(axis, v),
		sin(theta)
	);
	return ft_vec3_add(
		ft_vec3_add(t1, t2), t3
	);
}

t_vec3 rotate_xaxis(t_vec3 u, double angle)
{
	t_vec3 new;

	new.x = u.x;
	new.y = cos(angle) * u.y - sin(angle) * u.z;
	new.z = sin(angle) * u.y + cos(angle) * u.z;
	return (new);
}

t_vec3 rotate_yaxis(t_vec3 u, double angle)
{
	t_vec3 new;

	new.x = cos(angle) * u.x - sin(angle) * u.z;
	new.y = u.y;
	new.z = sin(angle) * u.x + cos(angle) * u.z;
	return (new);
}


t_vec3 rotate_zaxis(t_vec3 u, double angle)
{
	t_vec3 new;

	new.x = cos(angle) * u.x + sin(angle) * u.y;
	new.y = -sin(angle) * u.x + cos(angle) * u.y;
	new.z = u.z;
	return (new);
}

/*
	brief: mlx loop hook for navigation control
*/
void ft_nav_hook(void *param)
{

	mlx_t *mlx = param;

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


	// Rotate camera
	t_cam *cam = &(get_data()->cam);
	double theta = ft_deg_to_rad(5);
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

	// Translate Camera
	if (mlx_is_key_down(mlx, MLX_KEY_H))
	{
		// moce left
		axis = ft_vec3_cross_prod(cam->dir, cam->vup);
		axis = ft_vec3_scal_prod(axis, 4 * EPS);
		cam->ori = ft_vec3_minus(cam->ori, axis);
	}

	if (mlx_is_key_down(mlx, MLX_KEY_L))
	{
		// move right
		axis = ft_vec3_cross_prod(cam->dir, cam->vup);
		axis = ft_vec3_scal_prod(axis, 4 * EPS);
		cam->ori = ft_vec3_add(cam->ori, axis);

	}

	if (mlx_is_key_down(mlx, MLX_KEY_K))
	{
		// move up
		axis = ft_vec3_scal_prod(cam->vup, 4 * EPS);
		cam->ori = ft_vec3_add(cam->ori, axis);
	}

	if (mlx_is_key_down(mlx, MLX_KEY_J))
	{
		// move down
		axis = ft_vec3_scal_prod(cam->vup, 4 * EPS);
		cam->ori = ft_vec3_minus(cam->ori, axis);
	}

}

/*
	brief: mlx loop hook for rendering
*/
void ft_render_hook(void *param)
{
	(void) param;
	ft_render_image();
}