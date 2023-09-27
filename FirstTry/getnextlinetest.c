/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getnextlinetest.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:26:53 by codespace         #+#    #+#             */
/*   Updated: 2023/09/27 15:20:00 by codespace        ###   ########.fr       */
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
	if (end == 0 || end >= BUFFER_SIZE)
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

void	append_from_rest(char *dst, char *src, int fd)
{
	int	i;
	int	length;
    int end;

	length = len(dst);
	i = 0;
	end = look_for_end(src);
	expand(dst, end);
	while (i <= end)
	{
		dst[i + length] = src[i];
		i++;
	}
}

char	*get_next_line(int fd)
{
    char		*line;
    static char	rest[BUFFER_SIZE + 1] = {0};
    static int  found;
	int			i;

	found = 0;
	i = 0;
	line = (char *) malloc(BUFFER_SIZE + 1);
	while (i < BUFFER_SIZE + 1)
		line[i++] = 0;
	while (!found)
    {
		redo_rest()
        found = append_from_rest(line, rest, fd);
    }
	line = expand(line, 2);
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