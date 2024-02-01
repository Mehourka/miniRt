/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_operations2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:48:44 by kmehour           #+#    #+#             */
/*   Updated: 2024/02/01 13:48:45 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	ft_vec3_mod(t_vec3 u)
{
	return (sqrt((u.x * u.x) + (u.y * u.y) + (u.z * u.z)));
}

t_vec3	ft_vec3_normalize(t_vec3 u)
{
	double	mod;

	mod = ft_vec3_mod(u);
	if (mod)
		return (ft_vec3_scal_prod(u, 1 / mod));
	return (u);
}

double	ft_vec3_dot(t_vec3 u, t_vec3 v)
{
	double	res;

	res = (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
	return (res);
}

t_vec3	ft_vec3_cross_prod(t_vec3 u, t_vec3 v)
{
	double	i;
	double	j;
	double	k;

	i = u.y * v.z - u.z * v.y;
	j = u.z * v.x - u.x * v.z;
	k = u.x * v.y - u.y * v.x;
	return (ft_vec3_create(i, j, k));
}

double	ft_vec3_get_angle(t_vec3 u, t_vec3 v)
{
	double	num;
	double	denom;

	num = ft_vec3_dot(u, v);
	denom = ft_vec3_mod(u) * ft_vec3_mod(v);
	if (denom == 0)
		return (0);
	return (acos(num / denom));
}
