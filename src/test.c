#include <stdio.h>
#include "minirt.h"
# include "vectors.h"



int main (void)
{
	const int image_width = WIDTH;
	const int image_height = HEIGHT;

	// Setup mlx data
	t_data *data = get_data();
	create_objects();

	printf("Cam direction : ");
	ft_vec3_print(
		data->cam.dir
	);

	// rotate cam.dir
	double angle = ft_deg_to_rad(90);
	data->cam.dir = rotate_yaxis(data->cam.dir, -angle);

	printf("Cos(%f) = %f\n", angle, sin(angle));
	ft_vec3_print(
		data->cam.dir
	);

	
}
