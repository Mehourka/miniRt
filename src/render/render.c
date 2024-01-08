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

	if (0 == ft_vec3_mod(hpt.normal))
	{
		return (1);
	}

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

t_hit_point ft_get_hitpoint(t_ray ray, double t, t_obj obj)
{
	t_hit_point pt;
	pt.f_valid = true;
	pt.distance = t;
	pt.pos = ft_ray_project(ray, t);
	pt.object = obj;
	// Normal depends on object type:
	pt.normal = ft_get_obj_normal(obj, pt.pos);

	// Flip normal if we're inside the object
	if (ft_vec3_dot(ray.dir, pt.normal) > 0)
	{
		pt.normal = ft_vec3_scal_prod(pt.normal, -1.0);
		pt.f_inside = true;
	}
	else
		pt.f_inside = false;
	return (pt);
}

t_hit_point ft_get_closest_hitpoint(t_obj *object_list, int object_count, t_ray ray)
{
	t_obj obj;
	t_hit_point hit_pt;
	double min_dist;
	double t;

	min_dist = -1;
	hit_pt.f_valid = false;
	for (int i = 0; i < object_count; i++)
	{
		obj = object_list[i];
		t = ft_hit_object(obj, ray);
		if (t > 0)
		{
			// skip if object is obstructed
			if (min_dist != -1 && t > min_dist)
				continue;
			min_dist = t;
			hit_pt = ft_get_hitpoint(ray, t, obj);
			// render selon la normal
			double brightness = ft_get_shade(hit_pt);
			hit_pt.color = ft_vec3_scal_prod(obj.color, brightness);
		}
	}
	return hit_pt;
}

int ray_color(t_ray ray)
{
	t_data *data = get_data();
	t_color3 color;
	t_hit_point hit_pt;

	hit_pt = ft_get_closest_hitpoint(data->obj, data->object_count, ray);
	if (hit_pt.f_valid == true)
		return get_color_int(hit_pt.color);
	return get_color_int(ft_vec3_cap01(ray.dir));
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

t_ray ft_compute_ray(t_cam cam, int row, int col)
{
	t_pt3 pixel_pos = ft_vec3_add(
		ft_vec3_add(
			ft_vec3_scal_prod(cam.du, col),
			ft_vec3_scal_prod(cam.dv, row)),
		cam.pixel00_pos);
	t_vec3 ray_dir = ft_vec3_normalize(
		ft_vec3_minus(pixel_pos, cam.ori));
	return (ft_ray_create(cam.ori, ray_dir));
}

void	ft_render_image()
{
	t_data	*data = get_data();
	int color_int;

	compute_viewport();

	for (int j = 0; j < HEIGHT; j++)
	{
		for (int i = 0; i < WIDTH; i++)
		{
			t_ray ray = ft_compute_ray(data->cam, j, i);
			// Render le pixel (i, j)
			color_int = ray_color(ray);
			mlx_put_pixel(data->img, i, j, color_int);
		}
	}
}
