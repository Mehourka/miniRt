#ifndef OBJECTS_H
# define OBJECTS_H

#include "vectors.h"

enum e_obj_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
};

typedef struct s_cylinder
{
	t_pt3 ori;
	t_color3 color;
	t_vec3	dir;
	double	r;
	double	longueur;
}	t_cylinder;

typedef struct s_sphere
{
	t_pt3 ori;
	t_color3 color;
	double	r;
}	t_sphere;

typedef struct s_plane
{
	t_pt3 ori;
	t_color3 color;
	t_vec3	dir;
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
			t_vec3 ori;
			t_color3 color;
		};
	};
}	t_obj;



typedef struct ambiant_light
{
	double		ratio;
	t_color3	color;
}	t_ambiant;

typedef struct light
{
	t_pt3	ori;
	double	ratio;
}	t_light;

#endif