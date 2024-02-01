/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:17:49 by kmehour           #+#    #+#             */
/*   Updated: 2023/05/08 11:22:27 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	@brief Search of char c in a char pointer

	@param s The string to search
	@param c target character
	@return the address of first find, NULL otherwise
*/
char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	if (!(char)c)
		return ((char *)&s[i]);
	return (NULL);
}
