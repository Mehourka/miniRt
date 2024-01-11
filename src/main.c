
#include "minirt.h"
#include "render.h"
#include "parsing.h"

int	main(int argc, char**argv)
{
	if (argc == 2)
	{
		t_data *data = get_data();
		parsing(argv[1], data);
		// Compute object transform matrices
		ft_compute_obj_matrices(data->obj, data->object_count);
		// Setup mlx data
		if (!(data->mlx = mlx_init(WIDTH, HEIGHT, "miniRt", true)))
			ft_raise_error(data);
		if (!(data->img = mlx_new_image(data->mlx, data->width, data->height)))
			ft_raise_error(data);
		ft_memset(data->img->pixels, 255, sizeof(int32_t) * data->height * data->width);
		mlx_image_to_window(data->mlx, data->img, 0, 0);


		// // Hooks
		// Navigation Hook
		mlx_loop_hook(data->mlx, &ft_nav_hook, data);
		// Rendering Hook
		mlx_loop_hook(data->mlx, &ft_render_hook, data);
		// Selection hook
		mlx_loop_hook(data->mlx, &ft_mouse_select, data);
		// // mlx loop
		mlx_loop(data->mlx);
		mlx_terminate(data->mlx);

	}
	else if (argc == 1)
		printf("Map needed");
	else
		printf("Enter one map only");
	return (EXIT_SUCCESS);
}
