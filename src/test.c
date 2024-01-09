#include "minirt.h"

typedef union s_mat {
	struct {
		t_vec3 u;
		double u4;
		t_vec3 v;
		double v4;
		t_vec3 w;
		double w4;
		t_vec3 t;
		double t4;
	};
	double ms[16];
} t_matrix;

	// double md[4][4];

t_matrix set_matrix(t_vec3 u, t_vec3 v, t_vec3 w)
{
	t_matrix mx;
	mx.u = u;
	mx.v = v;
	mx.w = w;
	mx.t4 = 1;

	return mx;
}

void print_mat(t_matrix m)
{
	int idx;
	for(int i = 0; i < 4; i++)
	{
		printf("[");
		for (int j = 0; j < 4; j++)
		{
			int idx = i * 4 + j;
			printf(" %f", m.ms[idx]);
			// printf(" %f", m.md[i][j]);
			if (j != 4) printf(",");
		}
		printf(" ]\n");
	}

	// for (int i = 0; i < 16; i++)
	// 	printf("%f, ", m.ms[i]);
	// printf("\n");
}

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
	t_matrix A = set_matrix(nu, nv, nw);
	print_mat(A);
}
