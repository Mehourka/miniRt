#include "minirt.h"

// Ascii to double

static int	decimal(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] && str[i] != '.')
		i++;
	if (str[i] == '.')
		i++;
	while (str[i + count] && str[i + count] != '.')
		count++;
	return (count);
}

double	ft_atod(char *str)
{
	int		i;
	double	nb;
	int		multiple;

	i = 0;
	nb = 0;
	multiple = 1;
	if (!str)
		return (0);
	if (str[i] == '-')
	{
		i++;
		multiple = -1;
	}
	while (((str[i] >= '0' && str[i] <= '9') || str[i] == '.') && str[i] != ',')
	{
		if (str[i] != '.')
			nb = nb * 10 + str[i] - 48;
		i++;
	}
	if (decimal(str) != 0)
		nb = nb / pow(10, decimal(str));
	return (multiple * nb);
}