#include <stdio.h>
# include "vectors.h"

int main (void)
{
	t_pt3 ori = ft_vec3_create(0, 0, 0);
	t_vec3 dir = ft_vec3_create(1, 1, 0);
	t_ray ray = ft_ray_create(ori, dir);

	ft_vec3_print(
		ft_ray_project(ray, 3)
	);
	printf();
}
