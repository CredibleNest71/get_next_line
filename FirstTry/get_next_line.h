/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:41:39 by codespace         #+#    #+#             */
/*   Updated: 2023/10/02 16:42:10 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10000000
#endif
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

char	*get_next_line(int fd);
int     redo_rest(char *rest, int fd);
char	*expand(char *old, int size);
char	*append_from_rest(char *src, int *found);
char	*ft_strjoin(char const *s1, char const *s2);
#endif