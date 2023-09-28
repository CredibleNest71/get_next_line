/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:51:58 by codespace         #+#    #+#             */
/*   Updated: 2023/09/28 13:16:51 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*expand(char *old, size_t size)
{
	size_t	i;
	size_t	newlength;
	char	*new;
	
	newlength = len(old) + size + 1;
	i = 0;
	new = (char *) malloc(newlength);
	while(i < newlength)
		new[i++] = 0;
	i = 0;
	while (old[i])
	{
		new[i] = old[i];
		i++;
	}
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
	while (str[i])
	{
		if (str[i] == '\n')
		{
			while (str[i] == '\n')
				i++;
			return (i);
		}
		i++;
	}
	return (i);
}

int	redo_rest(char *rest, int fd)
{
	int		check;
	int		end;
	int		i;
	
	end = look_for_end(rest);
	if (end == 0 || end >= BUFFER_SIZE - 1)
	{
		check = get_buf(fd, rest);
		if (check <= 0)
			return (-1);
		return (0);
	}
	i = 0;
	while (rest[end])
		rest[i++] = rest[end++];
	while (rest[i])
		rest[i++] = 0;
	return (0);
}

void	append_from_rest(char *dst, char *src, int fd, int *found)
{
	int	i;
	int	length;
    int end;

	length = len(dst);
	i = 0;
	end = look_for_end(src);
	if (end < BUFFER_SIZE - 2)
		*found = 1;
	expand(dst, end);
	while (i <= end && src[i])
	{
		if (src[i] == '\n')
		{
			*found = 1;
			dst[i + length] = src[i];
			return ;
		}
		dst[i + length] = src[i];
		i++;
	}
}
