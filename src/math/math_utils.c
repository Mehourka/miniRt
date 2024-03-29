/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:48:33 by kmehour           #+#    #+#             */
/*   Updated: 2024/02/01 13:48:34 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

/*
	brief: caps a number betwwen [0, 1]
*/
double	ft_cap01(double f)
{
	return (fmin(1, (fmax(0, f))));
}
