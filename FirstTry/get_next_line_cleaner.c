/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_cleaner.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:26:53 by codespace         #+#    #+#             */
/*   Updated: 2023/09/28 16:38:08 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
    char		*line;
    static char	rest[BUFFER_SIZE + 1] = {0};
    int			found;
	int			i;

	found = 0;
	i = 0;
	line = (char *) malloc(10);
	line[0] = 0;
	if (!line)
		return (NULL);
	while (i < BUFFER_SIZE)
		line[i++] = 0;
	while (!found)
    {
		redo_rest(rest, fd);
        append_from_rest(line, rest, fd, &found);
		printf("LINE ATM = %s\n", line);
    }
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
	
	printf("%s", get_next_line(fd1));


	// printf("LINE= %s", line);
	// free(line);

	// line = get_next_line(fd1);
	// printf("LINE= %s",line);	
	// free(line);

	// line = get_next_line(fd1);
	// printf("LINE= %s", line);
	// free(line);

	// line = get_next_line(fd1);
	// printf("LINE= %s", line);
	// free(line);

	// line = get_next_line(fd1);
	// printf("LINE= %s", line);
	// free(line);
	
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}