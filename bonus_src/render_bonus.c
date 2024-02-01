/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:49:07 by kmehour           #+#    #+#             */
/*   Updated: 2024/02/01 13:49:08 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit_point	ft_get_hitpoint(t_ray ray, double t, t_obj *obj)
{
	t_hit_point	pt;

	pt.f_valid = true;
	pt.distance = t;
	pt.pos = ft_ray_project(ray, t);
	pt.object = obj;
	pt.normal = ft_get_obj_normal(*obj, pt.pos);
	pt.inc_dir = ray.dir;
	if (ft_vec3_dot(ray.dir, pt.normal) > 0)
	{
		pt.normal = ft_vec3_scal_prod(pt.normal, -1.0);
		pt.f_inside = true;
	}
	else
		pt.f_inside = false;
	return (pt);
}

t_hit_point	ft_get_closest_hitpoint(t_obj *obj_list, int obj_count, t_ray ray)
{
	t_obj		*obj;
	t_hit_point	hit_pt;
	double		min_dist;
	double		t;
	int			i;

	min_dist = -1;
	hit_pt.f_valid = false;
	i = -1;
	while (i < obj_count)
	{
		i++;
		obj = &obj_list[i];
		t = ft_hit_object(*obj, ray);
		if (t > 0)
		{
			if (min_dist != -1 && t > min_dist)
				continue ;
			min_dist = t;
			hit_pt = ft_get_hitpoint(ray, t, obj);
		}
	}
	return (hit_pt);
}

int	ray_color(t_ray ray)
{
	t_data		*data;
	t_hit_point	hit_pt;

	data = get_data();
	hit_pt = ft_get_closest_hitpoint(data->obj, data->object_count, ray);
	if (hit_pt.f_valid == true)
	{
		hit_pt.color = ft_get_shade(data, hit_pt);
		return (get_color_int(hit_pt.color));
	}
	return (get_color_int(ft_vec3_cap01(ray.dir)));
}

void	ft_render_image(t_data *data)
{
	int		color_int;
	t_ray	ray;
	int		j;
	int		i;

	j = 0;
	compute_viewport(data);
	while (j < data->height)
	{
		i = 0;
		while (i < data->width)
		{
			ray = ft_compute_ray(data->cam, j, i);
			color_int = ray_color(ray);
			mlx_put_pixel(data->img, i, j, color_int);
			i++;
		}
		j++;
	}
}
