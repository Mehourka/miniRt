#include "minirt.h"

void	draw_gradient(void)
{
	t_data		*data;
	float		c1;
	float		c2;
	uint32_t	j;
	uint32_t	i;

	j = 0;
	i = 0;
	data = get_data();
	while (j < data->img->height)
	{
		while (i < data->img->width)
		{
			c1 = 1.0 * i / data->img->width;
			c2 = 1.0 * j / data->img->height;
			mlx_put_pixel(data->img, i, j, norm_rgba(c1, 0, c2, 1));
			i++;
		}
		j++;
	}
}

int	get_color_int(t_color3 color)
{
	return (norm_rgba(color.x, color.y, color.z, 1));
}

t_hit_point	ft_get_hitpoint(t_ray ray, double t, t_obj *obj)
{
	t_hit_point	pt;

	pt.f_valid = true;
	pt.distance = t;
	pt.pos = ft_ray_project(ray, t);
	pt.object = obj;
	pt.normal = ft_get_obj_normal(*obj, pt.pos);
	if (ft_vec3_dot(ray.dir, pt.normal) > 0)
	{
		pt.normal = ft_vec3_scal_prod(pt.normal, -1.0);
		pt.f_inside = true;
	}
	else
		pt.f_inside = false;
	return (pt);
}

t_hit_point	ft_get_closest_hitpoint(t_obj *obj_list, int obj_count, t_ray ray)
{
	t_obj		*obj;
	t_hit_point	hit_pt;
	double		min_dist;
	double		t;

	min_dist = -1;
	hit_pt.f_valid = false;
	for (int i = 0; i < obj_count; i++)
	{
		obj = &obj_list[i];
		t = ft_hit_object(*obj, ray);
		if (t > 0)
		{
			if (min_dist != -1 && t > min_dist)
				continue ;
			min_dist = t;
			hit_pt = ft_get_hitpoint(ray, t, obj);
		}
	}
	return (hit_pt);
}

int	ray_color(t_ray ray)
{
	t_data		*data;
	t_hit_point	hit_pt;

	data = get_data();
	hit_pt = ft_get_closest_hitpoint(data->obj, data->object_count, ray);
	if (hit_pt.f_valid == true)
	{
		hit_pt.color = ft_get_shade(hit_pt);
		return (get_color_int(hit_pt.color));
	}
	return (get_color_int(ft_vec3_cap01(ray.dir)));
}

void	compute_viewport(t_data *data)
{
	const t_cam	*pcam;
	t_viewport	vp;
	double		viewport_w;
	double		viewport_h;
	t_vec3		w;
	t_vec3		u;
	t_vec3		v;

	pcam = &data->cam;
	viewport_w = tan(data->cam.angle * M_PI / 360) * 1;
	viewport_h = viewport_w * (1 / data->aspect_ratio);
	w = pcam->dir;
	u = ft_vec3_normalize(
			ft_vec3_cross_prod(w, pcam->vup));
	v = ft_vec3_cross_prod(u, w);
	vp.u = ft_vec3_scal_prod(u, viewport_w);
	vp.v = ft_vec3_scal_prod(v, -viewport_h);
	data->cam.du = ft_vec3_scal_prod(vp.u, 1.0 / data->width);
	data->cam.dv = ft_vec3_scal_prod(vp.v, 1.0 / data->height);
	vp.upper_left_corner = ft_vec3_create(0, 0, 0);
	vp.upper_left_corner.x = data->cam.ori.x + w.x - vp.u.x / 2 - vp.v.x / 2;
	vp.upper_left_corner.y = data->cam.ori.y + w.y - vp.u.y / 2 - vp.v.y / 2;
	vp.upper_left_corner.z = data->cam.ori.z + w.z - vp.u.z / 2 - vp.v.z / 2;
	data->cam.pixel00_pos = ft_vec3_add(
		ft_vec3_scal_prod(ft_vec3_add(data->cam.du, data->cam.dv), 0.5),
		vp.upper_left_corner);
}

t_ray	ft_compute_ray(t_cam cam, int row, int col)
{
	t_pt3	pixel_pos;
	t_vec3	ray_dir;

	pixel_pos = ft_vec3_add( ft_vec3_add(ft_vec3_scal_prod(cam.du, col),
			ft_vec3_scal_prod(cam.dv, row)),cam.pixel00_pos);
	ray_dir = ft_vec3_minus(pixel_pos, cam.ori);
	return (ft_ray_create(cam.ori, ray_dir));
}

void	ft_render_image(t_data *data)
{
	int		color_int;
	t_ray	ray;

	compute_viewport(data);
	for (int j = 0; j < data->height; j++)
	{
		for (int i = 0; i < data->width; i++)
		{
			ray = ft_compute_ray(data->cam, j, i);
			color_int = ray_color(ray);
			mlx_put_pixel(data->img, i, j, color_int);
		}
	}
}
