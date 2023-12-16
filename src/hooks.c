#include "minirt.h"

t_vec3 rotate_yaxis(t_vec3 u, double angle);
double ft_deg_to_rad(double deg);

double ft_deg_to_rad(double deg)
{
	return (deg * M_PI / 180);
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

void ft_hook(void *param)
{

	mlx_t *mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);

	// change sphere radius
	double EPS = 0.05;
	double *r = &get_data()->obj[0].sphere.r;
	if (mlx_is_key_down(mlx, MLX_KEY_PAGE_UP))
	{
		*r += EPS;
		if (*r > 2.5)
			*r = 2.5;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_PAGE_DOWN))
	{
		*r -= EPS;
		if (*r < 0.1)
			*r = 0.1;
	}


	// Rotate camera
	t_cam *cam = &(get_data()->cam);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		// cam->ori.z += EPS;
		cam->dir = rotate_yaxis(cam->dir, ft_deg_to_rad(5));
		ft_vec3_print(cam->dir);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		// cam->ori.z -= EPS;
		cam->dir = rotate_yaxis(cam->dir, -ft_deg_to_rad(5));
		ft_vec3_print(cam->dir);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		// cam->ori.z += EPS;
		cam->dir = rotate_zaxis(cam->dir, ft_deg_to_rad(5));
		ft_vec3_print(cam->dir);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		// cam->ori.z -= EPS;
		cam->dir = rotate_zaxis(cam->dir, -ft_deg_to_rad(5));
		ft_vec3_print(cam->dir);
	}

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);

	compute_viewport();
}