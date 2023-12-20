# include "../include/minirt.h"
#include "../include/render.h"
#include "../include/parsing.h"

void parse_count_atribute(char *new, t_parse *parse)
{
	int i;

	i = 0;
	while(new[i])
	{
		if(new[i] == ' ')
			parse->count++;
		while(new[i] == ' '&& new[i + 1])
			i++;
		i++;
	}
	parse->count++;
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

int	dot_digit(char *str)
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

void	parse_limit(int checker, int max)
{
	checker++;
	if(checker > max)
	{
		printf("This is an error");
		exit(1);
	}
}
