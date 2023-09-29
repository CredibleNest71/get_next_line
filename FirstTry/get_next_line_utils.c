/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:51:58 by codespace         #+#    #+#             */
/*   Updated: 2023/09/29 14:43:12 by codespace        ###   ########.fr       */
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
	if (old == NULL)
	{
		new = malloc(size + 1);
		return(new);
	}
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

int	redo_rest(char *rest, int fd)
{
	//char	temp[BUFFER_SIZE + 1] = {0};
	int		check;
	int		i;
	int		end;
	
	i = 0;
	while (rest[i] && rest[i] != '\n')
		i++;
	i++;
	if (rest[0] == 0 || i == BUFFER_SIZE - 1)
	{
		check = get_buf(fd, rest);
		return (check);
	}
	end = i;
	i = 0;
	while (rest[end] && end < BUFFER_SIZE)
		rest[i++] = rest[end++];
	while (i < BUFFER_SIZE)
		rest[i++] = 0;
	// while (i < BUFFER_SIZE)
	// {
	// 	rest[i] = temp[i];
	// 	i++;
	// }
	return (i);
}

char	*append_from_rest(char *dst, char *src, int *found)
{
	int	i;
	int	length;
    int end;

	end = 0;
	length = 0;
	while (dst[length])
		length++;
	i = 0;
	while (src[end] && src[end] != '\n')
		end++;
	dst = expand(dst, end + 1);
	while (i <= end)
	{
		dst[i + length] = src[i];
		if (src[i] == '\n')
			*found = 1;
		i++;
	}
	dst[i + length] = 0;
	return (dst);
}
