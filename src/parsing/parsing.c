# include "../include/minirt.h"
#include "../include/render.h"
#include "../include/parsing.h"

void	create_object(t_data *data, t_parse *parse)
{
	// pour des virgules vides
	//tester trop d'objets


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
		int i = 0;
		while (parse->token[i])
			printf("%s ", parse->token[i++]);
		printf("\n");
		exit(1);
	}
}

void	parsing(char *file, t_data *data)
{
	char *line;
	int fd_rt;
	int nb_token;
	int i;
	char *new_line;
	t_parse parse;

	dot_rt(file);
	nb_token = parse_nb_token(file);
	i = 0;
	parse.A = 0;
	parse.L = 0;
	parse.C = 0;
	parse.i = 0;
	fd_rt = open(file, O_RDONLY);
	if(fd_rt < 0)
	{
		printf("Impossible to open %s", file);
		exit(1);
	}
	while (i < nb_token)
	{
		if (i >= 103)
		{
			printf("Too many arguments. MAX : 100 objects");
			exit(1);
		}
		line = get_next_line(fd_rt);
		if (line == NULL)
		{
			close(fd_rt);
			i = nb_token;
		}
		else
		{
			new_line = ft_strtrim(line, " ");
			if (new_line && new_line[0] != '\n'
				&& ft_strncmp(line, "#", 1) != 0) // Gestion des commentaires
			{
				parse_token(line, &parse);
				//ici tout est beau
				create_object(data, &parse);
				i++;
			}
			free(parse.token); // TODO: SEGFAULT quand la premiere ligne du .rt est vide/espaces/commentaire
			parse.token = NULL;
			free(line);
			free(new_line);
		}
		// Mis en commantaire, car nous ne gerons pas encore A
		/*if(parse.A ==0 || parse.C == 0 || parse.L == 0)
		{
			printf("Ambiant light, Light or Camera is missing");
			exit(1);
		}*/
	}
}
