#ifndef HOOKS_H
#define HOOKS_H

void	ft_nav_hook(void *param);
void	ft_render_hook(void *param);
void	ft_mouse_select(void *param);
void	ft_resize_hook(int32_t width, int32_t height, void* param);
void	ft_mouse_select_object(void *param);
void	ft_obj_prop(void *param);
void	selec_light(void *param);
void	instruction(void);
void	ft_obj_trans(void *param);
void	ft_light_trans(void *param);
void ft_nav_obj_rotation(void *param);

#endif