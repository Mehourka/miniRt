#ifndef HEADER_H
# define HEADER_H

# include "libft.h"
# include "math.h"
# include "stdio.h"

typedef struct s_vect3 {
	double	x;
	double	y;
	double	z;
}	t_vect3;

t_vect3 *ft_vect3_create(double x, double y, double z);
t_vect3 *ft_vect3_add(t_vect3 *u, t_vect3 *v);
t_vect3 *ft_vect3_minus(t_vect3 *u, t_vect3 *v);
t_vect3 *ft_vect3_scal_prod(t_vect3 *u, double k);
double ft_vect3_mod(t_vect3 *u);
t_vect3 *ft_vect3_normalize(t_vect3 *u);
void ft_vect3_print(t_vect3 *u);
double ft_vect3_dot(t_vect3 *u, t_vect3 *v);
t_vect3 *ft_vect3_cross_prod(t_vect3 *u, t_vect3 *v);
double ft_vect3_get_angle(t_vect3 *u, t_vect3 *v);

#endif