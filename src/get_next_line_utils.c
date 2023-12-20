/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 11:03:40 by valerie           #+#    #+#             */
/*   Updated: 2023/12/15 15:09:18 by vst-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_gnl(char *s1, char const *s2)
{
	int		i;
	int		k;
	char	*new_string;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	k = 0;
	new_string = ft_calloc((ft_strlen(s1) + ft_strlen(s2)) + 1, sizeof(char));
	if (new_string == NULL)
		return (NULL);
	while (s1[i])
	{
		new_string[i] = s1[i];
		i++;
	}
	while (s2[k])
	{
		new_string[i + k] = s2[k];
		k++;
	}
	new_string[i + k] = '\0';
	free(s1);
	s1 = NULL;
	return (new_string);
}

char	*ft_strchr_gnl(const char *str, int c)
{
	char	*ptr;

	ptr = (char *)str;
	if (!str)
		return (NULL);
	while (*ptr != (char)c)
	{
		if (*ptr == '\0')
			return (NULL);
		ptr++;
	}
	return (ptr);
}
