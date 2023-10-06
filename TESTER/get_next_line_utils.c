/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:51:58 by codespace         #+#    #+#             */
/*   Updated: 2023/10/06 11:40:25 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	get_buf(int fd, char *rest)
{
	int	bytesread;

	bytesread = read(fd, rest, BUFFER_SIZE);
	return (bytesread);
}

int	redo_rest(char *rest, int fd)
{
	int		check;
	int		i;
	int		end;

	i = 0;
	while (rest[i] && rest[i] != '\n')
		i++;
	if (rest[i] == '\n')
		i++;
	if (rest[0] == 0 || i == BUFFER_SIZE)
	{
		check = get_buf(fd, rest);
		end = check;
		while (end < BUFFER_SIZE)
			rest[end++] = 0;
		return (check);
	}
	end = i;
	i = 0;
	while (rest[end] && end < BUFFER_SIZE)
		rest[i++] = rest[end++];
	while (i < BUFFER_SIZE)
		rest[i++] = 0;
	return (i);
}

char	*get_from_rest(char *src, int *found)
{
	char	*dst;
	int		i;
	int		end;

	end = 0;
	i = 0;
	dst = NULL;
	while (src[end] && src[end] != '\n')
		end++;
	if (src[end] == '\n')
		end++;
	if (end)
		dst = zalloc(end + 1);
	if (!dst)
		return (NULL);
	while (i < end)
	{
		dst[i] = src[i];
		if (src[i] == '\n')
			*found = 1;
		i++;
	}
	dst[i] = 0;
	return (dst);
}

int	gelen(char *s1, char *s2)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (s1)
	{
		while (s1[i])
			i++;
		len += i;
	}
	i = 0;
	if (s2)
	{
		while (s2[i])
			i++;
		len += i;
	}
	return (len);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		len;
	int		i;
	int		j;
	char	*ans;

	j = 0;
	i = -1;
	if (!s2)
		return (s1);
	if (!s1)
		return (s2);
	len = gelen(s1, s2);
	ans = zalloc(len + 1);
	if (!ans)
		return (NULL);
	while (s1[++i])
		ans[i] = s1[i];
	while (s2[j])
		ans[i++] = s2[j++];
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (ans);
}
