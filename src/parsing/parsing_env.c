#include "../include/minirt.h"
#include "../include/render.h"
#include "../include/parsing.h"

void	parse_ambiant_light(t_data *data, t_parse *parse)
{
	parse_limit(&parse->A, 1, "Ambiant light");
	if (parse->count != 3)
	{
		printf("Error\n");
		printf("Wrong number of attribute for %s", parse->token[0]);
		exit(1);
	}
	parse_ratio(&data->ambiant.ratio, parse->token[1]);
	ft_parse_rgb(&data->ambiant.color, parse->token[2]);
	free(parse->token[0]);
}

void	parse_light(t_data *data, t_parse *parse)
{
	parse_limit(&parse->L, 5, "Light");
	if (parse->count != 4)
	{
		printf("Error\n");
		printf("Wrong number of attribute for %s", parse->token[0]);
		exit(1);
	}
	ft_parse_orig_dir(&data->light[parse->l].ori, parse->token[1], 'o');
	parse_ratio(&data->light[parse->l].ratio, parse->token[2]);
	ft_parse_rgb(&data->light[parse->l].color, parse->token[3]);
	parse->l++;
	free(parse->token[0]);
}

void	parse_camera(t_data *data, t_parse *parse)
{
	parse_limit(&parse->C, 1, "Camera");
	if (parse->count != 4)
	{
		printf("Error\n");
		printf("Wrong number of attribute for %s", parse->token[0]);
		exit(1);
	}
	ft_parse_orig_dir(&data->cam.ori, parse->token[1], 'o');
	ft_parse_orig_dir(&data->cam.dir, parse->token[2], 'd');
	data->cam.dir = ft_vec3_normalize(data->cam.dir);
	parse_length(&data->cam.angle, parse->token[3]);
	if (data->cam.angle == 180)
		data->cam.angle = 179.99999;
	else if (data->cam.angle == 0)
		data->cam.angle = 0.00001;
	else if (data->cam.angle > 180 || data->cam.angle < 0)
		ft_error_message("Out of range : Cam angle must be between [0, 180]");
	data->cam.vup = ft_vec3_create(0, 1, 0);
	free(parse->token[0]);
}
