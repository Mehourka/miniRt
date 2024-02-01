/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 11:18:16 by kmehour           #+#    #+#             */
/*   Updated: 2023/05/08 11:18:19 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	@brief copy whole string with new memory allocation
*/
char	*ft_strdup(char const *s)
{
	size_t	tot_len;
	char	*new_str;

	tot_len = ft_strlen(s) + 1;
	new_str = malloc(tot_len);
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, s, tot_len);
	return (new_str);
}
