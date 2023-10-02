/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:51:58 by codespace         #+#    #+#             */
/*   Updated: 2023/10/02 16:46:35 by codespace        ###   ########.fr       */
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

	return (i);
}

char	*append_from_rest(char *src, int *found)
{
	char *dst;
	int	i;
    int end;

	end = 0;
	i = 0;
	while (src[end] && src[end] != '\n')
		end++;
	dst = malloc(end + 1);
	while (i <= end)
	{
		dst[i] = src[i];
		if (src[i] == '\n')
			*found = 1;
		i++;
	}
	dst[i] = 0;
	return (dst);
}

int	gelen(const char *s1, const char *s2)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s1[i])
		i++;
	len = i;
	i = 0;
	while (s2[i])
		i++;
	len += i;
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	int		i;
	int		j;
	char	*ans;

	j = 0;
	i = -1;
	len = gelen(s1, s2);
	ans = malloc(len + 1);
	if (!ans)
		return (0);
	while (s1[++i])
		ans[i] = s1[i];
	while (s2[j])
	{
		ans[i] = s2[j];
		i++;
		j++;
	}
	ans[i] = 0;
	return (ans);
}
