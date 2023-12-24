
#include "minirt.h"
#include "render.h"
#include "parsing.h"

int	main(int argc, char**argv)
{
	const int image_width = WIDTH;
	const int image_height = HEIGHT;

	if (argc == 2)
	{
		dot_rt(argv[1]);

		// Setup mlx data
		t_data *data = get_data();
		parsing(argv[1], data);

		if (!(data->mlx = mlx_init(WIDTH, HEIGHT, "miniRt", true)))
			ft_raise_error(data);
		if (!(data->img = mlx_new_image(data->mlx, image_width, image_height)))
			ft_raise_error(data);

		// // // Draw on image
		ft_memset(data->img->pixels, 255, sizeof(int32_t) * image_height * image_width);
		
		mlx_image_to_window(data->mlx, data->img, 0, 0);


		// // Hooks
		mlx_loop_hook(data->mlx, &ft_hook, data->mlx);

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