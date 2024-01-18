#include "../include/minirt.h"
#include "../include/render.h"
#include "../include/parsing.h"

void	create_object(t_data *data, t_parse *parse)
{
	int	i;

	i = 0;
	if (ft_strncmp(parse->token[0], "A", 2) == 0)
		parse_ambiant_light(data, parse);
	else if (ft_strncmp(parse->token[0], "L", 2) == 0)
		parse_light(data, parse);
	else if (ft_strncmp(parse->token[0], "C", 2) == 0)
		parse_camera(data, parse);
	else if (ft_strncmp(parse->token[0], "cy", 3) == 0)
		parse_cylinder(data, parse);
	else if (ft_strncmp(parse->token[0], "sp", 3) == 0)
		parse_sphere(data, parse);
	else if (ft_strncmp(parse->token[0], "pl", 3) == 0)
		parse_plane(data, parse);
	else if (ft_strncmp(parse->token[0], "co", 3) == 0)
		parse_cone(data, parse);
	else
	{
		printf("Error\nWrong type of argument : ");
		while (parse->token[i])
			printf("%s ", parse->token[i++]);
		printf("\n");
		exit(1);
	}
}

void	parse_init(t_parse *parse, char *file)
{
	parse->nb_token = parse_nb_token(file);
	if (parse->nb_token == 0)
	{
		printf("Error\n");
		printf("%s is an empty file", file);
		exit(1);
	}
	parse->a = 0;
	parse->l = 0;
	parse->c = 0;
	parse->i = 0;
	parse->j = 0;
	parse->fd_rt = open(file, O_RDONLY);
	if (parse->fd_rt < 0)
	{
		printf("Error\n");
		printf("Impossible to open %s", file);
		exit(1);
	}
}

void	missing_env(t_parse parse)
{
	if (parse.a == 0)
		ft_error_message("Ambiant light is mising");
	if (parse.c == 0)
		ft_error_message("Camera is mising");
	if (parse.l == 0)
		ft_error_message("Light is mising");
}

void	parsing(char *file, t_data *data)
{
	t_parse	parse;

	(void) data;
	dot_rt(file);
	parse_init(&parse, file);
	tokenization(&parse);
	missing_env(parse);
	data->l = parse.l;
	data->selec.obj = &(data->obj[0]);
	data->selec.light = &(data->light[0]);
}
