#include "minirt.h"

void ft_print_object(t_obj obj)
{
	printf("Object : ");
	if (OBJ_SPHERE == obj.obj_type)
	{
		printf("Sphere\n");
	}
	if (OBJ_PLANE == obj.obj_type)
	{
		printf("Plane\n");
	}
	if (OBJ_CYLINDER == obj.obj_type)
	{
		printf("Cylinder\n");
	}
}

void ft_print_hitpt(t_hit_point hp)
{
	if (hp.f_valid == false)
	{
		printf("No hit\n");
		return;
	}
	ft_print_object(hp.object);
}

void ft_print_ray(t_ray ray)
{
	printf("Ray: \n");
	printf("ori : ");
	ft_print_vec3(ray.ori);
	printf("dir : ");
	ft_print_vec3(ray.dir);
	printf("\n");
}

void ft_print_vec3(t_vec3 u)
{
	printf("Vec (%.4f, %.4f, %.4f)\n", u.x, u.y, u.z);
}