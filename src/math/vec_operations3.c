/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_operations3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:48:46 by kmehour           #+#    #+#             */
/*   Updated: 2024/02/01 13:48:47 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	ft_ray_create(t_pt3 origine, t_vec3 direction)
{
	t_ray	ray;

	ray.ori = origine;
	ray.dir = direction;
	return (ray);
}

t_pt3	ft_ray_project(t_ray ray, double t)
{
	return (ft_vec3_add(ray.ori,
			ft_vec3_scal_prod(ray.dir, t)));
}

t_vec3	ft_vec3_add_scal(t_vec3 u, double k)
{
	t_vec3	new;

	new.x = u.x + k;
	new.y = u.y + k;
	new.z = u.z + k;
	return (new);
}

/*
	brief: Scales the values of a vector between 0 and 1;
*/
t_vec3	ft_vec3_cap01(t_vec3 u)
{
	u.x = ft_cap01(u.x);
	u.y = ft_cap01(u.y);
	u.z = ft_cap01(u.z);
	return (u);
}
