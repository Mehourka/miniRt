# include "../include/minirt.h"
#include "../include/render.h"
#include "../include/parsing.h"

void parse_color(char *line, int *j, double *color)
{
	char *new;
	//TODO manage error

	new = line + *j;
	if(line[*j] != ',' && line[*j] && line[*j] != ' ')
	{
		while (line[*j] != ',' && line[*j] && line[*j] != ' ')
			(*j)++;
	}
	else
	{
		printf("The RGB value of %s is invalid", line);
		exit(1);
	}
	if (line[*j] == ',')
	{
		line[*j] = '\0';
		(*j)++;
	}
	if (dot_digit(new) == 0 && ft_strlen(new))
		*color = (ft_atod(new))/255;
	else
	{
		printf("%f is an invalid number", *color);
		exit(1);
	}
	if (*color > 255 || *color < 0)
	{
		printf("Ratio outside of the range of [0, 255]");
		exit(1);
	}
}

void parse_var(char *line, int *j, double *var)
{
	char *new;
	//TODO manage error

	new = line + *j;
	if(line[*j] != ',' && line[*j] && line[*j] != ' ')
	{
		while (line[*j] != ',' && line[*j] && line[*j] != ' ')
			(*j)++;
	}
	else
	{
		printf("The origin or direction value of %s is invalid", line);
		exit(1);
	}
	while (line[*j] != ',' && line[*j])
		(*j)++;
	if (line[*j] == ',')
	{
		line[*j] = '\0';
		(*j)++;
	}
	if (dot_digit(new) == 0)
		*var = ft_atod(new);
	else
	{
		printf("%f is an invalid number", *var);
		exit(1);
	}
	if (*var > __DBL_MAX__ || *var < -__DBL_MAX__)
	{
		printf("This is an error");
		exit(1);
	}
}