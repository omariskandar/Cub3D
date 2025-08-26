/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_direction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/01 15:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_player_direction_north(t_game *game)
{
	game->player.dir.x = 0.0;
	game->player.dir.y = -1.0;
	game->player.plane.x = 0.66;
	game->player.plane.y = 0.0;
}

void	set_player_direction_south(t_game *game)
{
	game->player.dir.x = 0.0;
	game->player.dir.y = 1.0;
	game->player.plane.x = -0.66;
	game->player.plane.y = 0.0;
}

void	set_player_direction_east(t_game *game)
{
	game->player.dir.x = 1.0;
	game->player.dir.y = 0.0;
	game->player.plane.x = 0.0;
	game->player.plane.y = 0.66;
}

void	set_player_direction_west(t_game *game)
{
	game->player.dir.x = -1.0;
	game->player.dir.y = 0.0;
	game->player.plane.x = 0.0;
	game->player.plane.y = -0.66;
}

void	set_player_direction(t_game *game, char spawn_char)
{
	if (spawn_char == 'N')
		set_player_direction_south(game);
	else if (spawn_char == 'S')
		set_player_direction_north(game);
	else if (spawn_char == 'E')
		set_player_direction_west(game);
	else if (spawn_char == 'W')
		set_player_direction_east(game);
}
