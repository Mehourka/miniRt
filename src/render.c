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
	static int i = 0;
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
	return (-b - sqrt(discriminant)) / (2.0 * a);
}

int get_color_int(t_color3 color)
{
	return (norm_rgba(
		color.x,
		color.y,
		color.z,
		1
	));
}

double ft_get_shade(t_hit_point hpt)
{
	t_data *data = get_data();

	t_vec3 light_dir = ft_vec3_minus(
		data->light.ori,
		hpt.pos
	);

	double	i = ft_vec3_dot(
		ft_vec3_normalize(hpt.normal),
		ft_vec3_normalize(light_dir)
	);
	return (i);
}

int ray_color(t_ray ray)
{
	t_data *data = get_data();
	t_vec3 u = ft_vec3_normalize(ray.dir);
	double a = 0.5 * (u.y + 1);
	t_color3 col  = u;
	t_hit_point	hit_pt;

	double min_dist = -1;

	for (int i = 0; i < 3; i++)
	{
		double t = hit_sphere(data->obj[i], ray);
		if (t >= 0)
		{
			t_vec3 n = ft_vec3_scal_prod(
				ft_vec3_minus(
					ft_ray_project(ray, t),
					data->obj[i].ori
				),
				1 / data->obj[i].sphere.r
			);
			// n = ft_vec3_scal_prod(
			// 	ft_vec3_add_scal(n, 1),
			// 	0.5
			// );

			hit_pt.normal = n;
			hit_pt.pos = ft_ray_project(ray, t);
			// render selon la normal
			if (min_dist == -1 || t < min_dist)
			{
				// col = get_col3(data->obj[i].color);
				// col = norm_rgba(n.x, n.y, n.z, 1);
				double brightness = ft_get_shade(hit_pt);
				col = ft_vec3_scal_prod(data->obj[i].color, brightness);
				min_dist = t;
			}
		}
	}

	// return (norm_rgba(col.x, col.y, col.z, 1));
	return get_color_int(col);
}

void compute_viewport()
{
	t_data	*data = get_data();
	t_cam	*pcam = &data->cam;
	t_viewport vp;
	double viewport_h = 2;

	// Trouver la hauteur/largeur du viewport
	double viewport_w = viewport_h * data->aspect_ratio;

	t_vec3 w = ft_vec3_normalize(
		ft_vec3_minus(pcam->dir, pcam->ori)
	);
	t_vec3 u = ft_vec3_normalize(
		ft_vec3_cross_prod(w, pcam->vup)
	);
	t_vec3 v = ft_vec3_normalize(
		ft_vec3_cross_prod(u, w)
	);


	// determiner les delta
	vp.u = ft_vec3_scal_prod(u, viewport_w);
	vp.v = ft_vec3_scal_prod(v, -viewport_h);
	data->cam.du = ft_vec3_scal_prod(vp.u, 1.0/WIDTH);
	data->cam.dv = ft_vec3_scal_prod(vp.v, 1.0/HEIGHT);

	// determier upper left
	// TODO : check le signe de cam.direction
	vp.upper_left_corner = ft_vec3_create(0, 0, 0);
	vp.upper_left_corner.x = data->cam.ori.x + w.x - vp.u.x / 2 - vp.v.x / 2;
	vp.upper_left_corner.y = data->cam.ori.y + w.y - vp.u.y / 2 - vp.v.y / 2;
	vp.upper_left_corner.z = data->cam.ori.z + w.z - vp.u.z / 2 - vp.v.z / 2;

	// trouver le Pixel00
	data->cam.pixel00_pos = ft_vec3_add(
		ft_vec3_scal_prod(ft_vec3_add(vp.du, vp.dv), 0.5),
		vp.upper_left_corner);
}

void	ft_render_image()
{
	t_data	*data = get_data();

	compute_viewport();

	for (int j = 0; j < HEIGHT; j++)
	{
		for (int i = 0; i < WIDTH; i++)
		{
			t_pt3 pixel_pos = ft_vec3_add(
				ft_vec3_add(
					ft_vec3_scal_prod(data->cam.du, i),
					ft_vec3_scal_prod(data->cam.dv, j)),
					data->cam.pixel00_pos);
			t_vec3 ray_dir = ft_vec3_minus(pixel_pos, data->cam.ori);
			t_ray ray = ft_ray_create(data->cam.ori, ray_dir);

			// Render le pixel (i, j)
			int color = ray_color(ray);
			mlx_put_pixel(data->img, i, j, color);
		}
	}
}
