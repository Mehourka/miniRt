#include "minirt.h"

void ft_ray_print(t_ray r)
{
	printf("Ray: \n");
	printf("org \n");
	ft_vec3_print(ray.ori);
	printf("dir \n");
	ft_vec3_print(ray.dir);
	printf("\n");
}

int main(void)
{
	const int image_width = WIDTH;
	const int image_height = HEIGHT;

	t_ray ray = ft_ray_create({0, 0, 0}, {0, 0, -1});

	ft_ray_print(ray);
}
