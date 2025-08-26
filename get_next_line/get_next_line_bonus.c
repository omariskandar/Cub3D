/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oiskanda <oiskanda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 19:15:08 by oiskanda          #+#    #+#             */
/*   Updated: 2025/05/27 12:58:29 by oiskanda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_line(int fd, char *str)
{
	char	*buffer;
	int		read_bytes;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while ((!ft_strchr(str, '\n') || !ft_strchr(str, '\0')) && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		str = ft_strjoin(str, buffer);
	}
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str[fd] = read_line(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	line = ft_copy_to_newline(str[fd]);
	str[fd] = ft_copy_left_from_buffer(str[fd]);
	return (line);
}

// int	main(int argc, char **argv)
// {
// 	char	*line;
// 	int		fd;
// 	int		i;

// 	if (argc < 2)
// 	{
// 		printf("Usage: %s file1 [file2 ...]\n", argv[0]);
// 		return (1);
// 	}
// 	i = 1;
// 	while (i < argc)
// 	{
// 		fd = open(argv[i], O_RDONLY);
// 		if (fd < 0)
// 		{
// 			perror(argv[i]);
// 			i++;
// 			continue ;
// 		}
// 		printf("----- %s -----\n", argv[i]);
// 		while ((line = get_next_line(fd)))
// 		{
// 			printf("%s", line);
// 			free(line);
// 		}
// 		close(fd);
// 		i++;
// 	}
// 	return (0);
// }