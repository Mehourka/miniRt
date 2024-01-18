#include "vectors.h"
#include <math.h>
/*
	brief: converts and angle from Degrees to radians
*/
double	ft_deg_to_rad(double deg)
{
	return (deg * M_PI / 180);
}

/*
	brief: Rodrigues' rotation of vector v around the given axis

	param: v target vector
	param: axis rotation axis, has to be normalized
	param: theta rotation angle in radians
	returns: the rotated axis
*/
t_vec3	ft_rodrigues_rotation(t_vec3 v, t_vec3 axis, double theta)
{
	t_vec3	t1;
	t_vec3	t2;
	t_vec3	t3;

	// normalize axis
	axis = ft_vec3_normalize(axis);
	// comput the three terms
	t1 = ft_vec3_scal_prod(v, cos(theta));
	t2 = ft_vec3_scal_prod(axis,
			ft_vec3_dot(v, axis) * (1 - cos(theta)));
	t3 = ft_vec3_scal_prod(
			ft_vec3_cross_prod(axis, v), sin(theta));
	return (ft_vec3_add(
			ft_vec3_add(t1, t2), t3));
}
