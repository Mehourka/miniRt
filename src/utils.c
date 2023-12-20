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
	
	t_cam *cam = &data->cam;

	data->obj[0].obj_type = OBJ_SPHERE;
	data->obj[0].ori = ft_vec3_create(2, 0, -5);
	data->obj[0].sphere.r = 1.1;
	data->obj[0].color = ft_vec3_create(.6, .1, .1);

	data->obj[1].obj_type = OBJ_SPHERE;
	data->obj[1].ori = ft_vec3_create(0, 0, -5);
	data->obj[1].sphere.r = 1;
	data->obj[1].color = ft_vec3_create(.1, .6, .1);

	data->obj[2].obj_type = OBJ_SPHERE;
	data->obj[2].ori = ft_vec3_create(-2, 0, -5);
	data->obj[2].sphere.r = 0.9;
	data->obj[2].color = ft_vec3_create(0.1, .1, .6);

	data->obj[3].obj_type = OBJ_SPHERE;
	data->obj[3].ori = ft_vec3_create(0, -150, 0);
	data->obj[3].sphere.r = 145;
	data->obj[3].color = ft_vec3_create(0.15, .15, .15);

	cam->ori = ft_vec3_create(0, 0, 0);
	cam->dir = ft_vec3_create(0, 0, -1);
	cam->vup = ft_vec3_create(0, 1, 0);
	cam->angle = 70;

	data->light.ori = ft_vec3_create(3, 0, 0);
}
