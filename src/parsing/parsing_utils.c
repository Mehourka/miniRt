#include "../include/minirt.h"
#include "../include/render.h"
#include "../include/parsing.h"

void	parse_count_atribute(char *new, t_parse *parse)
{
	int	i;

	i = 0;
	while (new[i])
	{
		if (new[i] == ' ')
			parse->count++;
		while (new[i] == ' ' && new[i + 1])
			i++;
		i++;
	}
	parse->count++;
}

int	parse_comma(char *line)
{
	int	i;
	int	comma;

	i = 0;
	comma = 0;
	while (line[i])
	{
		if (line[i] == ',')
			comma++;
		i++;
	}
	return (comma);
}

int	dot_digit(char *str)
{
	int	i;
	int	dot;

	i = 0;
	dot = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		if (str[i] == '.')
		{
			i++;
			dot++;
		}
		else
			return (0);
	}
	if (dot > 1)
		return (1);
	return (0);
}

void	parse_limit(int *checker, int max, char *type)
{
	(*checker)++;
	if (*checker > max)
	{
		printf("Error\n");
		printf("Too many %s", type);
		exit(1);
	}
}

void	dot_rt(char *file)
{
	char	*new;
	int		fd;

	new = ft_strrchr(file, '.');
	if (new == NULL)
		ft_error_message("Enter a valid .rt file");
	if (ft_strncmp(new, ".rt", 4) != 0)
		ft_error_message("Enter a valid .rt file");
	else
	{
		fd = open(file, O_RDONLY);
		if (fd < 0)
			ft_error_message("Permission denied");
		close(fd);
	}
}
