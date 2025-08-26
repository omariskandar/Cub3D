/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/01 15:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_map_closed(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map.grid[i])
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (game->map.grid[i][j] == '0' || game->map.grid[i][j] == 'N'
				|| game->map.grid[i][j] == 'S' || game->map.grid[i][j] == 'E'
				|| game->map.grid[i][j] == 'W')
			{
				if (!check_border_position(game, i, j))
					return (0);
				if (!check_adjacent_spaces(game, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	validate_map(t_game *game)
{
	if (!check_map_characters(game))
		return (exit_error("Error: Invalid character in map"));
	if (count_player_spawns(game) != 1)
		return (exit_error("Error: Map must have exactly one player spawn"));
	if (!check_map_closed(game))
		return (exit_error("Error: Map must be closed/surrounded by walls"));
	return (0);
}
