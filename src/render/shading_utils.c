#include "minirt.h"

/*
	result = (col1 + col2 * intensity).normalized()
*/
t_color3	ft_add_color(t_color3 col1, t_color3 col2, double intensity)
{
	intensity = ft_cap01(intensity);
	return (ft_vec3_cap01(
			ft_vec3_add(col1, ft_vec3_scal_prod(col2, intensity))));
}

/*
	Check if a ray is obstructed from light by any other object
*/
int	ft_is_obstructed(t_obj *obj_list, int obj_count,
	t_hit_point hpt, t_light light)
{
	t_ray			ray;
	t_obj			*obj;
	t_vec3			light_dir;
	double			hit_dist;
	int				i;

	light_dir = ft_vec3_minus(light.ori, hpt.pos);
	ray = ft_ray_create(hpt.pos, light_dir);
	i = 0;
	while (i < obj_count)
	{
		obj = obj_list + i;
		if (obj == hpt.object)
		{
			ray.ori = ft_vec3_add(ray.ori, ft_vec3_scal_prod(light_dir, .001));
		}
		hit_dist = ft_hit_object(*obj, ray) * ft_vec3_mod(ray.dir);
		if (hit_dist > 0 && hit_dist < ft_vec3_mod(light_dir))
			return (true);
		i++;
	}
	return (false);
}

t_color3	ft_bdrf(t_hit_point hpt, t_vec3 light_dir,
	t_color3 light_color)
{
	t_vec3	project_2;
	t_vec3	reflect_dir;
	double	intensity;

	project_2 = ft_vec3_scal_prod(
			hpt.normal,
			ft_vec3_dot(hpt.normal, hpt.inc_dir) * 2);
	reflect_dir = ft_vec3_minus(hpt.inc_dir, project_2);
	reflect_dir = ft_vec3_normalize(reflect_dir);
	light_dir = ft_vec3_normalize(light_dir);
	intensity = ft_cap01(ft_vec3_dot(reflect_dir, light_dir));
	intensity = pow(intensity, 5);
	return (ft_vec3_scal_prod(light_color, intensity * .2));
}
