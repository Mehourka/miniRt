/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:48:41 by kmehour           #+#    #+#             */
/*   Updated: 2024/02/01 13:48:42 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	ft_vec3_create(double x, double y, double z)
{
	t_vec3	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_vec3	ft_vec3_add(t_vec3 u, t_vec3 v)
{
	t_vec3	new;

	new.x = u.x + v.x;
	new.y = u.y + v.y;
	new.z = u.z + v.z;
	return (new);
}

t_vec3	ft_vec3_minus(t_vec3 u, t_vec3 v)
{
	t_vec3	new;

	new.x = u.x - v.x;
	new.y = u.y - v.y;
	new.z = u.z - v.z;
	return (new);
}

/*
	brief: element-wise multiplication of vector components
*/
t_vec3	ft_vec3_elem_mult(t_vec3 u, t_vec3 v)
{
	t_vec3	w;

	w.x = u.x * v.x;
	w.y = u.y * v.y;
	w.z = u.z * v.z;
	return (w);
}

t_vec3	ft_vec3_scal_prod(t_vec3 u, double k)
{
	t_vec3	new;

	new.x = u.x * k;
	new.y = u.y * k;
	new.z = u.z * k;
	return (new);
}
