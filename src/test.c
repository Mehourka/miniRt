#include <stdio.h>
# include "vectors.h"

int main (void)
{
	t_vec3 u = {1, 2, 3};
	t_vec3 v = {10, 20, 30};

	t_vec3 result;

	u = ft_vec3_create(4, 5, 6);
	ft_vec3_print(
		ft_vec3_add(
			ft_vec3_create(1, 2, 3),
			ft_vec3_create(3, 2, 1)
		)
	);


}