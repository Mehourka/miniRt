#ifndef DEBUG_H
# define DEBUG_H

# include "objects.h"
# include "vectors.h"
# include "render.h"


void ft_print_hitpt(t_hit_point hp);
void ft_print_object(t_obj obj);
void ft_print_ray(t_ray ray);
void ft_print_vec3(t_vec3 vec3);
void ft_print_mat3(t_mat3 mx);
void manual_create_objects(void);
int ft_is_obstructed(t_obj *obj_list, int object_count, t_hit_point hpt, t_light light);


#endif