# include "../include/minirt.h"
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
	else
	{
		printf("Wrong type of argument : ");
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
		printf("%s is an empty file", file);
		exit(1);
	}
	parse->A = 0;
	parse->L = 0;
	parse->C = 0;
	parse->i = 0;
	parse->fd_rt = open(file, O_RDONLY);
	if (parse->fd_rt < 0)
	{
		printf("Impossible to open %s", file);
		exit(1);
	}
}

void	missing_env(t_parse parse)
{
	// if(parse.A == 0)
	// {
	// 	printf("Ambiant light is missing");
	// 	exit(1);
	// }
	if (parse.C == 0)
	{
		printf("Camera is missing");
		exit(1);
	}
	if (parse.L == 0)
	{
		printf("Light is missing");
		exit(1);
	}
}

void	parsing(char *file, t_data *data)
{
	t_parse	parse;

	dot_rt(file);
	parse_init(&parse, file);
	tokenization(&parse);
	missing_env(parse);
}
