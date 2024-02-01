/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:49:42 by kmehour           #+#    #+#             */
/*   Updated: 2024/02/01 14:52:41 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_BONUS_H
# define HOOKS_BONUS_H

void	ft_nav_hook(void *param);
void	ft_render_hook(void *param);
void	ft_mouse_select(void *param);
void	ft_resize_hook(int32_t width, int32_t height, void *param);
void	ft_mouse_select_object(void *param);
void	ft_obj_prop(void *param);
void	selec_light(void *param);
void	instruction(void);
void	ft_obj_trans(void *param);
void	ft_light_trans(void *param);
void	ft_obj_rotation(void *param);

#endif