# include "minirt.h"

t_data *get_data()
{
	static t_data *data;

	if (data == NULL)
	{
		data = malloc(sizeof(t_data));
		data->height = 300;
		data->width = 500;
		data->aspect_ratio = (float) data->width / data->height;
	}
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

void instruction(void)
{
	t_data * data = get_data();
	mlx_put_string(data->mlx, "ESC : Quit", 5, 5);
	mlx_put_string(data->mlx, "N/M : decrease / increase height", 5, 20);
	mlx_put_string(data->mlx, "7/9 : Down/Up", 5, 35);
	mlx_put_string(data->mlx, "4/6 : Left/Right", 5, 50);
	mlx_put_string(data->mlx, "8/5 : Forward/Backward", 5, 65);
	mlx_put_string(data->mlx, "V/B : decrease / increase radius", 5, 80);
	mlx_put_string(data->mlx, "ARROWS : Cam Rotation", 5, 95);
}


