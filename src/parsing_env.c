# include "../include/minirt.h"
#include "../include/render.h"
#include "../include/parsing.h"

void	parse_ambiant_light(t_data *data, t_parse *parse)
{
	parse_limit(parse->A, 1);
	parse_ratio(&data->ambiant.ratio, parse->token[1]);
	ft_parse_rgb(&data->ambiant.color, parse->token[2]);
	//regarder s'il y a du garbage apres
	//regarder l<ordre
}

void	parse_light(t_data *data, t_parse *parse)
{
	parse_limit(parse->L, 1);
	ft_parse_orig_dir(&data->light.orig, parse->token[1]);
	parse_ratio(&data->light.ratio, parse->token[2]);

}

void	parse_camera(t_data *data, t_parse *parse)
{
	parse_limit(parse->C, 1);
	ft_parse_orig_dir(&data->cam.center, parse->token[1]);
	ft_parse_orig_dir(&data->cam.direction, parse->token[2]);
	parse_length(&data->cam.angle, parse->token[3]);
	//TODO cas particulier 0-180
	if(data->cam.angle >180 || &data->cam.angle < 0)
	{
		printf("This is an error");
		exit(1);
	}
}
