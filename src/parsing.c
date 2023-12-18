# include "../include/minirt.h"
#include "../include/render.h"

void parse_count_atribute(char *new, t_parse *parse_struct)
{
	int i;

	i = 0;
	while(new[i])
	{
		if(new[i] == ' ')
			parse_struct->count++;
		while(new[i] == ' '&& new[i + 1])
			i++;
		i++;
	}
	parse_struct->count++;
}

void	parse_token(char *line, t_parse *parse_struct)
{
	char	*new;
	int		i;
	int		t;

	i = 0;
	parse_struct->count = 0;
	new = ft_strtrim(line, " ");
	parse_count_atribute(new, parse_struct);
	parse_struct->token_line = ft_calloc(parse_struct->count + 1, sizeof (char*));
	t = 0;
	while(new[i])
	{
		parse_struct->token_line[t] = new + i;
		while (new[i] != ' ' && new[i])
			i++;
		while (new[i] == ' ')
		{
			new[i] = '\0';
			i++;
		}
		printf("%d %s\n", t, parse_struct->token_line[t]);
		t++;
	}
}

int parse_nb_token(char *file)
{
	char *line;
	char *new_line;
	int fd_rt;
	int nb_token;

	fd_rt = open(file, O_RDONLY);
	nb_token = 0;
	if(fd_rt < 0)
	{
		printf("Impossible to open %s", file);
		close(fd_rt);
		exit(1);
	}
	while(1)
	{
		line = get_next_line(fd_rt);
		if (line == NULL)
			return(close(fd_rt), nb_token);
		new_line = ft_strtrim(line, " ");
		if (new_line[0] != '\n')
			nb_token++;
		free(line);
		free(new_line);
	}
}

int dot_digit(char *str)
{
	int i;
	int dot;

	i = 0;
	dot = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		i++;
		if(str[i] == '.')
		{
			i++;
			dot++;
		}
		else
			return(0);
	}
	if(dot > 1)
		return (1);
	return (0);
}

void parse_color(t_parse *parse_struct, int *j, double color)
{
	char *new;
	//TODO manage error

	new = parse_struct->token_line[2] + *j;
	while (parse_struct->token_line[2][*j] != ',' && parse_struct->token_line[2][*j])
		(*j)++;
	if (parse_struct->token_line[2][*j] == ',')
		parse_struct->token_line[2][*j] = '\0';
	if (dot_digit(new) == 0)
		color = ft_atod(new);
	else
	{
		printf("This is an error");
		exit(1);
	}
	if (color > 255 || color < 0)
	{
		printf("This is an error");
		exit(1);
	}
}

int	parse_comma(char *line)
{
	int i;
	int comma;

	i = 0;
	comma = 0;
	while(line[i])
	{
		if(line[i] == ',')
			comma++;
		i++;
	}
	return(comma);
}

void	parse_limit(int checker, int max)
{
	checker++;
	if(checker > max)
	{
		printf("This is an error");
		exit(1);
	}
}

void	ft_parse_rgb(t_data *data, t_parse *parse_struct)
{
	double R;
	double G;
	double B;
	int		j;

	j = 0;
	if(parse_comma(parse_struct->token_line[2]) > 2)
	{
		printf("This is an error");
		exit(1);
	}
	parse_color(parse_struct, &j, R);
	parse_color(parse_struct, &j, G);
	parse_color(parse_struct, &j, B);
	data->ambiant.color = ft_vec3_create(R, G, B);
}

void	parse_ratio(double *ratio, char *nb)
{
	if(dot_digit(nb) == 0)
	{
		*ratio = ft_atod(nb);
		if (*ratio > 1 || *ratio < -1)
		{
			printf("This is an error");
			exit(1);
		}
	}
	else
	{
		printf("This is an error");
		exit(1);
	}
}

//direction et origin
// just double



void	parse_ambiant_light(t_data *data, t_parse *parse_struct)
{
	parse_limit(parse_struct->A, 1);
	parse_ratio(&data->ambiant.ratio, parse_struct->token_line[1]);
	ft_parse_rgb(data, parse_struct);
	//regarder s'il y a du garbage apres
	//regarder l<ordre
}


void	parse_light(t_data *data, t_parse *parse_struct)
{
	parse_limit(parse_struct->L, 1);
	parse_ratio(&data->light.ratio, parse_struct->token_line[2]);

}

/*void	parse_camera(t_data *data, t_parse *parse_struct)
{
	parse_limit(parse_struct->C, 1);
}

void	parse_cylinder(t_data *data, t_parse *parse_struct, int i)
{
	data->obj[i]->;
}

void	parse_sphere(t_data *data, t_parse *parse_struct, int i)
{
	data->obj[i]->;
}

void	parse_plane(t_data *data, t_parse *parse_struct, int i)
{
	data->obj[i]->;
}*/


void	create_object(t_data *data, t_parse *parse_struct, int i)
{
	if (ft_strncmp(parse_struct->token_line[0], "A", 2) == 0)
		parse_ambiant_light(data, parse_struct);
	else if (ft_strncmp(parse_struct->token_line[0], "L", 2) == 1)
		parse_light(data, parse_struct);
	/*else if (ft_strncmp(parse_struct->token_line[0], "C", 2) == 1)
		parse_camera(data, parse_struct);
	else if (ft_strncmp(parse_struct->token_line[0], "cy", 2) == 1)
		parse_cylinder(data, parse_struct, i);
	else if (ft_strncmp(parse_struct->token_line[0], "sp", 2) == 1)
		parse_sphere(data, parse_struct, i);
	else if (ft_strncmp(parse_struct->token_line[0], "pl", 2) == 1)
		parse_plane(data, parse_struct, i);*/
}

void	parse(char *file, t_data *data)
{
	char *line;
	int fd_rt;
	int nb_token;
	int i;
	char *new_line;
	t_parse parse_struct;

	nb_token = parse_nb_token(file);
	i = 0;
	printf("nb_of token : %d\n", nb_token);
	fd_rt = open(file, O_RDONLY);
	if(fd_rt < 0)
	{
		printf("Impossible to open %s", file);
		exit(1);
	}
	parse_struct.A = 0;
	parse_struct.L = 0;
	parse_struct.C = 0;
	while (i < nb_token)
	{
		if (i == 103)
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
				//create token for the line
				parse_token(line, &parse_struct);
				//create struct with the attribute and check everything is all ok
				create_object(data, &parse_struct, i);
				//pas malloc pas de free;
				i++;
			}
			free(parse_struct.token_line);
			parse_struct.token_line = NULL;
			free(line);
			free(new_line);
		}
	}
}

int main(int argc, char **argv)
{
	if(argc != 2)
		return(printf("Wrong number of arguments"), 0);
	t_data *data = get_data();
	parse(argv[1], data);
}
