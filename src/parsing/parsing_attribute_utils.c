# include "../include/minirt.h"
#include "../include/render.h"
#include "../include/parsing.h"

void	parse_nb(char *line, int *j, double *color)
{
	char	*new;

	new = line + *j;
	if (line[*j] != ',' && line[*j] && line[*j] != ' ')
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
		*color = ft_atod(new);
	else
	{
		printf("%f is an invalid number", *color);
		exit(1);
	}
}

void	parse_color(char *line, int *j, double *color)
{
	parse_nb(line, j, color);
	*color = (*color)/255;
	if (*color > 1 || *color < 0)
	{
		printf("Ratio outside of the range of [0, 255]");
		exit(1);
	}
}

void	parse_var(char *line, int *j, double *var, char vect)
{
	parse_nb(line, j, var);
	if (vect == 'd')
	{
		if (*var > 1 || *var < -1)
		{
			printf("Out of range");
			exit(1);
		}
	}
}
