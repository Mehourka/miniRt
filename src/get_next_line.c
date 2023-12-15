/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vst-pier <vst-pier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 11:03:38 by valerie           #+#    #+#             */
/*   Updated: 2023/12/15 15:08:34 by vst-pier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_and_null(char *ptr)
{
	free(ptr);
	ptr = NULL;
	return (NULL);
}

char	*find_line(char *stash)
{
	int		len;
	char	*line;

	len = 0;
	if (!stash || stash[0] == '\0')
		return (NULL);
	while (stash[len] && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	line = ft_calloc(len + 1, sizeof(char));
	if (!line)
		return (NULL);
	len = 0;
	while (stash[len] != '\n' && stash[len])
	{
		line[len] = stash[len];
		len++;
	}
	if (stash[len] && stash[len] == '\n')
		line[len] = '\n';
	return (line);
}

char	*find_stash(char *stash)
{
	int		len;
	char	*new_stash;
	int		new_stash_len;
	int		len2;

	len = 0;
	if (!stash)
		return (NULL);
	while (stash[len] && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	new_stash_len = ft_strlen(stash) - len;
	new_stash = ft_calloc(new_stash_len + 1, sizeof(char));
	if (!new_stash)
		return (free_and_null(stash));
	len2 = 0;
	while (stash[len + len2])
	{
		new_stash[len2] = stash[len + len2];
		len2++;
	}
	free_and_null(stash);
	return (new_stash);
}

char	*loop(int fd, char *stash, char *buffer)
{
	int	char_readed;

	char_readed = 1;
	while (char_readed != 0)
	{
		ft_bzero(buffer, BUFFER_SIZE + 1);
		char_readed = read(fd, buffer, BUFFER_SIZE);
		if (char_readed == -1)
		{
			if (stash)
				free_and_null(stash);
			return (free_and_null(buffer));
		}
		stash = ft_strjoin_gnl(stash, buffer);
		if (ft_strchr_gnl(stash, '\n') != NULL)
			char_readed = 0;
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (stash = free_and_null(stash), NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	if (!stash)
		stash = ft_calloc(1, sizeof(char));
	if (!stash)
		return (free_and_null(buffer));
	stash = loop(fd, stash, buffer);
	free_and_null(buffer);
	if (stash == NULL)
		return (NULL);
	line = find_line(stash);
	if (!line)
		return (stash = free_and_null(stash), NULL);
	stash = find_stash(stash);
	if (stash == NULL)
		free_and_null(line);
	return (line);
}
