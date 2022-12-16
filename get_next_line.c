/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:18:46 by naal-jen          #+#    #+#             */
/*   Updated: 2022/12/16 10:17:27 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*str;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		if (str != NULL)
		{
			free(str);
			str = NULL;
		}
		return (NULL);
	}
	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(*buff));
	if (!buff)
		return (NULL);
	str = process_str(fd, buff, str);
	if (!str)
	{
		free(str);
		return (NULL);
	}
	new_str = process_line(str);
	str = delete(str);
	return (new_str);
}
/*int	main(void)
{
	int		fd;
	char	*loco;
	fd = 0;
	fd = open("read_error.txt", O_RDONLY);
	loco = get_next_line(fd);
	printf("%s", loco);
	free(loco);
	loco = get_next_line(fd);
	printf("%s", loco);
	free(loco);
	loco = get_next_line(fd);
	printf("%s", loco);
	free(loco);
	loco = get_next_line(fd);
	printf("%s", loco);
	free(loco);
	loco = get_next_line(fd);
	printf("%s", loco);
	free(loco);
	return (0);
}*/
