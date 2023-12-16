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

void create_objects(void)
{
	t_data *data = get_data();
	t_obj *sphere = &data->obj;;
	t_cam *cam = &data->cam;

	sphere->obj_type = OBJ_SPHERE;
	sphere->center = ft_vec3_create(100, 0, 0);
	sphere->r = 20;

	cam->center = ft_vec3_create(0, 0, 0);
	cam->direction = ft_vec3_create(1, 0, 0);
	cam->angle = 70;
}