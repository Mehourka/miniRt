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
		printf("Error\n");
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
		printf("Error\n");
		printf("%s is an empty file", file);
		exit(1);
	}
	parse->A = 0;
	parse->L = 0;
	parse->C = 0;
	parse->i = 0;
	parse->l = 0;
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
	// if(parse.A == 0)
	// ft_error_message("Ambiant light is mising");
	if (parse.C == 0)
		ft_error_message("Camera is mising");
	if (parse.L == 0)
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
	data->L = parse.L;
	/*printf("cam\n");
	ft_print_vec3(data->cam.dir);
	ft_print_vec3(data->cam.ori);
	printf("%f\n", data->cam.angle);
	printf("light\n");
	ft_print_vec3(data->light.ori);
	printf("%f\n", data->light.ratio);
	printf("object\n");
	int i = 0;
	while(i < parse.nb_token - 6)
	{
		printf("%i\n", data->obj[i].obj_type);
		if(data->obj[i].obj_type == OBJ_PLANE)
		{
			ft_print_vec3(data->obj[i].plane.ori);
			ft_print_vec3(data->obj[i].plane.dir);
			ft_print_vec3(data->obj[i].plane.color);
		}
		if(data->obj[i].obj_type == OBJ_CYLINDER)
		{
			ft_print_vec3(data->obj[i].cylinder.ori);
			ft_print_vec3(data->obj[i].cylinder.dir);
			printf("%f\n", data->obj[i].cylinder.r);
			printf("%f\n", data->obj[i].cylinder.longueur);
			ft_print_vec3(data->obj[i].cylinder.color);
		}
		if(data->obj[i].obj_type == OBJ_SPHERE)
		{
			ft_print_vec3(data->obj[i].sphere.ori);
			printf("%f\n", data->obj[i].sphere.r);
			ft_print_vec3(data->obj[i].sphere.color);
		}
		i++;
	}*/
}
