/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:18:46 by naal-jen          #+#    #+#             */
/*   Updated: 2025/05/11 16:08:19 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

static char	*delete(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	new_str = (char *)malloc((ft_strlen(str) - i + 1) * sizeof(*new_str));
	if (!new_str)
		return (NULL);
	i++;
	j = 0;
	while (str[i])
		new_str[j++] = str[i++];
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

char	*process_line(char *str)
{
	int		i;
	char	*new_str;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] != '\n' && str[i])
		i++;
	new_str = (char *)malloc((i + 2) * sizeof(*new_str));
	if (!new_str)
		return (NULL);
	i = -1;
	while (str[++i] != '\n' && str[i])
	{
		new_str[i] = str[i];
	}
	if (str[i] == '\n')
	{
		new_str[i] = '\n';
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*process_str(int fd, char *buff, char *str)
{
	int	num;

	num = 1;
	while (!ft_strchr(str, '\n') && num != 0)
	{
		num = read(fd, buff, BUFFER_SIZE);
		if (num == -1)
		{
			free (buff);
			return (NULL);
		}
		buff[num] = '\0';
		str = ft_strjoin(str, buff);
	}
	free (buff);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*buff;
	char		*new_str;
	static char	*str[1024];

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		if (str[fd] != NULL)
		{
			free(str[fd]);
			str[fd] = NULL;
		}
		return (NULL);
	}
	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(*buff));
	if (!buff)
		return (NULL);
	str[fd] = process_str(fd, buff, str[fd]);
	if (!str[fd])
	{
		free(str[fd]);
		return (NULL);
	}
	new_str = process_line(str[fd]);
	str[fd] = delete(str[fd]);
	return (new_str);
}

/*int	main( void)
{
	int		fd1;
	int		fd2;
	char	*line;

	fd1 = open("test1.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd1 < 0)
	{
		printf("Error creating test1.txt\n");
		return (1);
	}
	write(fd1, "This is line 1 from file 1\n", 27);
	write(fd1, "This is line 2 from file 1\n", 27);
	write(fd1, "This is line 3 from file 1\n", 27);
	close(fd1);

	fd2 = open("test2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd2 < 0)
	{
		printf("Error creating test2.txt\n");
		return (1);
	}
	write(fd2, "This is line 1 from file 2\n", 27);
	write(fd2, "This is line 2 from file 2\n", 27);
	close(fd2);
	
	fd1 = open("test1.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	
	if (fd1 < 0 || fd2 < 0)
	{
		printf("Error opening test files\n");
		return (1);
	}

	line = get_next_line(fd1);
	printf("File 1, Line 1: %s", line);
	free(line);

	line = get_next_line(fd2);
	printf("File 2, Line 1: %s", line);
	free(line);

	line = get_next_line(fd1);
	printf("File 1, Line 2: %s", line);
	free(line);

	line = get_next_line(fd2);
	printf("File 2, Line 2: %s", line);
	free(line);

	line = get_next_line(fd1);
	printf("File 1, Line 3: %s", line);
	free(line);

	line = get_next_line(fd2);
	if (line)
	{
		printf("File 2, Line 3: %s", line);
		free(line);
	}
	else
		printf("File 2, Line 3: (NULL - End of file)\n");
	
	line = get_next_line(-1);
	if (line == NULL)
		printf("Invalid FD test: Correctly returned NULL\n");
	else
	{
		printf("Invalid FD test: Error - did not return NULL\n");
		free(line);
	}

	close(fd1);
	close(fd2);
	return (0);
} */
