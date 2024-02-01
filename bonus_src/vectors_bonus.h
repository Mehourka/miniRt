/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:49:48 by kmehour           #+#    #+#             */
/*   Updated: 2024/02/01 13:49:49 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

typedef union s_vec3
{
	struct
	{
		double	x;
		double	y;
		double	z;
	};
	double	cord[3];
}	t_vec3;

typedef t_vec3	t_pt3;

typedef t_vec3	t_color3;
typedef struct s_ray
{
	t_pt3	ori;
	t_vec3	dir;
}	t_ray;

// Basic vector math
t_vec3	ft_vec3_create(double x, double y, double z);
t_vec3	ft_vec3_add(t_vec3 u, t_vec3 v);
t_vec3	ft_vec3_minus(t_vec3 u, t_vec3 v);
t_vec3	ft_vec3_elem_mult(t_vec3 u, t_vec3 v);
t_vec3	ft_vec3_add_scal(t_vec3 u, double k);
t_vec3	ft_vec3_scal_prod(t_vec3 u, double k);
t_vec3	ft_vec3_cross_prod(t_vec3 u, t_vec3 v);
t_vec3	ft_vec3_normalize(t_vec3 u);
t_vec3	ft_vec3_cap01(t_vec3 u);
double	ft_vec3_mod(t_vec3 u);
double	ft_vec3_dot(t_vec3 u, t_vec3 v);
double	ft_vec3_get_angle(t_vec3 u, t_vec3 v);
double	ft_cap01(double f);
t_vec3	ft_vec3_cap01(t_vec3 u);

// Rays
t_ray	ft_ray_create(t_pt3 origine, t_vec3 direction);
t_pt3	ft_ray_project(t_ray ray, double t);

// Vector rotation
t_vec3	ft_rodrigues_rotation(t_vec3 v, t_vec3 axis, double theta);
double	ft_deg_to_rad(double deg);

#endif