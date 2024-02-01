/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:49:43 by kmehour           #+#    #+#             */
/*   Updated: 2024/02/01 14:52:47 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_BONUS_H
# define MATRIX_BONUS_H

# include "vectors.h"

typedef union u_mat3
{
	struct
	{
		t_vec3	i;
		t_vec3	j;
		t_vec3	k;
	};
	double	mx[3][3];
}	t_mat3;

t_mat3	ft_mat3_from_vec3(t_vec3 a, t_vec3 b, t_vec3 c);
t_mat3	ft_mat3_identity(void);
t_vec3	ft_mat3_multiplication(t_mat3 A, t_vec3 u);
t_ray	ft_ray_transform(t_ray ray, t_mat3 A, t_pt3 new_ori);

t_mat3	ft_mat3_inverse(t_mat3 A);
t_mat3	ft_ortho_normal_mat3(t_vec3 v);

#endif