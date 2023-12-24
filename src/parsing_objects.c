# include "../include/minirt.h"
#include "../include/render.h"
#include "../include/parsing.h"

void	parse_sphere(t_data *data, t_parse *parse)
{
	if(parse->count != 4)
	{
		printf("Wrong number of attribute for %s", parse->token[0]);
		exit(1);
	}
	if (parse->i > 99)
	{
		printf("Too many objects");
		exit(1);
	}
	data->obj[parse->i].obj_type = OBJ_SPHERE;
	ft_parse_orig_dir(&data->obj[parse->i].sphere.ori, parse->token[1]);
	parse_length(&data->obj[parse->i].sphere.r, parse->token[2]);
	ft_parse_rgb(&data->obj[parse->i].sphere.color, parse->token[3]);
	data->object_count++;
	parse->i++;
}

void	parse_plane(t_data *data, t_parse *parse)
{
	if(parse->count != 4)
	{
		printf("Wrong number of attribute for %s", parse->token[0]);
		exit(1);
	}
	if (parse->i > 99)
	{
		printf("Too many objects");
		exit(1);
	}
	data->obj[parse->i].obj_type = OBJ_PLANE;
	ft_parse_orig_dir(&data->obj[parse->i].plane.ori, parse->token[1]);
	ft_parse_orig_dir(&data->obj[parse->i].plane.dir, parse->token[2]);
	ft_parse_rgb(&data->obj[parse->i].plane.color, parse->token[3]);
	data->object_count++;
	parse->i++;
}

void	parse_cylinder(t_data *data, t_parse *parse)
{
	if(parse->count != 6)
	{
		printf("Wrong number of attribute for %s", parse->token[0]);
		exit(1);
	}
	if (parse->i > 99)
	{
		printf("Too many objects");
		exit(1);
	}
	data->obj[parse->i].obj_type = OBJ_CYLINDER;
	ft_parse_orig_dir(&data->obj[parse->i].cylinder.ori, parse->token[1]);
	ft_parse_orig_dir(&data->obj[parse->i].cylinder.dir, parse->token[2]);
	parse_length(&data->obj[parse->i].cylinder.r, parse->token[3]);
	parse_length(&data->obj[parse->i].cylinder.longueur, parse->token[4]);
	ft_parse_rgb(&data->obj[parse->i].cylinder.color, parse->token[5]);
	data->object_count++;
	parse->i++;

}