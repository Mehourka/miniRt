#include "minirt.h"

void manual_create_objects(void)
{
	t_data *data = get_data();

	t_cam *cam = &data->cam;

	data->obj[0].obj_type = OBJ_SPHERE;
	data->obj[0].ori = ft_vec3_create(0, 0, 0);
	data->obj[0].sphere.r = 1;
	data->obj[0].color = ft_vec3_create(.6, .1, .1);

	// data->obj[1].obj_type = OBJ_SPHERE;
	// data->obj[1].ori = ft_vec3_create(0, 0, -5);
	// data->obj[1].sphere.r = 1;
	// data->obj[1].color = ft_vec3_create(.1, .6, .1);

	// data->obj[2].obj_type = OBJ_SPHERE;
	// data->obj[2].ori = ft_vec3_create(-2, 0, -5);
	// data->obj[2].sphere.r = 0.9;
	// data->obj[2].color = ft_vec3_create(0.1, .1, .6);

	// data->obj[3].obj_type = OBJ_SPHERE;
	// data->obj[3].ori = ft_vec3_create(0, -150, 0);
	// data->obj[3].sphere.r = 145;
	// data->obj[3].color = ft_vec3_create(0.15, .15, .15);

	cam->ori = ft_vec3_create(0, 0, -5);
	cam->dir = ft_vec3_create(0, 0, 1);
	cam->vup = ft_vec3_create(0, 1, 0);
	cam->angle = 70;

	data->light.ori = ft_vec3_create(3, 0, 0);
}

void ft_print_object(t_obj obj)
{
	printf("Object : ");
	if (OBJ_SPHERE == obj.obj_type)
	{
		printf("Sphere\n");
	}
	if (OBJ_PLANE == obj.obj_type)
	{
		printf("Plane\n");
	}
	if (OBJ_CYLINDER == obj.obj_type)
	{
		printf("Cylinder\n");
	}
}

void ft_print_hitpt(t_hit_point hp)
{
	if (hp.f_valid == false)
	{
		printf("No hit\n");
		return;
	}
	ft_print_object(*hp.object);
}

void ft_print_ray(t_ray ray)
{
	printf("Ray: \n");
	printf("ori : ");
	ft_print_vec3(ray.ori);
	printf("dir : ");
	ft_print_vec3(ray.dir);
	printf("\n");
}

void ft_print_vec3(t_vec3 u)
{
	printf("Vec (%.4f, %.4f, %.4f)\n", u.x, u.y, u.z);
}

void ft_print_mat3(t_mat3 mx)
{
	printf("Matrix: \n");
	printf("[%.2f, %.2f, %.2f]\n", mx.mx[0][0], mx.mx[0][1], mx.mx[0][2]);
	printf("[%.2f, %.2f, %.2f]\n", mx.mx[1][0], mx.mx[1][1], mx.mx[1][2]);
	printf("[%.2f, %.2f, %.2f]\n", mx.mx[2][0], mx.mx[2][1], mx.mx[2][2]);
	printf("\n");
}

void ft_mouse_select(void *param)
{
	t_data *data;
	mlx_t *mlx;
	t_ray ray;
	int32_t mousePos[2];

	data = (t_data *)param;
	mlx = data->mlx;

		// change sphere radius
	t_ambiant *amb = &data->ambiant;
	if (mlx_is_key_down(mlx, MLX_KEY_PAGE_UP))
	{
		 amb->ratio = ft_cap01(amb->ratio + 0.01);
		 printf("%f\n",amb->ratio);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_PAGE_DOWN))
	{
		 amb->ratio = ft_cap01(amb->ratio - 0.01);
		 printf("%f\n",amb->ratio);
	}


	if (mlx_is_mouse_down(mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		// Get mouse position
		mlx_get_mouse_pos(mlx, mousePos, mousePos + 1);

		// Create ray pointing at mouse
		ray = ft_compute_ray(data->cam, mousePos[1], mousePos[0]);

		// Compute the hit point in that pixel
		t_hit_point hit_pt = ft_get_closest_hitpoint(data->obj, data->object_count, ray);
		// ft_print_hitpt(hit_pt);

		// Wordspace / local space
		// if (false && OBJ_CYLINDER == hit_pt.object->obj_type && hit_pt.f_valid)
		// {
			// t_cylinder cy = hit_pt.object->cylinder;
			// ft_print_vec3( hit_pt.pos);
			// t_pt3 lspace_pos = ft_mat3_multiplication(cy.inverse_transfrom, hit_pt.pos);
			// t_pt3 wspace_pos = ft_mat3_multiplication(cy.transform_matrix, lspace_pos);

			// Reference direction
			// printf("Local space dir : ");
			// ft_print_vec3(ft_mat3_multiplication(cy.inverse_transfrom, cy.dir));
			// printf("Word space dir : ");
			// ft_print_vec3(cy.dir);
			// printf("\n");

			// t_vec3 lspace_normal = ft_get_obj_normal(*hit_pt.object, wspace_pos);
		// }


		// Color
		if (true && hit_pt.f_valid)
		{
			t_light light = data->light;
			t_vec3 light_dir = ft_vec3_minus(light.ori, hit_pt.pos);
			ray = ft_ray_create(hit_pt.pos, light_dir);
				for (int i = 0; i < data->object_count; i++)
				{
					t_obj *obj = data->obj + i;
					if (obj == hit_pt.object)
					continue;
					if (ft_hit_object(*obj, ray) > 0)
					{
						printf("Obstruction by object[%i]\n",i);
						printf("intersect_distance : %f\n", ft_hit_object(data->obj[i], ray));
					}

				}
			ft_print_ray(ray);
			// ft_print_vec3(light_dir);
		}

		printf("\n\n");
	}
}
