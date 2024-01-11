# include "../include/minirt.h"
#include "../include/render.h"
#include "../include/parsing.h"

void	ft_parse_rgb(t_color3 *color, char *line)
{
	double	R;
	double	G;
	double	B;
	int		j;

	j = 0;
	if (parse_comma(line) != 2)
	{
		printf("%s is not a valid vector", line);
		exit(1);
	}
	parse_color(line, &j, &R);
	parse_color(line, &j, &G);
	parse_color(line, &j, &B);
	*color = ft_vec3_create(R, G, B);
}

void	ft_parse_orig_dir(t_vec3 *orig_dir, char *line, char vect)
{
	double	x;
	double	y;
	double	z;
	int		j;

	j = 0;
	if (parse_comma(line) != 2)
	{
		printf("%s is not a valid vector", line);
		exit(1);
	}
	parse_var(line, &j, &x, vect);
	parse_var(line, &j, &y, vect);
	parse_var(line, &j, &z, vect);
	*orig_dir = ft_vec3_create(x, y, z);
}

void	parse_ratio(double *ratio, char *nb)
{
	if (parse_comma(nb) != 0)
	{
		printf("%s is not a ratio", nb);
		exit(1);
	}
	if (dot_digit(nb) == 0)
	{
		*ratio = ft_atod(nb);
		if (*ratio > 1 || *ratio < 0)
		{
			printf("Ratio outside of the range of [0, 1]");
			exit(1);
		}
	}
	else
	{
		printf("%s is not a ratio", nb);
		exit(1);
	}
}

void	parse_length(double *length, char *nb)
{
	if (parse_comma(nb) != 0)
	{
		printf("%s is not a length", nb);
		exit(1);
	}
	if (dot_digit(nb) == 0)
	{
		*length = ft_atod(nb);
		if (*length > __DBL_MAX__ || *length < __DBL_MIN__)
		{
			printf("This is an error");
			exit(1);
		}
	}
	else
	{
		printf("%s is not a length", nb);
		exit(1);
	}
}