# include "minirt.h"

t_data *get_data()
{
	static t_data *data;

	if (data == NULL)
	{
		data = malloc(sizeof(t_data));
		data->aspect_ratio = (float) WIDTH / HEIGHT;
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


