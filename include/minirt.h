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
	OBJ_CYLINDER,
};

typedef struct s_cylinder
{
	t_pt3 center;
	t_vec3	direction;
	double	r;
	double	longueur;
	t_color3 color;
}	t_cylinder;

typedef struct s_sphere
{
	t_pt3 center;
	double	r;
	t_color3 color;
}	t_sphere;

typedef struct s_plane
{
	t_pt3 center;
	t_vec3	direction;
	t_color3 color;
}	t_plane;

typedef struct s_obj
{
	int		obj_type;
	union
	{
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
		struct
		{
			t_vec3 center;
			t_color3 color;

		};
	};
}	t_obj;

typedef struct s_cam
{
	t_vec3	center;
	t_vec3	direction;
	double	angle;
}	t_cam;

typedef struct ambiant_light
{
	double		ratio;
	t_color3	color;
}	t_ambiant;

typedef struct light
{
	t_pt3	orig;
	double	ratio;
}	t_light;


typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_obj		obj[100];
	t_cam		cam;
	t_light		light;
	t_ambiant	ambiant;
	double		aspect_ratio;
} t_data;

t_data *get_data();
void ft_hook(void *param);
void ft_raise_error(t_data *data);
void create_objects(void);
void compute_viewport();

#endif