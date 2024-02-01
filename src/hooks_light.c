/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:49:21 by kmehour           #+#    #+#             */
/*   Updated: 2024/02/01 13:49:22 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	selec_light(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_1))
		data->selec.light = &data->light[0];
	else if (mlx_is_key_down(data->mlx, MLX_KEY_2))
	{
		if (data->l >= 2)
			data->selec.light = &data->light[0];
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_3))
	{
		if (data->l >= 3)
			data->selec.light = &data->light[0];
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_4))
	{
		if (data->l >= 4)
			data->selec.light = &data->light[0];
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_5))
	{
		if (data->l >= 5)
			data->selec.light = &data->light[0];
	}
}

void	ft_light_trans(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_I))
		data->selec.light->ori.x += 0.1;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_K))
		data->selec.light->ori.x -= 0.1;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_J))
		data->selec.light->ori.y += 0.1;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_L))
		data->selec.light->ori.y -= 0.1;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_U))
		data->selec.light->ori.z += 0.1;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_O))
		data->selec.light->ori.z -= 0.1;
}
