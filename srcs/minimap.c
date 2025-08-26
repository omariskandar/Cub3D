/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 13:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/01 13:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_minimap_background_and_border(t_game *game)
{
	int	center_x;
	int	center_y;
	int	x;
	int	y;

	center_x = game->mlx.current_width - MINIMAP_RADIUS - MINIMAP_MARGIN;
	center_y = game->mlx.current_height - MINIMAP_RADIUS - MINIMAP_MARGIN;
	y = center_y - MINIMAP_RADIUS - 5;
	while (y <= center_y + MINIMAP_RADIUS + 5)
	{
		x = center_x - MINIMAP_RADIUS - 5;
		while (x <= center_x + MINIMAP_RADIUS + 5)
		{
			draw_minimap_border_pixel(game, x, y, center_x);
			x++;
		}
		y++;
	}
}

void	draw_minimap_cell_at_pos(t_game *game, int world_x, int world_y)
{
	int	center_x;
	int	center_y;
	int	screen_x;
	int	screen_y;

	center_x = game->mlx.current_width - MINIMAP_RADIUS - MINIMAP_MARGIN;
	center_y = game->mlx.current_height - MINIMAP_RADIUS - MINIMAP_MARGIN;
	screen_x = center_x + ((int)game->player.pos.x - world_x) / 4;
	screen_y = center_y + ((int)game->player.pos.y - world_y) / 4;
	if (is_in_minimap_circle(screen_x - center_x, screen_y - center_y,
			MINIMAP_RADIUS - 2))
	{
		if (world_y / MAP_SCALE >= 0 && world_y / MAP_SCALE < game->map.height
			&& world_x / MAP_SCALE >= 0 && world_x / MAP_SCALE
			< (int)ft_strlen(game->map.grid[world_y / MAP_SCALE]))
		{
			if (game->map.grid[world_y / MAP_SCALE][world_x / MAP_SCALE] == '1')
				put_pixel(game, screen_x, screen_y, MINIMAP_WALL);
			else if (game->map.grid[world_y / MAP_SCALE][world_x / MAP_SCALE]
				== '0')
				put_pixel(game, screen_x, screen_y, MINIMAP_FLOOR);
		}
	}
}

void	draw_minimap_player_professional(t_game *game)
{
	int	center_x;
	int	center_y;
	int	i;

	center_x = game->mlx.current_width - MINIMAP_RADIUS - MINIMAP_MARGIN;
	center_y = game->mlx.current_height - MINIMAP_RADIUS - MINIMAP_MARGIN;
	i = -3;
	while (i <= 3)
	{
		if (is_in_minimap_circle(i, 0, MINIMAP_RADIUS - 2))
			put_pixel(game, center_x + i, center_y, MINIMAP_PLAYER_DOT);
		if (is_in_minimap_circle(0, i, MINIMAP_RADIUS - 2))
			put_pixel(game, center_x, center_y + i, MINIMAP_PLAYER_DOT);
		i++;
	}
	i = 4;
	while (i <= 15)
	{
		if (is_in_minimap_circle(-(int)(game->player.dir.x * i),
			-(int)(game->player.dir.y * i), MINIMAP_RADIUS - 2))
			put_pixel(game, center_x - (int)(game->player.dir.x * i),
				center_y - (int)(game->player.dir.y * i), MINIMAP_DIRECTION);
		i++;
	}
}

void	draw_minimap_world_cells(t_game *game)
{
	int	world_x;
	int	world_y;
	int	start_x;
	int	start_y;

	start_x = (int)game->player.pos.x - MINIMAP_RADIUS * 4;
	start_y = (int)game->player.pos.y - MINIMAP_RADIUS * 4;
	world_y = start_y;
	while (world_y < (int)game->player.pos.y + MINIMAP_RADIUS * 4)
	{
		world_x = start_x;
		while (world_x < (int)game->player.pos.x + MINIMAP_RADIUS * 4)
		{
			draw_minimap_cell_at_pos(game, world_x, world_y);
			world_x += 4;
		}
		world_y += 4;
	}
}

void	draw_minimap(t_game *game)
{
	draw_minimap_background_and_border(game);
	draw_minimap_world_cells(game);
	draw_minimap_items(game);
	draw_minimap_enemies(game);
	draw_minimap_player_professional(game);
}
