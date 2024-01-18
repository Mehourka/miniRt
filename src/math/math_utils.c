#include <math.h>

/*
	brief: caps a number betwwen [0, 1]
*/
double	ft_cap01(double f)
{
	return fmin(1, (fmax(0, f)));
}
