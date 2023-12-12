# include "header.h"

int main(void)
{
	t_vect3 *u;
	t_vect3 *v;
	t_vect3 *res;
	double  double_res;
	
	u = ft_vect3_create(1, 0 , 0);
	v = ft_vect3_create(0, 1, 0);

	// res = ft_vect3_cross_prod(u, v);
	// ft_vect3_print(res);

	double_res = ft_vect3_get_angle(u, v);
	printf("Angle : %f\n", double_res / M_PI * 180);
}