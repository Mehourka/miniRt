#include "minirt.h"
#include "render.h"

double ft_deg_to_rad(double deg)
{
	return (deg * M_PI / 180);
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
	double *r = &get_data()->obj[0].sphere.r;
	if (mlx_is_key_down(mlx, MLX_KEY_PAGE_UP))
		*r += EPS;
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
		cam->dir = rotate_yaxis(cam->dir, ft_deg_to_rad(5));
	}
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		cam->dir = rotate_yaxis(cam->dir, -ft_deg_to_rad(5));
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		cam->dir = rotate_xaxis(cam->dir, -ft_deg_to_rad(5));
	}
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		cam->dir = rotate_xaxis(cam->dir, ft_deg_to_rad(5));
	}
}

/*
	brief: mlx loop hook for rendering
*/
void ft_render_hook(void *param)
{
	ft_render_image();
}