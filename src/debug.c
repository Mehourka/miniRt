#include "minirt.h"

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
	ft_print_object(hp.object);
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
	if (mlx_is_mouse_down(mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		// Get mouse position
		mlx_get_mouse_pos(mlx, mousePos, mousePos + 1);

		// Create ray pointing at mouse
		ray = ft_compute_ray(data->cam, mousePos[1], mousePos[0]);

		// Compute the hit point in that pixel
		t_hit_point hit_pt = ft_get_closest_hitpoint(data->obj, data->object_count, ray);
		// ft_print_hitpt(hit_pt);

		if (OBJ_CYLINDER == hit_pt.object.obj_type && hit_pt.f_valid)
		{
			t_cylinder cy = hit_pt.object.cylinder;
			// ft_print_vec3( hit_pt.pos);
			t_pt3 lspace_pos = ft_mat3_multiplication(cy.inverse_transfrom, hit_pt.pos);
			t_pt3 wspace_pos = ft_mat3_multiplication(cy.transform_matrix, lspace_pos);

			// Reference direction
			printf("Local space dir : ");
			ft_print_vec3(ft_mat3_multiplication(cy.inverse_transfrom, cy.dir));
			printf("Word space dir : ");
			ft_print_vec3(cy.dir);
			printf("\n");

			t_vec3 lspace_normal = ft_get_obj_normal(hit_pt.object, wspace_pos);


		}
		printf("\n\n");
	}
}
