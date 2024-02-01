/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:48:36 by kmehour           #+#    #+#             */
/*   Updated: 2024/02/01 13:48:37 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vectors.h"
#include "matrix.h"
#include "objects.h"
#include "minirt.h"

/*
	Creates a 3x3 Matrix from 3 column vectors a, b and c;
	example :

	a [1, 2 ,3] | b[4, 5, 6] | c[7, 8, 9]

	M => [a | b | c]

		[1, 4, 7]
	M =	[2, 5, 8]
		[3, 6, 9]

	to access an element, we use
	===> M.mx[row][column]
*/
t_mat3	ft_mat3_from_vec3(t_vec3 a, t_vec3 b, t_vec3 c)
{
	t_mat3	mx;

	mx.mx[0][0] = a.cord[0];
	mx.mx[1][0] = a.cord[1];
	mx.mx[2][0] = a.cord[2];
	mx.mx[0][1] = b.cord[0];
	mx.mx[1][1] = b.cord[1];
	mx.mx[2][1] = b.cord[2];
	mx.mx[0][2] = c.cord[0];
	mx.mx[1][2] = c.cord[1];
	mx.mx[2][2] = c.cord[2];
	return (mx);
}

t_mat3	ft_mat3_identity(void)
{
	const t_vec3	a = {{1, 0, 0}};
	const t_vec3	b = {{0, 1, 0}};
	const t_vec3	c = {{0, 0, 1}};

	return (ft_mat3_from_vec3(a, b, c));
}

t_vec3	ft_mat3_multiplication(t_mat3 A, t_vec3 u)
{
	t_vec3	new;

	new.x = A.mx[0][0] * u.x + A.mx[0][1] * u.y + A.mx[0][2] * u.z;
	new.y = A.mx[1][0] * u.x + A.mx[1][1] * u.y + A.mx[1][2] * u.z;
	new.z = A.mx[2][0] * u.x + A.mx[2][1] * u.y + A.mx[2][2] * u.z;
	return (new);
}

t_ray	ft_ray_transform(t_ray ray, t_mat3 A, t_pt3 new_ori)
{
	return (
		ft_ray_create(
			ft_mat3_multiplication(A, ft_vec3_minus(ray.ori, new_ori)),
			// ray.ori,
			ft_mat3_multiplication(A, ray.dir)));
}

t_mat3	ft_ortho_normal_mat3(t_vec3 v)
{
	t_vec3	u;
	t_vec3	w;

	v = ft_vec3_normalize(v);
	if (fabs(v.x) < fabs(v.y))
		u = ft_vec3_cross_prod((t_vec3){{1, 0, 0}}, v);
	else
		u = ft_vec3_cross_prod((t_vec3){{0, 1, 0}}, v);
	w = ft_vec3_cross_prod(u, v);
	return (ft_mat3_from_vec3(u, v, w));
}
