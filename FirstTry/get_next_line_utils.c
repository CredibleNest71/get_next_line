/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:51:58 by codespace         #+#    #+#             */
/*   Updated: 2023/09/28 16:44:34 by codespace        ###   ########.fr       */
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
	i = -1;
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
	char	buf[BUFFER_SIZE];
	int		bytesread;
    int     i;

    i = 0;
	bytesread = read(fd, buf, BUFFER_SIZE);
	if (bytesread <= 0)
		return (bytesread);
    while (i < BUFFER_SIZE)
    {
        rest[i] = buf[i];
        i++;
    }
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
	char	temp[BUFFER_SIZE + 1] = {0};
	int		check;
	int		i;
	int		end;
	
	i = 0;
	while (rest[i] && rest[i] != '\n')
		i++;
	if (rest[0] == 0 || i == BUFFER_SIZE - 1)
	{
		check = get_buf(fd, rest);
		return (check);
	}
	end = i;
	i = 0;
	while (rest[end] && end < BUFFER_SIZE)
		temp[i++] = rest[end++];
	i = 0;
	while (i < BUFFER_SIZE)
	{
		rest[i] = temp[i];
		i++;
	}
	return (i);
}

void	append_from_rest(char *dst, char *src, int fd, int *found)
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
	expand(dst, end + 1);
	while (i <= end)
	{
		dst[i + length] = src[i];
		if (src[i] == '\n')
			*found = 1;
		i++;
	}
	dst[i] = 0;
}
