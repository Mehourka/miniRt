#ifndef HOOKS_H
#define HOOKS_H

void	ft_nav_hook(void *param);
void	ft_render_hook(void *param);
void ft_mouse_select(void *param);
void ft_resize_hook(int32_t width, int32_t height, void* param);

#endif