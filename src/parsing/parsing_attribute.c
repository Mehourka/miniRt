/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_attribute.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:48:58 by kmehour           #+#    #+#             */
/*   Updated: 2024/02/01 13:48:59 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"
#include "../include/render.h"
#include "../include/parsing.h"

void	ft_parse_rgb(t_color3 *color, char *line)
{
	double	r;
	double	g;
	double	b;
	int		j;

	j = 0;
	if (parse_comma(line) != 2)
	{
		printf("Error\n");
		printf("%s is not a valid vector", line);
		exit(1);
	}
	parse_color(line, &j, &r);
	parse_color(line, &j, &g);
	parse_color(line, &j, &b);
	*color = ft_vec3_create(r, g, b);
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
		printf("Error\n");
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
		printf("Error\n");
		printf("%s is not a ratio", nb);
		exit(1);
	}
	if (dot_digit(nb) == 0)
	{
		*ratio = ft_atod(nb);
		if (*ratio > 1 || *ratio < 0)
			ft_error_message("Out of range : Ratio must be between [0, 1]");
	}
	else
	{
		printf("Error\n");
		printf("%s is not a ratio", nb);
		exit(1);
	}
}

void	parse_length(double *length, char *nb)
{
	if (parse_comma(nb) != 0)
	{
		printf("Error\n");
		printf("%s is not a length", nb);
		exit(1);
	}
	if (dot_digit(nb) == 0)
		*length = ft_atod(nb);
	else
	{
		printf("Error\n");
		printf("%s is not a length", nb);
		exit(1);
	}
}
