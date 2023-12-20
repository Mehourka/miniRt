# include "../include/minirt.h"
#include "../include/render.h"
#include "../include/parsing.h"

void	create_object(t_data *data, t_parse *parse)
{
	if (ft_strncmp(parse->token[0], "A", 2) == 0)
		parse_ambiant_light(data, parse);
	else if (ft_strncmp(parse->token[0], "L", 2) == 1)
		parse_light(data, parse);
	else if (ft_strncmp(parse->token[0], "C", 2) == 1)
		parse_camera(data, parse);
	else if (ft_strncmp(parse->token[0], "cy", 3) == 1)
		parse_cylinder(data, parse);
	else if (ft_strncmp(parse->token[0], "sp", 3) == 1)
		parse_sphere(data, parse);
	else if (ft_strncmp(parse->token[0], "pl", 3) == 1)
		parse_plane(data, parse);
	//else
		//ft_error();
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
	printf("nb_of token : %d\n", nb_token);
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
			if (new_line[0] != '\n')
			{
				parse_token(line, &parse);
				create_object(data, &parse);
				i++;
			}
			free(parse.token);
			parse.token = NULL;
			free(line);
			free(new_line);
		}
	}
}

// int	main(int argc, char **argv)
// {
// 	if(argc != 2)
// 		return(printf("Wrong number of arguments"), 0);
// 	t_data *data = get_data();
// 	parsing(argv[1], data);
// }
