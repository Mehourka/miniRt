#include "../include/minirt.h"
#include "../include/render.h"
#include "../include/parsing.h"

void	parse_sphere(t_data *data, t_parse *parse)
{
	if (parse->count != 4)
	{
		printf("Error\n");
		printf("Wrong number of attribute for %s", parse->token[0]);
		exit(1);
	}
	if (parse->i > 99)
		ft_error_message("A maximum of 100 objects is allowed");
	data->obj[parse->i].obj_type = OBJ_SPHERE;
	ft_parse_orig_dir(&data->obj[parse->i].sphere.ori, parse->token[1], 'o');
	parse_length(&data->obj[parse->i].sphere.r, parse->token[2]);
	data->obj[parse->i].sphere.r /= 2;
	ft_parse_rgb(&data->obj[parse->i].sphere.color, parse->token[3]);
	data->object_count++;
	parse->i++;
	free(parse->token[0]);
}

void	parse_plane(t_data *data, t_parse *parse)
{
	if (parse->count != 4)
	{
		printf("Error\n");
		printf("Wrong number of attribute for %s", parse->token[0]);
		exit(1);
	}
	if (parse->i > 99)
		ft_error_message("A maximum of 100 objects is allowed");
	data->obj[parse->i].obj_type = OBJ_PLANE;
	ft_parse_orig_dir(&data->obj[parse->i].plane.ori, parse->token[1], 'o');
	ft_parse_orig_dir(&data->obj[parse->i].plane.dir, parse->token[2], 'd');
	data->obj[parse->i].plane.dir
		= ft_vec3_normalize(data->obj[parse->i].plane.dir);
	ft_parse_rgb(&data->obj[parse->i].plane.color, parse->token[3]);
	data->object_count++;
	parse->i++;
	free(parse->token[0]);
}

void	parse_cylinder(t_data *data, t_parse *parse)
{
	if (parse->count != 6)
	{
		printf("Error\n");
		printf("Wrong number of attribute for %s", parse->token[0]);
		exit(1);
	}
	if (parse->i > 99)
		ft_error_message("A maximum of 100 objects is allowed");
	data->obj[parse->i].obj_type = OBJ_CYLINDER;
	ft_parse_orig_dir(&data->obj[parse->i].cylinder.ori, parse->token[1], 'o');
	ft_parse_orig_dir(&data->obj[parse->i].cylinder.dir, parse->token[2], 'd');
	data->obj[parse->i].cylinder.dir
		= ft_vec3_normalize(data->obj[parse->i].cylinder.dir);
	parse_length(&data->obj[parse->i].cylinder.r, parse->token[3]);
	data->obj[parse->i].cylinder.r /= 2;
	parse_length(&data->obj[parse->i].cylinder.longueur, parse->token[4]);
	ft_parse_rgb(&data->obj[parse->i].cylinder.color, parse->token[5]);
	data->object_count++;
	parse->i++;
	free(parse->token[0]);
}

void	parse_cone(t_data *data, t_parse *parse)
{
	if (parse->count != 6)
	{
		printf("Error\n");
		printf("Wrong number of attribute for %s", parse->token[0]);
		exit(1);
	}
	if (parse->i > 99)
		ft_error_message("A maximum of 100 objects is allowed");
	data->obj[parse->i].obj_type = OBJ_CONE;
	ft_parse_orig_dir(&data->obj[parse->i].cone.ori, parse->token[1], 'o');
	ft_parse_orig_dir(&data->obj[parse->i].cone.dir, parse->token[2], 'd');
	data->obj[parse->i].cone.dir
		= ft_vec3_normalize(data->obj[parse->i].cone.dir);
	parse_length(&data->obj[parse->i].cone.h, parse->token[3]);
	parse_length(&data->obj[parse->i].cone.angle, parse->token[4]);
	if (data->obj[parse->i].cone.angle >= 180
		&& data->obj[parse->i].cone.angle <= 0)
		ft_error_message("The angle of the cone is out of range : ]0, 180[");
	ft_parse_rgb(&data->obj[parse->i].cone.color, parse->token[5]);
	data->object_count++;
	parse->i++;
	free(parse->token[0]);
}
