/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:49:09 by kmehour           #+#    #+#             */
/*   Updated: 2024/02/01 13:49:10 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color3	ft_spec_light(t_color3 init_color, t_hit_point hpt,
	t_light light, t_vec3 light_dir)
{
	t_color3	spec_light;

	spec_light = ft_bdrf(hpt, light_dir, light.color);
	spec_light = ft_vec3_add(init_color,
			ft_vec3_elem_mult(hpt.object->color, spec_light));
	return (spec_light);
}

t_color3	ft_diffuse_color(t_color3 init_color, t_hit_point hpt,
	t_light light, t_vec3 light_dir)
{
	double		brightness;
	t_color3	diffuse_color;

	brightness = ft_vec3_dot(ft_vec3_normalize(hpt.normal),
			ft_vec3_normalize(light_dir));
	brightness = fmax(0, brightness);
	diffuse_color = ft_vec3_scal_prod(light.color, brightness * light.ratio);
	diffuse_color = ft_vec3_add(init_color,
			ft_vec3_elem_mult(hpt.object->color, diffuse_color));
	return (diffuse_color);
}

t_color3	ft_get_shade(t_data *data, t_hit_point hpt)
{
	t_light		light;
	t_color3	final_color;
	t_vec3		light_dir;
	int			i;

	i = 0;
	final_color = ft_vec3_elem_mult(hpt.object->color,
			ft_vec3_scal_prod(data->ambiant.color, data->ambiant.ratio));
	while (data->light[i].ratio > 0)
	{
		light = data->light[i];
		if (!ft_is_obstructed(data->obj, data->object_count, hpt, light))
		{
			light_dir = ft_vec3_minus(light.ori, hpt.pos);
			final_color = ft_diffuse_color(final_color, hpt, light, light_dir);
			final_color = ft_spec_light(final_color, hpt, light, light_dir);
		}
		i++;
	}
	return (final_color);
}
