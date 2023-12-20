#include "render.h"

void draw_gradient(t_data *data)
{
	mlx_image_t *image = data->img;

	for (int j = 0; j < image->height; j++)
	{
		for (int i = 0; i < image->width; i++)
		{
			float c1 = 1.0 * i / image->width;
			float c2 = 1.0 * j / image->height;
			mlx_put_pixel(image, i, j, norm_rgba(c1, 0, c2, 1));
		}
	}
}

void gen_p3_image(t_data *data)
{
	const int image_width = data->img->height;
	const int image_height = data->img->width;
	uint8_t *buffer = data->img->pixels;

	// Render
	printf("P3\n%i %i\n255\n", image_width, image_height);
	for (int j = 0; j < image_height; j++)
	{
		for (int i = 0; i < image_width; i++)
		{
			int pos = (i + j * image_width) * sizeof(uint8_t);
			printf("%i %i %i\n",
				buffer[pos],
				buffer[pos + 1],
				buffer[pos + 2]);
		}
	}
}

double hit_sphere(t_obj obj, t_ray ray)
{
	t_vec3 oc = ft_vec3_minus(ray.orig, obj.sphere.ori);

	// TODO: optimize by replacing dot products with len*len
	double a = ft_vec3_dot(ray.dir, ray.dir);
	double b = ft_vec3_dot(
		ft_vec3_scal_prod(ray.dir, 2.0),
		oc);
	double c =	ft_vec3_dot(oc, oc) - pow(obj.sphere.r, 2);

	double discriminant = b*b - 4*a*c;
	if (discriminant < 0 || a == 0)
		return (-1);
	return (-b - (discriminant)) / (2.0 * a);
}

int ray_color(t_ray ray)
{
	t_data *data = get_data();
	t_vec3 u = ft_vec3_normalize(ray.dir);
	double a = 0.5 * (u.y + 1);
	t_vec3 col1 = ft_vec3_create(0.2, 0.2, 0.4);
	t_vec3 col2 = ft_vec3_create(0.2, 0.6, 0.7);
	t_vec3 col  = ft_vec3_add(
		ft_vec3_scal_prod(col1, 1.0 - a),
		ft_vec3_scal_prod(col2, a)
	);

	double t = hit_sphere(data->obj[0], ray);
	if (t >= 0)
	{
		// Calcule la normale
		t_vec3 n = ft_vec3_scal_prod(
			ft_vec3_minus(
				ft_ray_project(ray, t),
				data->obj[0].ori
			),
			1 / data->obj[0].sphere.r
		);
		n = ft_vec3_scal_prod(
			ft_vec3_add_scal(n, 1),
			0.5
		);
		// render selon la normal
		return norm_rgba(n.x, n.y, n.z, 1);
	}
	// return (norm_rgba(col.x, col.y, col.z, 1));
	return (norm_rgba(u.x, u.y, u.z, 1));
}

void compute_viewport()
{
	t_data *data = get_data();
	t_viewport vp;
	double viewport_h = 3                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 ;

	// Trouver la hauteur/largeur du viewport
	double viewport_w = viewport_h * data->aspect_ratio;
	// printf("%d %d Aspect ratio : %f\n",WIDTH, HEIGHT, data->aspect_ratio);
	// printf("Viewport dimensions : (%f x %f)\n", viewport_w, viewport_h);

	// determiner les delta
	vp.u = ft_vec3_create(0, 0, viewport_w);
	vp.v = ft_vec3_create(0, -viewport_h, 0);
	vp.du = ft_vec3_scal_prod(vp.u, 1.0/WIDTH);
	vp.dv = ft_vec3_scal_prod(vp.v, 1.0/HEIGHT);

	// determier upper left
	// TODO : check le signe de cam.direction
	vp.upper_left_corner = ft_vec3_create(0, 0, 0);
	vp.upper_left_corner.x = data->cam.ori.x + data->cam.dir.x - vp.u.x / 2 - vp.v.x / 2;
	vp.upper_left_corner.y = data->cam.ori.y + data->cam.dir.y - vp.u.y / 2 - vp.v.y / 2;
	vp.upper_left_corner.z = data->cam.ori.z + data->cam.dir.z - vp.u.z / 2 - vp.v.z / 2;

	// trouver le Pixel00
	t_vec3 pixel00 = ft_vec3_add(
		ft_vec3_scal_prod(ft_vec3_add(vp.du, vp.dv), 0.5),
		vp.upper_left_corner);
	
	// DEBUG
	printf("Viewport axes: ");
	ft_vec3_print(vp.u);
	ft_vec3_print(vp.v);

	// loop
	for (int j = 0; j < HEIGHT; j++)
	{
		for (int i = 0; i < WIDTH; i++)
		{
			t_pt3 pixel_pos = ft_vec3_add(
				ft_vec3_add(
					ft_vec3_scal_prod(vp.du, i),
					ft_vec3_scal_prod(vp.dv, j)
				),
				pixel00
			);
			t_vec3 ray_dir = ft_vec3_minus(
				pixel_pos,
				data->cam.ori);
			t_ray ray = ft_ray_create(data->cam.ori, ray_dir);

			// Render le pixel (i, j)
			int color = ray_color(ray);
			mlx_put_pixel(data->img, i, j, color);
		}
	}
	// compute rays
}

