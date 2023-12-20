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
	t_obj *obj1 = &data->obj[0];
	t_cam *cam = &data->cam;

	obj1->obj_type = OBJ_SPHERE;
	obj1->ori = ft_vec3_create(0, 0, -5);
	obj1->sphere.r = 3;

	cam->ori = ft_vec3_create(0, 0, 0);
	cam->dir = ft_vec3_create(0, 0, 1);
	cam->angle = 70;
}
