/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:30:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/01 12:30:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parse_texture_line(char *line, t_game *game)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		handle_texture_path(line, "NO ", &game->map.north_texture);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		handle_texture_path(line, "SO ", &game->map.south_texture);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		handle_texture_path(line, "WE ", &game->map.west_texture);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		handle_texture_path(line, "EA ", &game->map.east_texture);
	else if (ft_strncmp(line, "F ", 2) == 0)
	{
		handle_color(line, "F ", &game->map.floor_color);
		if (game->map.floor_color == -1)
			return (1);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		handle_color(line, "C ", &game->map.ceiling_color);
		if (game->map.ceiling_color == -1)
			return (1);
	}
	return (0);
}

void	process_map_line(char *line, t_game *game, int *i, int *map_started)
{
	if (!*map_started && (line[0] == '1' || line[0] == '0' || line[0] == ' '))
	{
		*map_started = 1;
		game->map.grid[*i] = trim_newline(line);
		if (*i == 0)
			game->map.width = ft_strlen(game->map.grid[*i]);
		(*i)++;
	}
	else if (*map_started && (line[0] == '1' || line[0] == '0'
			|| line[0] == ' '))
	{
		game->map.grid[*i] = trim_newline(line);
		(*i)++;
	}
	else if (!*map_started)
	{
		if (parse_texture_line(line, game))
		{
			free(line);
			return ;
		}
		free(line);
	}
	else
		free(line);
}

int	read_map_data(int fd, t_game *game)
{
	char	*line;
	int		i;
	int		map_started;

	i = 0;
	map_started = 0;
	line = get_next_line(fd);
	while (line)
	{
		process_map_line(line, game, &i, &map_started);
		line = get_next_line(fd);
	}
	game->map.grid[i] = NULL;
	return (0);
}

int	parse_map_file(char *filename, t_game *game)
{
	int	fd;

	game->map.height = count_map_lines(filename);
	if (game->map.height == 0)
		return (1);
	game->map.grid = malloc(sizeof(char *) * (game->map.height + 1));
	if (!game->map.grid)
		return (1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		free(game->map.grid);
		return (1);
	}
	if (read_map_data(fd, game))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

void	free_map(t_game *game)
{
	int	i;

	if (game->map.grid)
	{
		i = 0;
		while (game->map.grid[i])
		{
			free(game->map.grid[i]);
			i++;
		}
		free(game->map.grid);
		game->map.grid = NULL;
	}
	free_textures(game);
}
