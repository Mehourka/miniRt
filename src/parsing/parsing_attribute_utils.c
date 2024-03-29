/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_attribute_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:48:55 by kmehour           #+#    #+#             */
/*   Updated: 2024/02/01 13:48:56 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"
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
		printf("Error\nThe RGB value of %s is invalid", line);
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
		printf("Error\n%f is an invalid number", *color);
		exit(1);
	}
}

void	parse_color(char *line, int *j, double *color)
{
	parse_nb(line, j, color);
	*color = (*color) / 255;
	if (*color > 1 || *color < 0)
		ft_error_message("Out of range : Color must be between [0, 255]");
}

void	parse_var(char *line, int *j, double *var, char vect)
{
	parse_nb(line, j, var);
	if (vect == 'd')
	{
		if (*var > 1 || *var < -1)
			ft_error_message("Out of range : Vector of direction");
	}
}

void	ft_error_message(char *str)
{
	printf("Error\n");
	printf("%s\n", str);
	exit(1);
}
