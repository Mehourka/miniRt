#include <math.h>
#include "vectors.h"
#include "matrix.h"
#include "objects.h"
#include "minirt.h"

/*
	brief: Calcule de l'inverse d'une matrice par methode de l'adjoint
	Inv(A) = Transpose(Comatrice(A)) / Det(A)
*/

double	ft_det(t_mat3 A)
{
	double	det;

	det = A.mx[0][0] * A.mx[1][1] * A.mx[2][2]
		+ A.mx[0][1] * A.mx[1][2] * A.mx[2][0]
		+ A.mx[0][2] * A.mx[1][0] * A.mx[2][1]
		- A.mx[0][2] * A.mx[1][1] * A.mx[2][0]
		- A.mx[0][0] * A.mx[1][2] * A.mx[2][1]
		- A.mx[0][1] * A.mx[1][0] * A.mx[2][2];
	return (det);
}

t_mat3	ft_mat3_inverse(t_mat3 A)
{
	t_mat3	inv;
	double	det;
	int		i;
	int		j;

	i = 0;
	j = 0;
	det = ft_det(A);
	if (det == 0)
		return (A);
	inv.mx[0][0] = (A.mx[1][1] * A.mx[2][2] - A.mx[1][2] * A.mx[2][1]) / det;
	inv.mx[0][1] = (A.mx[0][2] * A.mx[2][1] - A.mx[0][1] * A.mx[2][2]) / det;
	inv.mx[0][2] = (A.mx[0][1] * A.mx[1][2] - A.mx[0][2] * A.mx[1][1]) / det;
	inv.mx[1][0] = (A.mx[1][2] * A.mx[2][0] - A.mx[1][0] * A.mx[2][2]) / det;
	inv.mx[1][1] = (A.mx[0][0] * A.mx[2][2] - A.mx[0][2] * A.mx[2][0]) / det;
	inv.mx[1][2] = (A.mx[0][2] * A.mx[1][0] - A.mx[0][0] * A.mx[1][2]) / det;
	inv.mx[2][0] = (A.mx[1][0] * A.mx[2][1] - A.mx[1][1] * A.mx[2][0]) / det;
	inv.mx[2][1] = (A.mx[0][1] * A.mx[2][0] - A.mx[0][0] * A.mx[2][1]) / det;
	inv.mx[2][2] = (A.mx[0][0] * A.mx[1][1] - A.mx[0][1] * A.mx[1][0]) / det;
	return (inv);
}
