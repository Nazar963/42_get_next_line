/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 13:00:19 by naal-jen          #+#    #+#             */
/*   Updated: 2022/12/13 16:30:13 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include   <stdio.h>
# include   <stdlib.h>
# include   <stddef.h>
# include   <sys/types.h>
# include   <sys/stat.h>
# include   <fcntl.h>
# include   <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
char	*process_str(int fd, char *buff, char *str);
char	*process_line(char *str);

char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *str, char *buff);
size_t	ft_strlen(char *s);

#endif