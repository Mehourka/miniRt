
#include "minirt.h"
#include "render.h"

t_data *get_data()
{
	static t_data *data;

	if (data == NULL)
	{
		data = malloc(sizeof(t_data));
		data->aspect_ratio = (float) WIDTH / HEIGHT;
	}
	return (data);
}

void ft_raise_error(t_data *data)
{
	// TODO: Should free data here
	if (data->mlx)
		mlx_close_window(data->mlx);
	ft_putstr_fd((char *)mlx_strerror(mlx_errno), STDERR_FILENO);
	exit(EXIT_FAILURE);
}



void create_objects(void)
{
	t_data *data = get_data();
	t_obj *sphere = &data->obj;;
	t_cam *cam = &data->cam;

	sphere->obj_type = OBJ_SPHERE;
	sphere->center = ft_vec3_create(3, 0, 0);
	sphere->r = 1;

	cam->center = ft_vec3_create(0, 0, 0);
	cam->direction = ft_vec3_create(1, 0, 0);
	cam->angle = 70;
}

typedef struct s_viewport
{
	t_vec3	upper_left_corner;
	t_vec3	u;
	t_vec3	v;
	t_vec3	du;
	t_vec3	dv;
	t_vec3	focal_length;
}	t_viewport;

bool hit_sphere(t_obj sphere, t_ray ray)
{
	t_vec3 oc = ft_vec3_minus(ray.orig, sphere.center);

	double a = ft_vec3_dot(ray.dir, ray.dir);
	double b = ft_vec3_dot(
		ft_vec3_scal_prod(ray.dir, 2.0),
		oc);
	double c =	ft_vec3_dot(oc, oc) - pow(sphere.r, 2);

	double discriminant = b*b - 4*a*c;
	return (discriminant >= 0);
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

	if (hit_sphere(data->obj, ray))
		return norm_rgba(1, 1, 1, 1);

	return (norm_rgba(col.x, col.y, col.z, 1));
}



void compute_viewport()
{
	t_data *data = get_data();
	t_viewport vp;
	double viewport_h = 3;

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
	vp.upper_left_corner.x = data->cam.center.x + data->cam.direction.x - vp.u.x / 2 - vp.v.x / 2;
	vp.upper_left_corner.y = data->cam.center.y + data->cam.direction.y - vp.u.y / 2 - vp.v.y / 2;
	vp.upper_left_corner.z = data->cam.center.z + data->cam.direction.z - vp.u.z / 2 - vp.v.z / 2;

	// trouver le Pixel00
	t_vec3 pixel00 = ft_vec3_add(
		ft_vec3_scal_prod(ft_vec3_add(vp.du, vp.dv), 0.5),
		vp.upper_left_corner);
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
				data->cam.center);
			t_ray ray = ft_ray_create(data->cam.center, ray_dir);

			// Render le pixel (i, j)
			int color = ray_color(ray);
			mlx_put_pixel(data->img, i, j, color);
		}
	}
	// compute rays
}

void ft_hook(void *param)
{

	mlx_t *mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);

	// change sphere radius
	double EPS = 0.05;
	double *r = &get_data()->obj.r;
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		*r += EPS;
		if (*r > 2.5)
			*r = 2.5;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		*r -= EPS;
		if (*r < 0.1)
			*r = 0.1;
	}

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);

	compute_viewport();
}

/*int main(void)
{
	const int image_width = WIDTH;
	const int image_height = HEIGHT;

	// Setup mlx data
	t_data *data = get_data();
	create_objects();

	if (!(data->mlx = mlx_init(WIDTH, HEIGHT, "miniRt", true)))
		ft_raise_error(data);
	if (!(data->img = mlx_new_image(data->mlx, image_width, image_height)))
		ft_raise_error(data);

	// // // Draw on image
	ft_memset(data->img->pixels, 255, sizeof(int32_t) * image_height * image_width);
	// draw_gradient(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);


	// // Hooks
	mlx_loop_hook(data->mlx, &ft_hook, data->mlx);

	// // mlx loop
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);

	// printf("Sphere : %p\n", data->obj->center);


	return (EXIT_SUCCESS);
}*/