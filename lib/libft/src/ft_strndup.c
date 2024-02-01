/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:18:42 by kmehour           #+#    #+#             */
/*   Updated: 2023/05/08 11:20:27 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	@brief  duplicates the firt n characters of a string
 */
char	*ft_strndup(char const *s, size_t n)
{
	size_t	tot_len;
	char	*new_str;

	tot_len = ft_min(ft_strlen(s), n) + 1;
	new_str = malloc(tot_len);
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, s, tot_len);
	return (new_str);
}
