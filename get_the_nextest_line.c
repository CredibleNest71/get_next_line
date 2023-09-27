/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_the_nextest_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:26:53 by codespace         #+#    #+#             */
/*   Updated: 2023/09/27 10:26:26 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

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

void	set_rest(char *rest, char *buf, int bookmark)
{
	int	i;

	i = 0;
	while (i < BUFFER_SIZE)
		rest[i++] = 0;
	i = 0;
	while (buf[bookmark])
		rest[i++] = buf[bookmark++];
	rest[i] = 0;
}

char	*get_buf(int fd)
{
	char	*buf;
	int		bytesread;
	
	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf)
		return(NULL);
	bytesread = read(fd, buf, BUFFER_SIZE);
	if (bytesread <= 0)
		return (NULL);
	buf[BUFFER_SIZE] = 0;
	return (buf);
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
	return (-1);
}

char	*get_next_line(int fd)
{
    char		*line;
    static char	rest[BUFFER_SIZE] = {0};
	char		*buf;
	int			bookmark;

	line = (char *) malloc(BUFFER_SIZE);
	set_rest(line, rest, BUFFER_SIZE);
	append(line, rest, BUFFER_SIZE);
	while (1)
	{
		buf = get_buf(fd);
		if (!buf)
			return (NULL);
		bookmark = check_buf(buf);
		if (bookmark > 0)
			break;
		line = expand(line, BUFFER_SIZE);
		append(line, buf, BUFFER_SIZE);
		free(buf);
	}
	line = expand(line, bookmark + 1);
	append(line, buf, bookmark);
	append(line, "\n", 1);
	set_rest(rest, buf, bookmark + 1);
	free(buf);
	return (line);
}

int	main(void)
{
	char	*line;
	int		fd1;
	int		fd2;
	int		fd3;
	fd1 = open("tests/test.txt", O_RDONLY);
	fd2 = open("tests/test2.txt", O_RDONLY);
	fd3 = open("tests/test3.txt", O_RDONLY);
	line = get_next_line(fd1);
	printf("LINE%s", line);
	line = get_next_line(fd1);
	printf("LINE%s",line);	
	line = get_next_line(fd1);
	printf("LINE%s", line);
	// line = get_next_line(fd1);
	// printf("LINE%s", line);
	// line = get_next_line(fd1);
	// printf("LINE%s", line);
	free(line);
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}