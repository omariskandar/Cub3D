/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:59:34 by oiskanda          #+#    #+#             */
/*   Updated: 2025/05/27 13:00:58 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(int fd, char *str)
{
	char	*buffer;
	char	*temp;
	int		read_bytes;

	if (!str)
	{
		str = malloc(sizeof(char) * 1);
		if (!str)
			return (NULL);
		str[0] = '\0';
	}
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(str, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		temp = str;
		str = ft_strjoin(str, buffer);
		free(temp);
		if (!str)
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str = read_line(fd, str);
	if (!str || str[0] == '\0')
	{
		free(str);
		str = NULL;
		return (NULL);
	}
	line = ft_copy_to_newline(str);
	str = ft_copy_left_from_buffer(str);
	return (line);
}

// int	main(int argc, char **argv)
// {
// 	char	*str;
// 	int		fd;
// 	int		i;

// 	if (argc < 2)
// 		return (1);
// 	i = 1;
// 	while (i < argc)
// 	{
// 		fd = open(argv[i], O_RDONLY);
// 		while (str = get_next_line(fd))
// 		{
// 			printf("%s", str);
// 			free(str);
// 		}
// 		close(fd);
// 		i++;
// 	}
// 	return (0);
// }