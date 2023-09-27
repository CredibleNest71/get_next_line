/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:26:53 by codespace         #+#    #+#             */
/*   Updated: 2023/09/27 13:17:23 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

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

void	append(char *dst, char *src, int size)
{
	int	i;
	int	length;

	length = len(dst);
	i = 0;
	while (src[i] && i < size)
	{
		dst[length + i] = src[i];
		i++;
	}
	dst[length + i] = 0;
}

void	set_rest(char *rest, int bookmark)
{
	int		i;
	char	temp[BUFFER_SIZE + 1] = {0};
	
	i = 0;
	while(bookmark < BUFFER_SIZE)
	{
		temp[i++] = rest[bookmark++];
	}
	i = 0;
	while (i < BUFFER_SIZE)
	{
		rest[i] = temp[i];
		i++;
	}
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
    while (i < BUFFER_SIZE + 1)
    {
        rest[i] = buf[i];
        i++;
    }
	return (i);
}

int		check_buf(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (i);
		i++;
	}
    return (i);
}

char	*get_next_line(int fd)
{
    char		*line;
    static char	rest[BUFFER_SIZE + 1] = {0};
	int			bookmark;
    int         found;
	int			i;
	int endoffile = 0;

	found = 0;
	i = 0;
	line = (char *) malloc(BUFFER_SIZE + 1);
	while (i < BUFFER_SIZE + 1)
		line[i++] = 0;
	i = 0;
	while (rest[i])
	{
		line[i] = rest[i];
		if (rest[i] == '\n')
		{
			set_rest(rest, i + 1);
			return (line);
		}
		i++;
	}
	while (!found)
    {
		int bytes = get_buf(fd, rest);
		if (bytes <= 0)
		{
			free(line);
			return (NULL);
		}
		else if (bytes < BUFFER_SIZE)
			endoffile = 1;
		bookmark = check_buf(rest);
		if (bookmark < BUFFER_SIZE)
			found = 1;
		line = expand(line, bookmark + 1);
        append(line, rest, bookmark);
        set_rest(rest, bookmark + 1);
    }
	line = expand(line, 2);
	if (endoffile)
		append(line, "\0", 1);
	else
		append(line, "\n\0", 2);
	return (line);
}

// int	main(void)
// {
// 	char	*line;
// 	int		fd1;
// 	int		fd2;
// 	int		fd3;
// 	fd2 = open("tests/test.txt", O_RDONLY);
// 	fd1 = open("tests/test2.txt", O_RDONLY);
// 	fd3 = open("tests/test3.txt", O_RDONLY);
// 	line = get_next_line(fd1);
// 	printf("LINE%s", line);
// 	line = get_next_line(fd1);
// 	printf("LINE%s",line);	
// 	line = get_next_line(fd1);
// 	printf("LINE%s", line);
// 	line = get_next_line(fd1);
// 	printf("LINE%s", line);
// 	line = get_next_line(fd1);
// 	printf("LINE%s", line);
// 	free(line);
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// 	return (0);
// }