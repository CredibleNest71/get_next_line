/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:32:08 by codespace         #+#    #+#             */
/*   Updated: 2023/09/26 14:23:02 by codespace        ###   ########.fr       */
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

char	get_c(int fd)
{
	char	buf[1];
	read(fd, buf, 1);
	return (buf[0]);
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

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	i;

	i = 0;
	if (!size)
		return (ft_strlen(src));
	while (src[i] && (i < size - 1))
	{
		dest[i] = src[i];
		i++;
	}
	return (ft_strlen(src));
}

char	*get_next_line(int fd)
{
	char			*temp;
	char			*line;
	unsigned int	size;
	unsigned int	i;

	i = 0;
	size = 32;
	line = (char *) malloc(size + 1);
	if (!line)
		return (0);
	while (line[i] != '\n')
	{
		line[i] = get_c(fd);
		if (line[i] == '\n' || line[i] == 0)
			break;
		if (i == size - 1)
		{
			size *= 2;
			temp = (char *) malloc(size);
			ft_strlcpy(temp, line, size);
			free(line);
			line = temp;
		}
		i++;
	}
	line[i++] = '\n';
	line[i] = 0;
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