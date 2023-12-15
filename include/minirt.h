#ifndef HEADER_H
#define HEADER_H

# include "libft.h"
# include <math.h>
# include "vectors.h"
# include <stdio.h>
# include <stdlib.h>
# include <MLX42/MLX42.h>
# include "get_next_line.h"

# define WIDTH 720
# define HEIGHT 480

enum e_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDRE,
};

typedef struct s_obj
{
	int		obj_type;

	t_vec3 center;
	t_vec3 color;

	double	r;
	double	longueur;
	t_vec3	direction;
}	t_obj;

typedef struct s_cam
{
	t_vec3	center;
	t_vec3	direction;
	double	angle;
}	t_cam;

typedef struct s_data
{
	mlx_t *mlx;
	mlx_image_t *img;

	t_obj	obj;
	t_cam	cam;
	double	aspect_ratio;
} t_data;

t_data *get_data();

#endif