# include "header.h"


void gen_p3_image(){
	const int image_width = 256;
	const int image_height = 256;

	// Render

	printf("P3\n%i %i\n255\n", image_width, image_height);

	for (int j = 0; j < image_height; j++)
	{
		for (int i = 0; i < image_width; i++)
		{
			printf("%i %i %i\n", i, j, 0);
		}
	}
}

int get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	norm_rgba(float r, float g, float b, float a)
{
	// static t_color;

	r = fmin(fmax(r, 0), 1) * 255;
	g = fmin(fmax(g, 0), 1) * 255;
	b = fmin(fmax(b, 0), 1) * 255;
	a = fmin(fmax(a, 0), 1) * 255;
	return ((int)r << 24 | (int)g << 16 | (int)b << 8 | (int)a);
}

void draw_gradient(t_data *data)
{
	mlx_image_t *image = data->image;

	for (int j = 0; j < image->height; j++)
	{
		for (int i = 0; i < image->width; i++)
		{
			float c1 = 1.0 * i / image->width;
			float c2 = 1.0 * j / image->height;
			mlx_put_pixel(image, i, j, norm_rgba(c1, c2, 0, 1));
		}
	}

}

t_data *get_data()
{
	static t_data *data;

	if (data == NULL)
		data = malloc (sizeof(t_data));
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

void ft_hook(void* param)
{

	mlx_t* mlx = param;

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
	if (!(data->image = mlx_new_image(data->mlx, image_width, image_height)))
		ft_raise_error(data);

	// Draw on image
	ft_memset(data->image->pixels, 255, sizeof(int32_t) * image_height * image_width);
	draw_gradient(data);
	mlx_image_to_window(data->mlx, data->image, 0, 0);

	// Hooks
	mlx_loop_hook(data->mlx, &ft_hook,data->mlx);

	// mlx loop
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);

	return (EXIT_SUCCESS);
}