#include "minirt.h"

void ft_ray_print(t_ray ray);

int main(void)
{
	t_vec3 new_o = {3, 3, 3};
	t_vec3 nu = {1, 2, 3};
	t_vec3 nv = {4, 5, 6};
	t_vec3 nw = {7, 8, 9};


	t_vec3 dir = {1,1, 1};
	t_vec3 ori = {4, 0, 0};
	t_ray oray = ft_ray_create(ori, dir);

	t_mat3 id = ft_mat3_identity();
	t_mat3 A = ft_mat3_from_vec3(nu, nv, nw);

	// ft_ray_print(oray);
	// t_ray nray = ft_ray_transform(oray, A, new_o);
	// ft_ray_print(nray);
	ft_vec3_print(dir);
	printf("Transformation... \n");
	dir = ft_mat3_multiplication(A, dir);
	ft_vec3_print(dir);
}
