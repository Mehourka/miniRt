# include "minirt.h"

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
	// TODO: Should free data here
	if (data->mlx)
		mlx_close_window(data->mlx);
	ft_putstr_fd((char *)mlx_strerror(mlx_errno), STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	instruction(void)
{
	t_data	*data;

	//change instruction
	data = get_data();
	mlx_put_string(data->mlx, "ESC : Quit", 5, 5);
	mlx_put_string(data->mlx, "7/9 (cam): Down/Up", 5, 20);
	mlx_put_string(data->mlx, "4/6 (cam): Left/Right", 5, 35);
	mlx_put_string(data->mlx, "8/5 (cam): Forward/Backward", 5, 50);
	mlx_put_string(data->mlx, "A/D (object): Translation in x", 5, 65);
	mlx_put_string(data->mlx, "W/S (object): Translation in y", 5, 80);
	mlx_put_string(data->mlx, "Q/E (object): Translation in z", 5, 95);
	mlx_put_string(data->mlx, "V/B : decrease / increase radius", 5, 110);
	mlx_put_string(data->mlx, "N/M : decrease / increase height", 5, 125);
	mlx_put_string(data->mlx, "ARROWS : Cam Rotation", 5, 140);
	mlx_put_string(data->mlx, "I/K (light): Translation in x", 5, 155);
	mlx_put_string(data->mlx, "J/L (light): Translation in y", 5, 170);
	mlx_put_string(data->mlx, "O/P (light): Translation in z", 5, 185);
	mlx_put_string(data->mlx, "F/H (object): Rotation in x", 5, 200);
	mlx_put_string(data->mlx, "T/G (object): Rotation in y", 5, 215);
	mlx_put_string(data->mlx, "R/Y (object): Rotation in z", 5, 230);
}
