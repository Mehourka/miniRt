/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atod.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:49:11 by kmehour           #+#    #+#             */
/*   Updated: 2024/02/01 13:49:12 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"
#include "../include/parsing.h"

// Ascii to double

static int	decimal(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] && str[i] != '.')
		i++;
	if (str[i] == '.')
		i++;
	while (str[i + count] && str[i + count] != '.')
		count++;
	return (count);
}

double	ft_atod(char *str)
{
	int		i;
	double	nb;
	int		multiple;

	i = 0;
	nb = 0;
	multiple = 1;
	if (!str)
		return (0);
	if (str[i] == '-')
	{
		i++;
		multiple = -1;
	}
	while (((str[i] >= '0' && str[i] <= '9') || str[i] == '.') && str[i] != ',')
	{
		if (str[i] != '.')
			nb = nb * 10 + str[i] - 48;
		i++;
	}
	if (decimal(str) != 0)
		nb = nb / pow(10, decimal(str));
	if (str[i])
		ft_error_message("Error with atod");
	return (multiple * nb);
}
