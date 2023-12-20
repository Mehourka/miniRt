# include "../include/minirt.h"
#include "../include/render.h"
#include "../include/parsing.h"

void parse_color(char *line, int *j, double *color)
{
	char *new;
	//TODO manage error

	new = line + *j;
	while (line[*j] != ',' && line[*j])
		(*j)++;
	if (line[*j] == ',')
	{
		line[*j] = '\0';
		(*j)++;
	}
	if (dot_digit(new) == 0 && ft_strlen(new))
		*color = ft_atod(new);
	else
	{
		printf("This is an error");
		exit(1);
	}
	if (*color > 255 || *color < 0)
	{
		printf("This is an error");
		exit(1);
	}
}

void parse_var(char *line, int *j, double *var)
{
	char *new;
	//TODO manage error

	new = line + *j;
	while (line[*j] != ',' && line[*j])
		(*j)++;
	if (line[*j] == ',')
		line[*j] = '\0';
	if (dot_digit(new) == 0)
		*var = ft_atod(new);
	else
	{
		printf("This is an error");
		exit(1);
	}
	if (*var > __DBL_MAX__ || *var < __DBL_MIN__)
	{
		printf("This is an error");
		exit(1);
	}
}