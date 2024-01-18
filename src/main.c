#include "minirt.h"
#include "render.h"
#include "parsing.h"

void	all_hooks(void)
{
	t_data	*data;

	data = get_data();
	mlx_loop_hook(data->mlx, &ft_nav_hook, data);
	mlx_loop_hook(data->mlx, &ft_render_hook, data);
	mlx_loop_hook(data->mlx, &ft_mouse_select_object, data);
	mlx_loop_hook(data->mlx, &selec_light, data);
	mlx_loop_hook(data->mlx, &ft_obj_prop, data);
	mlx_loop_hook(data->mlx, &ft_obj_trans, data);
	mlx_resize_hook(data->mlx, &ft_resize_hook, data);
	mlx_loop_hook(data->mlx, &ft_light_trans, data);
	mlx_loop_hook(data->mlx, &ft_obj_rotation, data);
	instruction();
}

int	main(int argc, char**argv)
{
	t_data	*data;

	if (argc == 2)
	{
		data = get_data();
		parsing(argv[1], data);
		ft_compute_obj_matrices(data->obj, data->object_count);
		data->mlx = mlx_init(data->width, data->height, "miniRt", true);
		if (!(data->mlx))
			ft_raise_error(data);
		data->img = mlx_new_image(data->mlx, data->width, data->height);
		if (!(data->img))
			ft_raise_error(data);
		ft_memset(data->img->pixels, 255, sizeof(int32_t)
			* data->height * data->width);
		mlx_image_to_window(data->mlx, data->img, 0, 0);
		all_hooks();
		mlx_loop(data->mlx);
		mlx_terminate(data->mlx);
	}
	else if (argc == 1)
		printf("Map needed");
	else
		printf("Enter one map only");
	return (EXIT_SUCCESS);
}
