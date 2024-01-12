#ifndef MINIRT_H
#define MINIRT_H

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
# include "matrix.h"
# include "debug.h"

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
	int			height;
	int			width;
} t_data;

t_data *get_data();
void 	compute_viewport(t_data *data);
void	ft_render_image(t_data *data);
void ft_raise_error(t_data *data);

#endif