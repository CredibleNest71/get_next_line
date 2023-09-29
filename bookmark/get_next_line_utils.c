/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:51:58 by codespace         #+#    #+#             */
/*   Updated: 2023/09/29 12:40:08 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*expand(char *old, int size)
{
	int		i;
	int		newlength;
	char	*new;
	
	i = 0;
	while (old[i])
		i++;
	newlength = i + size + 1;
	i = 0;
	new = (char *) malloc(newlength);
	if (!new)
	{
		free(old);
		return (NULL);
	}
	while (old[i])
	{
		new[i] = old[i];
		i++;
	}
	while (i < newlength)
		new[i++] = 0;
	free(old);
	return(new);
}

int	get_buf(int fd, char *rest)
{
	int	bytesread;

	bytesread = read(fd, rest, BUFFER_SIZE);
	// while (rest[i])
	// 	i++;
	// while (i < BUFFER_SIZE)
	// 	rest[i++] = 0;
	return (bytesread);
}

int	look_for_end(char *str)
{
	int	i;
	
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

int	redo_rest(char *rest, int fd, int *bookmark)
{
	char	temp[BUFFER_SIZE + 1] = {0};
	int		check;
	int		i;
	int		end;
	
	i = 0;

	if (*bookmark == BUFFER_SIZE)
	{
		*bookmark = 0;
		check = get_buf(fd, rest);
		return (check);
	}
	
	return (i);
}

char	*append_from_rest(char *dst, char *src, int *found, int *bookmark)
{
	int	i;
	int	length;
	int	beginning;

	beginning = bookmark;
	length = 0;
	while (dst[length])
		length++;
	while (src[*bookmark] && src[*bookmark] != '\n' && bookmark < BUFFER_SIZE)
		*bookmark++;
	*bookmark++;
	dst = expand(dst, *bookmark + 1);
	while (beginning <= bookmark)
	{
		dst[length + i] = src[beginning];
		beginning++;
		i++;
	}
	return (dst);
}
