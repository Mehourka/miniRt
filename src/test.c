#include "minirt.h"

typedef union u_mat3 {
		struct {
			t_vec3 i;
			t_vec3 j;
			t_vec3 k;
		};
		double mx[3][3];
} t_mat3;

void ft_ray_print(t_ray ray)
{
	printf("Ray: \n");
	printf("ori : ");
	ft_vec3_print(ray.ori);
	printf("dir : ");
	ft_vec3_print(ray.dir);
	printf("\n");
}

/*
	Creates a 3x3 Matrix from 3 column vectors a, b and c;
	example :

	a [1, 2 ,3] | b[4, 5, 6] | c[7, 8, 9]

	M => [a | b | c]

		[1, 4, 7]
	M =	[2, 5, 8]
		[3, 6, 9]

	to access an element, we use
	===> M.mx[row][column]
*/
t_mat3 ft_mat3_from_vec3(t_vec3 a, t_vec3 b, t_vec3 c)
{
	t_mat3 mx;

	mx.mx[0][0] = a.cord[0];
	mx.mx[1][0] = a.cord[1];
	mx.mx[2][0] = a.cord[2];
	mx.mx[0][1] = b.cord[0];
	mx.mx[1][1] = b.cord[1];
	mx.mx[2][1] = b.cord[2];
	mx.mx[0][2] = c.cord[0];
	mx.mx[1][2] = c.cord[1];
	mx.mx[2][2] = c.cord[2];

	return (mx);
}

t_mat3 ft_mat3_identity(void)
{
	t_vec3 a = {1, 0, 0};
	t_vec3 b = {0, 1, 0};
	t_vec3 c = {0, 0, 1};

	return ft_mat3_from_vec3(a, b, c);
}

void ft_mat3_print(t_mat3 mx)
{
	printf("Matrix: \n");
	printf("[%.2f, %.2f, %.2f]\n", mx.mx[0][0], mx.mx[1][0], mx.mx[2][0]);
	printf("[%.2f, %.2f, %.2f]\n", mx.mx[0][1], mx.mx[1][1], mx.mx[2][1]);
	printf("[%.2f, %.2f, %.2f]\n", mx.mx[0][2], mx.mx[1][2], mx.mx[2][2]);
	printf("\n");
}

t_vec3 ft_mat3_multiplication(t_mat3 A, t_vec3 u)
{
	t_vec3 new;

	new.x = ft_vec3_dot(A.i, u);
	new.y = ft_vec3_dot(A.j, u);
	new.z = ft_vec3_dot(A.k, u);

	return (new);
}

t_ray ft_ray_transform(t_ray ray, t_mat3 A, t_pt3 new_ori)
{
	return (
		ft_ray_create(
			ft_vec3_minus(ray.ori, new_ori),
			ft_mat3_multiplication(A, ray.dir)
		)
	);
}

int main(void)
{
	t_vec3 new_o = {3, 3, 3};
	t_vec3 nu = {1, 0, 0};
	t_vec3 nv = {0, 1, 0};
	t_vec3 nw = {0, 0, 1};


	t_vec3 dir = {1, 1, 0};
	t_vec3 ori = {0, 0, 0};
	t_ray oray = ft_ray_create(ori, dir);

	t_mat3 id = ft_mat3_identity();
	t_mat3 A = ft_mat3_from_vec3(nu, nv, nw);

	ft_ray_print(oray);
	printf("Transformation... \n");
	t_ray nray = ft_ray_transform(oray, A, new_o);
	ft_ray_print(nray);
}
