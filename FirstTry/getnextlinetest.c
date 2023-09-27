/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnextlinetest.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:26:53 by codespace         #+#    #+#             */
/*   Updated: 2023/09/27 14:07:05 by codespace        ###   ########.fr       */
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

int	redo_rest(char *oldrest, int idx, int fd)
{
	char	newrest[BUFFER_SIZE + 1];

	int	i;
	int	errors;

	i = 0;
	while (oldrest[idx + i])
	{
		newrest[i] == oldrest[idx + i];
		i++;
	}
	while (i < BUFFER_SIZE)
		newrest[i++] = 0;
	if (newrest[0] == 0)
	{
		errors = get_buf(fd, newrest);
	}
	return (errors);
}

int	append_from_rest(char *dst, char *src, int fd)
{
	int	i;
	int	length;
    int found;

    found = 0;
	length = len(dst);
	i = 0;
	while (src[i])
	{
		if (src[i] == '\n')
		{
			while (src[i] == '\n')
				i++;
            found = 1;
			break ;
		}
		dst[length + i] = src[i];
		i++;
	}
	redo_rest(src, i, fd);
	dst[length + i] = 0;
    return (found);
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

char	*get_next_line(int fd)
{
    char		*line;
    static char	rest[BUFFER_SIZE + 1] = {0};
    int         found;
	int			i;

	found = 0;
	i = 0;
	line = (char *) malloc(BUFFER_SIZE + 1);
	while (i < BUFFER_SIZE + 1)
		line[i++] = 0;
	while (!found)
    {
        line = expand(line, BUFFER_SIZE);
        found = append_from_rest(line, rest, fd);
    }
	line = expand(line, 2);
	append(line, "\n\0", 2);
	return (line);
}

int	main(void)
{
	char	*line;
	int		fd1;
	int		fd2;
	int		fd3;
	fd2 = open("tests/test.txt", O_RDONLY);
	fd1 = open("tests/test2.txt", O_RDONLY);
	fd3 = open("tests/test3.txt", O_RDONLY);
	line = get_next_line(fd1);
	printf("LINE%s", line);
	line = get_next_line(fd1);
	printf("LINE%s",line);	
	line = get_next_line(fd1);
	printf("LINE%s", line);
	line = get_next_line(fd1);
	printf("LINE%s", line);
	line = get_next_line(fd1);
	printf("LINE%s", line);
	free(line);
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}