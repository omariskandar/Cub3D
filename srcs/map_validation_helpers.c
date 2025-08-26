/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_helpers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/01 15:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W' || c == ' ' || c == 'D' || c == 'O' || c == 'T'
		|| c == 'M' || c == 'A');
}

int	check_map_characters(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map.grid[i])
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (!is_valid_map_char(game->map.grid[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	count_player_spawns(t_game *game)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (game->map.grid[i])
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (game->map.grid[i][j] == 'N' || game->map.grid[i][j] == 'S'
				|| game->map.grid[i][j] == 'E' || game->map.grid[i][j] == 'W')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

int	check_border_position(t_game *game, int i, int j)
{
	if (i == 0 || i == game->map.height - 1 || j == 0
		|| j == (int)ft_strlen(game->map.grid[i]) - 1)
		return (0);
	return (1);
}

int	check_adjacent_spaces(t_game *game, int i, int j)
{
	if (game->map.grid[i - 1][j] == ' ' || game->map.grid[i + 1][j] == ' '
		|| game->map.grid[i][j - 1] == ' ' || game->map.grid[i][j + 1] == ' ')
		return (0);
	return (1);
}
