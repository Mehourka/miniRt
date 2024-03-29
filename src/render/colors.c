/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:49:05 by kmehour           #+#    #+#             */
/*   Updated: 2024/02/01 13:49:06 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include <math.h>

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	norm_rgba(float r, float g, float b, float a)
{
	r = fmin(fmax(r, 0), 1) * 255;
	g = fmin(fmax(g, 0), 1) * 255;
	b = fmin(fmax(b, 0), 1) * 255;
	a = fmin(fmax(a, 0), 1) * 255;
	return ((int)r << 24 | (int)g << 16 | (int)b << 8 | (int)a);
}
