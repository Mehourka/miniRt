/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:49:07 by kmehour           #+#    #+#             */
/*   Updated: 2024/02/01 17:56:30 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_color_int(t_color3 color)
{
	return (norm_rgba(color.x, color.y, color.z, 1));
}

void	compute_viewport(t_data *data)
{
	t_viewport	vp;
	double		viewport_w;
	double		viewport_h;
	t_vec3		u;
	t_vec3		w;

	viewport_w = tan(data->cam.angle * M_PI / 360) * 1;
	viewport_h = viewport_w * (1 / data->aspect_ratio);
	w = data->cam.dir;
	u = ft_vec3_normalize(
			ft_vec3_cross_prod(w, data->cam.vup));
	vp.u = ft_vec3_scal_prod(u, viewport_w);
	vp.v = ft_vec3_scal_prod(ft_vec3_cross_prod(u, w), -viewport_h);
	data->cam.du = ft_vec3_scal_prod(vp.u, 1.0 / data->width);
	data->cam.dv = ft_vec3_scal_prod(vp.v, 1.0 / data->height);
	vp.upper_left_corner = ft_vec3_create(0, 0, 0);
	vp.upper_left_corner.x = data->cam.ori.x + w.x - vp.u.x / 2 - vp.v.x / 2;
	vp.upper_left_corner.y = data->cam.ori.y + w.y - vp.u.y / 2 - vp.v.y / 2;
	vp.upper_left_corner.z = data->cam.ori.z + w.z - vp.u.z / 2 - vp.v.z / 2;
	data->cam.pixel00_pos = ft_vec3_add(
			ft_vec3_scal_prod(ft_vec3_add(data->cam.du, data->cam.dv), 0.5),
			vp.upper_left_corner);
}

t_ray	ft_compute_ray(t_cam cam, int row, int col)
{
	t_pt3	pixel_pos;
	t_vec3	ray_dir;

	pixel_pos = ft_vec3_scal_prod(cam.dv, row);
	pixel_pos = ft_vec3_add(ft_vec3_scal_prod(cam.du, col), pixel_pos);
	pixel_pos = ft_vec3_add(pixel_pos, cam.pixel00_pos);
	ray_dir = ft_vec3_minus(pixel_pos, cam.ori);
	return (ft_ray_create(cam.ori, ray_dir));
}
