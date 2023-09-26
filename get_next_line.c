/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:32:08 by codespace         #+#    #+#             */
/*   Updated: 2023/09/26 16:00:05 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Function name		get_next_line
// Prototype 			char *get_next_line(int fd);
// Turn in files 		get_next_line.c, get_next_line_utils.c,
// 						get_next_line.h
// Parameters fd: 		The file descriptor to read from
// Return value 		Read line: correct behavior
// 						NULL: there is nothing else to read, or an error
// 						occurred
// External functs. 	read, malloc, free
// Description 			Write a function that returns a line read from a
// 						file descriptor
#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

char	*get_buf(int fd, int *bookmark)
{
	char	buf[BUFFER_SIZE];
	int		bytes;
	int		i;

	i = 0;
	bytes = read(fd, buf, BUFFER_SIZE);
	if (bytes <= 0)
		return (NULL);
	while (i++ < BUFFER_SIZE)
	{
		if (buf[i] == '\n')
		{
			*bookmark = i;
			return (buf);
		}
	}
	bookmark = BUFFER_SIZE;
	return (buf);
}

int	ft_strlen(const char *str)
{
	int	length;

	length = 0;
	while (*str)
	{
		length++;
		str++;
	}
	return (length);
}

void	append(char *dst, char *src, size_t n)
{
	size_t i;

	if (!dst && !src)
		return (0);
	i = 0;
	while (dst[i])
		i++;
	dst = &dest[i];
	i = 0;
	while (i < n && src[i])
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return ;
}

void	copy_from_bookmark(char *rest, char *buf, int bookmark)
{
	int	i;

	i = 0;
	while (bookmark < BUFFER_SIZE)
	{
		rest[i++] = buf[bookmark++];
	}
	rest[i] = 0;
}

char	*get_next_line(int fd)
{
	char			*line;
	char			*buf;
	int				bookmark;
	static char		rest[BUFFER_SIZE];
	int				i;

	bookmark = BUFFER_SIZE;
	line = (char *) malloc(BUFFER_SIZE* 10);
	if (!line || !rest)
		return (0);
	append(line, rest, ft_strlen(rest));
	while (bookmark == BUFFER_SIZE)
	{
		buf = get_buf(fd, &bookmark);
		append(line, buf, bookmark);
	}
	append(line, buf, bookmark);
	copy_from_bookmark(rest, buf, bookmark);
	return (line);
}



// int	main(void)
// {
// 	char	*line;
// 	int		i;
// 	int		fd1;
// 	int		fd2;
// 	int		fd3;
// 	fd1 = open("tests/test.txt", O_RDONLY);
// 	fd2 = open("tests/test2.txt", O_RDONLY);
// 	fd3 = open("tests/test3.txt", O_RDONLY);
// 	i = 1;
// 	line = get_next_line(fd1);
// 	printf("%s", line);
// 	line = get_next_line(fd1);
// 	printf("%s", line);	
// 	line = get_next_line(fd1);
// 	printf("%s", line);	
// 	line = get_next_line(fd1);
// 	printf("%s", line);	
// 	line = get_next_line(fd1);
// 	printf("%s", line);
// 	free(line);
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// 	return (0);
// }