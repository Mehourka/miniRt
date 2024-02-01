/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmehour <kmehour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 14:54:38 by valerie           #+#    #+#             */
/*   Updated: 2024/02/01 14:52:27 by kmehour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "../lib/libft/libft.h"

char	*get_next_line(int fd);
char	*ft_strchr_gnl(const char *str, int c);
char	*ft_strjoin_gnl(char *s1, char const *s2);
char	*find_line(char *stash);
char	*find_stash(char *stash);
char	*loop(int fd, char *stash, char *buffer);

#endif