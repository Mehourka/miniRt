#include "render.h"

void draw_gradient(t_data *data)
{
	mlx_image_t *image = data->img;

	for (int j = 0; j < image->height; j++)
	{
		for (int i = 0; i < image->width; i++)
		{
			float c1 = 1.0 * i / image->width;
			float c2 = 1.0 * j / image->height;
			mlx_put_pixel(image, i, j, norm_rgba(c1, 0, c2, 1));
		}
	}
}

void gen_p3_image(t_data *data)
{
	const int image_width = data->img->height;
	const int image_height = data->img->width;
	uint8_t *buffer = data->img->pixels;

	// Render
	printf("P3\n%i %i\n255\n", image_width, image_height);
	for (int j = 0; j < image_height; j++)
	{
		for (int i = 0; i < image_width; i++)
		{
			int pos = (i + j * image_width) * sizeof(uint8_t);
			printf("%i %i %i\n",
				buffer[pos],
				buffer[pos + 1],
				buffer[pos + 2]);
		}
	}
}