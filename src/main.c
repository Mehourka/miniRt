#include "render.h"
#include "vectors.h"

t_data *get_data()
{
	static t_data *data;

	if (data == NULL)
		data = malloc(sizeof(t_data));
	return (data);
}

void ft_raise_error(t_data *data)
{
	// TODO: Should free data here
	if (data->mlx)
		mlx_close_window(data->mlx);
	ft_putstr_fd((char *)mlx_strerror(mlx_errno), STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void ft_hook(void *param)
{

	mlx_t *mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

int main(void)
{
	const int image_width = 200;
	const int image_height = 200;

	// Setup mlx data
	t_data *data = get_data();
	if (!(data->mlx = mlx_init(WIDTH, HEIGHT, "miniRt", true)))
		ft_raise_error(data);
	if (!(data->img = mlx_new_image(data->mlx, image_width, image_height)))
		ft_raise_error(data);

	// Draw on image
	ft_memset(data->img->pixels, 255, sizeof(int32_t) * image_height * image_width);
	draw_gradient(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);

	// Hooks
	mlx_loop_hook(data->mlx, &ft_hook, data->mlx);

	// mlx loop
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);

	return (EXIT_SUCCESS);
}