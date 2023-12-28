#ifndef HEADER_H
#define HEADER_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <MLX42/MLX42.h>
# include "libft.h"
# include "get_next_line.h"
# include "vectors.h"
# include "hooks.h"
# include "render.h"
# include "objects.h"

# define WIDTH 	256
# define HEIGHT	256

typedef struct s_hit_point
{
	t_pt3	pos;
	t_vec3	normal;
	double	distance;
}	t_hit_point;

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_obj		obj[100];
	t_cam		cam;
	t_light		light;
	t_ambiant	ambiant;
	double		aspect_ratio;
	int			object_count;
} t_data;

t_data *get_data();
void ft_raise_error(t_data *data);
void create_objects(void);
void compute_viewport();

#endif