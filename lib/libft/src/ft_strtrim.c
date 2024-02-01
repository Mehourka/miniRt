/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:05:09 by kmehour           #+#    #+#             */
/*   Updated: 2023/02/05 19:49:23 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>


/*
	@brief trims a set of characters from both ends of astring

	@param s1 string to be trimmed
	@param set the set of characters to remove

	@warning creates a copy, does not free the original
	@return A copy of the trimmed part of the string
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*dest;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	dest = (char *)malloc(end - start + 1);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, (s1 + start), (end - start + 1));
	return (dest);
}
