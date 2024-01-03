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

double ft_hit_object(t_obj obj, t_ray ray);
double ft_intersect_plane(t_plane plane, t_ray ray);
double ft_intersect_sphere(t_sphere spehere, t_ray ray);
double ft_intersect_cylinder(t_cylinder cylinder, t_ray ray);

t_vec3 ft_get_obj_normal(t_obj obj, t_pt3 pos);
t_vec3 ft_get_plane_normal(t_plane plane, t_pt3 pos);
t_vec3 ft_get_sphere_normal(t_sphere sphere, t_pt3 pos);
t_vec3 ft_get_cylinder_normal(t_cylinder cylinder, t_pt3 pos);

#endif