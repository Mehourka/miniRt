#include "minirt.h"

t_data	*get_data(void)
{
	static t_data	*data;

	if (data == NULL)
	{
		data = malloc(sizeof(t_data));
		data->height = 300;
		data->width = 500;
		data->aspect_ratio = (float) data->width / data->height;
	}
	return (data);
}

void	ft_raise_error(t_data *data)
{
	if (data->mlx)
		mlx_close_window(data->mlx);
	ft_putstr_fd((char *)mlx_strerror(mlx_errno), STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	instruction(void)
{
	t_data	*data;

	data = get_data();
	mlx_put_string(data->mlx, "ESC : Quit", 5, 5);
	mlx_put_string(data->mlx, "CAMERA :", 5, 20);
	mlx_put_string(data->mlx, "7/9 : Down/Up", 5, 35);
	mlx_put_string(data->mlx, "4/6 : Left/Right", 5, 50);
	mlx_put_string(data->mlx, "8/5 : Forward/Backward", 5, 65);
	mlx_put_string(data->mlx, "ARROWS : Rotation", 5, 80);
	mlx_put_string(data->mlx, "LIGHT :", 5, 95);
	mlx_put_string(data->mlx, "I/K : Trans x", 5, 110);
	mlx_put_string(data->mlx, "J/L : Trans y", 5, 125);
	mlx_put_string(data->mlx, "O/P : Trans z", 5, 140);
	mlx_put_string(data->mlx, "OBJECT :", 5, 155);
	mlx_put_string(data->mlx, "A/D : Trans in x", 5, 170);
	mlx_put_string(data->mlx, "W/S : Trans in y", 5, 185);
	mlx_put_string(data->mlx, "Q/E : Trans in z", 5, 200);
	mlx_put_string(data->mlx, "F/H : Rot x", 5, 215);
	mlx_put_string(data->mlx, "T/G : Rot y", 5, 230);
	mlx_put_string(data->mlx, "R/Y : Rot z", 5, 245);
	mlx_put_string(data->mlx, "V/B : Radius", 5, 260);
	mlx_put_string(data->mlx, "N/M : Height", 5, 275);
}
