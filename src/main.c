
#include "minirt.h"
#include "render.h"

int main(void)
{
	const int image_width = WIDTH;
	const int image_height = HEIGHT;

	// Setup mlx data
	t_data *data = get_data();
	create_objects();

	if (!(data->mlx = mlx_init(WIDTH, HEIGHT, "miniRt", true)))
		ft_raise_error(data);
	if (!(data->img = mlx_new_image(data->mlx, image_width, image_height)))
		ft_raise_error(data);

	// // // Draw on image
	ft_memset(data->img->pixels, 255, sizeof(int32_t) * image_height * image_width);
	// draw_gradient(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);

	// // Hooks
	mlx_loop_hook(data->mlx, &ft_hook, data->mlx);

	// // mlx loop
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);

	// printf("Sphere : %p\n", data->obj->center);


	return (EXIT_SUCCESS);
}