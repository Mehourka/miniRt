/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:49:44 by kmehour           #+#    #+#             */
/*   Updated: 2024/02/01 13:50:46 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <MLX42/MLX42.h>
# include "libft.h"
# include "get_next_line.h"
# include "vectors.h"
# include "hooks.h"
# include "render.h"
# include "objects.h"
# include "matrix.h"

typedef struct s_selected
{
	int		type;
	t_obj	*obj;
	t_light	*light;
}	t_selected;

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_obj		obj[100];
	t_cam		cam;
	t_light		light[5];
	t_ambiant	ambiant;
	t_selected	selec;
	double		aspect_ratio;
	int			object_count;
	int			height;
	int			width;
	int			l;
}	t_data;

t_data		*get_data(void);
void		compute_viewport(t_data *data);
void		ft_render_image(t_data *data);
void		ft_raise_error(t_data *data);
t_color3	ft_get_shade(t_data *data, t_hit_point hpt);

#endif