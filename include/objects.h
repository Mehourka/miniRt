#ifndef OBJECTS_H
# define OBJECTS_H

# include "vectors.h"
# include "matrix.h"

enum e_obj_type
{
	OBJ_NULL,
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
	OBJ_CONE,
	ENV_CAM,
	ENV_LIGHT
};

typedef struct s_cylinder
{
	t_pt3		ori;
	t_color3	color;
	t_mat3		transform_matrix;
	t_mat3		inverse_transfrom;
	t_vec3		dir;
	double		r;
	double		longueur;
}	t_cylinder;

typedef struct s_sphere
{
	t_pt3		ori;
	t_color3	color;
	t_mat3		transform_matrix;
	t_mat3		inverse_transfrom;
	double		r;
}	t_sphere;

typedef struct s_plane
{
	t_pt3		ori;
	t_color3	color;
	t_mat3		transform_matrix;
	t_mat3		inverse_transfrom;
	t_vec3		dir;
}	t_plane;

typedef struct s_cone
{
	t_pt3		ori;
	t_color3	color;
	t_vec3		dir;
	t_mat3		transform_matrix;
	t_mat3		inverse_transfrom;
	double		h;
	double		angle;
}	t_cone;

typedef struct s_obj
{
	int		obj_type;
	union
	{
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
		t_cone		cone;
		struct
		{
			t_vec3		ori;
			t_color3	color;
			t_vec3		dir;
			t_mat3		transform_matrix;
			t_mat3		inverse_transfrom;
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
	double		ratio;
	t_color3	color;
	t_pt3		ori;
}	t_light;

double	ft_hit_object(t_obj obj, t_ray ray);
double	ft_intersect_plane(t_plane plane, t_ray ray);
double	ft_intersect_sphere(t_sphere spehere, t_ray ray);
double	ft_intersect_cylinder(t_cylinder cylinder, t_ray ray);

t_vec3	ft_get_obj_normal(t_obj obj, t_pt3 pos);
t_vec3	ft_get_plane_normal(t_plane plane, t_pt3 pos);
t_vec3	ft_get_sphere_normal(t_sphere sphere, t_pt3 pos);
t_vec3	ft_get_cylinder_normal(t_cylinder cylinder, t_pt3 pos);

void	ft_compute_obj_matrices(t_obj *object_list, int object_count);

#endif