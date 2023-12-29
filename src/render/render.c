#include "minirt.h"

void draw_gradient()
{
	t_data *data = get_data();
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

void gen_p3_image()
{
	t_data *data = get_data();
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

	double min_dist = -1;

	for (int i = 0; i < data->object_count; i++)
	{
		double t = ft_hit_object(data->obj[i], ray);
		if (t > 0)
		{
			// skip if object is obstructed
			if (min_dist != -1 && t > min_dist)
				continue;
			min_dist = t;
			t_hit_point	hit_pt;
			t_vec3 n = ft_vec3_scal_prod(
				ft_vec3_minus(
					ft_ray_project(ray, t),
					data->obj[i].ori
				),
				1 / data->obj[i].sphere.r
			);

			hit_pt.normal = n;
			hit_pt.pos = ft_ray_project(ray, t);
			// render selon la normal
			double brightness = 1;
			brightness = ft_get_shade(hit_pt);
			col = ft_vec3_scal_prod(data->obj[i].color, brightness);
		}
	}
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

	t_vec3 w = ft_vec3_normalize(pcam->dir);
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
		ft_vec3_scal_prod(ft_vec3_add(data->cam.du, data->cam.dv), 0.5),
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
