#include "header.h"

t_vect3 *ft_vect3_create(double x, double y, double z)
{
	t_vect3 *new;

	new = malloc(sizeof(t_vect3));
	new->x = x;
	new->y = y;
	new->z = z;
	return (new);
}

t_vect3 *ft_vect3_add(t_vect3 *u, t_vect3 *v)
{
	t_vect3 *new;

	new = malloc(sizeof(t_vect3));
	new->x = u->x + v->x;
	new->y = u->y + v->y;
	new->z = u->z + v->z;
	return (new);
}

t_vect3 *ft_vect3_minus(t_vect3 *u, t_vect3 *v)
{
	t_vect3 *new;

	new = malloc(sizeof(t_vect3));
	new->x = u->x - v->x;
	new->y = u->y - v->y;
	new->z = u->z - v->z;
	return (new);
}

t_vect3 *ft_vect3_scal_prod(t_vect3 *u, double k)
{
	t_vect3 *new;

	new = malloc(sizeof(t_vect3));
	new->x = u->x * k;
	new->y = u->y * k;
	new->z = u->z * k;
	return (new);
}

double ft_vect3_mod(t_vect3 *u)
{
	return (sqrt((u->x * u->x) + (u->y * u->y) + (u->z * u->z)));
}

t_vect3 *ft_vect3_normalize(t_vect3 *u)
{
	double mod;

	mod = ft_vect3_mod(u);
	if (mod)
		return (ft_vect3_scal_prod(u, 1 / mod));
	return (u);
}

double ft_vect3_dot(t_vect3 *u, t_vect3 *v)
{
	double res;

	res = (u->x * v->x) + (u->y * v->y) + (u->z * v->z);
	return (res);
}

t_vect3 *ft_vect3_cross_prod(t_vect3 *u, t_vect3 *v)
{
	double i;
	double j;
	double k;

	i = u->y * v->z - u->z * v->y;
	j = u->z * v->x - u->x * v->z;
	k = u->x * v->y - u->y * v->x;
	return (ft_vect3_create(i, j, k));
}

double ft_vect3_get_angle(t_vect3 *u, t_vect3 *v)
{
	double num;
	double denom;

	num = ft_vect3_dot(u, v);
	denom = ft_vect3_mod(u) * ft_vect3_mod(v);
	if (denom == 0)
		return (0);
	return (acos(num/denom));
}

void ft_vect3_print(t_vect3 *u)
{
	printf("Vec (%.2f, %.2f, %.2f)\n", u->x, u->y, u->z);
}

