/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:26:53 by codespace         #+#    #+#             */
/*   Updated: 2023/10/04 14:52:33 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

void	*zalloc(size_t size)
{
	char	*assign;
	void	*ans;
	size_t	i;

	i = 0;
	if (!size)
		return (malloc(0));
	ans = malloc(size);
	if (!ans)
		return (0);
	assign = (char *) ans;
	while (i < size)
		assign[i++] = 0;
	return (ans);
}

char	*get_next_line(int fd)
{
    char		*line;
    static char	rest[BUFFER_SIZE + 1] = {0};
	char		*str_to_add;
    int			found;
	int			i;

	found = 0;
	i = 0;
	line = NULL;
	while (!found)
    {
		i = redo_rest(rest, fd);
		if (i <= 0)
			return (line);
        str_to_add = get_from_rest(rest, &found);
		line = ft_strjoin(line, str_to_add);
    }
	return (line);
}

// int	main(void)
// {
// 	char	*line;
// 	int		fd1;
// 	int		fd2;
// 	int		fd3;
// 	int		fdtest;
// 	fd1 = open("tests/test.txt", O_RDONLY);
// 	fd2 = open("tests/test2.txt", O_RDONLY);
// 	fd3 = open("tests/test3.txt", O_RDONLY);
// 	fdtest = fd3;
	
// 	line = get_next_line(fdtest);
// 	printf("\nLINE= %s", line);
// 	free(line);

// 	line = get_next_line(fdtest);
// 	printf("\nLINE= %s",line);	
// 	free(line);

// 	line = get_next_line(fdtest);
// 	printf("\nLINE= %s", line);
// 	free(line);

// 	line = get_next_line(fdtest);
// 	printf("\nLINE= %s", line);
// 	free(line);

// 	line = get_next_line(fdtest);
// 	printf("\nLINE= %s", line);
// 	free(line);
	
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// 	return (0);
// }