# include "../include/minirt.h"
#include "../include/render.h"
#include "../include/parsing.h"

void	parse_sphere(t_data *data, t_parse *parse)
{
	if (parse->i > 99)
	{
		printf("Too many objects");
		exit(1);
	}
	data->obj[parse->i].obj_type = OBJ_SPHERE;
	ft_parse_orig_dir(&data->obj[parse->i].sphere.center, parse->token[1]);
	parse_length(&data->obj[parse->i].sphere.r, parse->token[2]);
	ft_parse_rgb(&data->obj[parse->i].sphere.color, parse->token[3]);
}

void	parse_plane(t_data *data, t_parse *parse)
{
	if (parse->i > 99)
	{
		printf("Too many objects");
		exit(1);
	}
	data->obj[parse->i].obj_type = OBJ_PLANE;
	ft_parse_orig_dir(&data->obj[parse->i].plane.center, parse->token[1]);
	ft_parse_orig_dir(&data->obj[parse->i].plane.direction, parse->token[2]);
	ft_parse_rgb(&data->obj[parse->i].plane.color, parse->token[3]);
}

void	parse_cylinder(t_data *data, t_parse *parse)
{
	if (parse->i > 99)
	{
		printf("Too many objects");
		exit(1);
	}
	data->obj[parse->i].obj_type = OBJ_CYLINDER;
	ft_parse_orig_dir(&data->obj[parse->i].cylinder.center, parse->token[1]);
	ft_parse_orig_dir(&data->obj[parse->i].cylinder.direction, parse->token[2]);
	parse_length(&data->obj[parse->i].cylinder.r, parse->token[3]);
	parse_length(&data->obj[parse->i].cylinder.longueur, parse->token[4]);
	ft_parse_rgb(&data->obj[parse->i].cylinder.color, parse->token[5]);
	parse->i++;

}