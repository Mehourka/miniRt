/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:49:25 by kmehour           #+#    #+#             */
/*   Updated: 2024/02/01 13:49:26 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_resize_hook(int32_t width, int32_t height, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	data->height = height;
	data->width = width;
	data->aspect_ratio = (float) data->width / data->height;
	mlx_delete_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	if (!(data->img))
		ft_raise_error(data);
	ft_memset(data->img->pixels, 255, sizeof(int32_t)
		* data->height * data->width);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	instruction();
}
/*
	brief: mlx loop hook for rendering
*/

void	ft_render_hook(void *param)
{
	t_data	*data;

	data = param;
	ft_render_image(data);
}
