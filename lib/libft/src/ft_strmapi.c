/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 19:25:15 by kmehour           #+#    #+#             */
/*   Updated: 2023/02/06 19:49:00 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	size;
	size_t	i;

	i = 0;
	size = ft_strlen(s);
	str = (char *)malloc(size + 1);
	if (!s || !str)
		return (NULL);
	str[size] = '\0';
	while (i < size)
	{
		str[i] = (*f)(i, s[i]);
		i++;
	}
	return (str);
}
