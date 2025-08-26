/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_position.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/01 15:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	find_player_spawn(t_game *game, int *spawn_x, int *spawn_y)
{
	int	i;
	int	j;

	i = 0;
	while (game->map.grid[i])
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (game->map.grid[i][j] == 'N' || game->map.grid[i][j] == 'S'
				|| game->map.grid[i][j] == 'E' || game->map.grid[i][j] == 'W')
			{
				*spawn_x = j;
				*spawn_y = i;
				return (game->map.grid[i][j]);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	set_player_position(t_game *game)
{
	int		spawn_x;
	int		spawn_y;
	char	spawn_char;

	spawn_char = find_player_spawn(game, &spawn_x, &spawn_y);
	if (!spawn_char)
		return (exit_error("Error: No player spawn found"));
	game->player.pos.x = spawn_x * MAP_SCALE + MAP_SCALE / 2;
	game->player.pos.y = spawn_y * MAP_SCALE + MAP_SCALE / 2;
	set_player_direction(game, spawn_char);
	game->map.grid[spawn_y][spawn_x] = '0';
	return (0);
}
