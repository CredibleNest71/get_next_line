/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:26:53 by codespace         #+#    #+#             */
/*   Updated: 2023/10/03 09:56:01 by codespace        ###   ########.fr       */
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
	char		*str_to_add;
    int			found;
	int			i;
	int			first;

	first = 1;
	found = 0;
	i = 0;
	line = (char *) malloc(1);
	if (!line)
		return (NULL);
	line[0] = 0;
	while (!found)
    {
		i = redo_rest(rest, fd);
		if (i < 0 || (first && i == 0))
		{
			free(line);
			return (NULL);
		}
		if (i == 0)
			return (line);
		first = 0;
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
// 	fd2 = open("tests/test.txt", O_RDONLY);
// 	fd1 = open("tests/test2.txt", O_RDONLY);
// 	fd3 = open("tests/test3.txt", O_RDONLY);

	
// 	line = get_next_line(fd1);
// 	printf("LINE= %s", line);
// 	free(line);

// 	line = get_next_line(fd1);
// 	printf("LINE= %s",line);	
// 	free(line);

// 	line = get_next_line(fd1);
// 	printf("LINE= %s", line);
// 	free(line);

// 	line = get_next_line(fd1);
// 	printf("LINE= %s", line);
// 	free(line);

// 	line = get_next_line(fd1);
// 	printf("LINE= %s", line);
// 	free(line);
	
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// 	return (0);
// }