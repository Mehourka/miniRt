
#include "minirt.h"
#include "render.h"

int *ft_sphere_intersec(t_pt3 sp_center, t_pt3 cam_origin, t_vec3 ray_dir, double rayon)
{
	// b.bt2     +      2b.(A - C)t      +     (A-c)(A-C) - r2 = 0
	double a;
	double b;
	double c;

}


int* ft_sphere_quad (double a, double b, double c)
{
	int t[2];
	double denom;
	double square;
	
	denom = 2 * a;
	if(denom == 0)
		return(NULL);
	square = (b * b) - (4.0 * a * c);
	if (square < 0)
		return(NULL);
	square = sqrt(square);
	t[0] = -b - square;
	t[1] = -b + square;
	return(t);
}