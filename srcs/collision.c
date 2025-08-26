/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 13:30:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/01 13:30:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_single_point(t_game *game, int map_x, int map_y)
{
	if (map_y >= 0 && map_y < game->map.height
		&& map_x >= 0 && map_x < (int)ft_strlen(game->map.grid[map_y]))
	{
		if (game->map.grid[map_y][map_x] == '1')
			return (1);
		if (game->map.grid[map_y][map_x] == 'D')
			return (1);
		return (0);
	}
	return (1);
}

int	check_collision(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;
	int	margin;

	margin = 5;
	map_x = (int)((x + margin) / MAP_SCALE);
	map_y = (int)((y + margin) / MAP_SCALE);
	if (check_single_point(game, map_x, map_y))
		return (1);
	map_x = (int)((x - margin) / MAP_SCALE);
	map_y = (int)((y - margin) / MAP_SCALE);
	if (check_single_point(game, map_x, map_y))
		return (1);
	map_x = (int)((x + margin) / MAP_SCALE);
	map_y = (int)((y - margin) / MAP_SCALE);
	if (check_single_point(game, map_x, map_y))
		return (1);
	map_x = (int)((x - margin) / MAP_SCALE);
	map_y = (int)((y + margin) / MAP_SCALE);
	if (check_single_point(game, map_x, map_y))
		return (1);
	return (0);
}

int	touch(float ray_x, float ray_y, t_game *game)
{
	int	map_x;
	int	map_y;

	map_x = (int)(ray_x / MAP_SCALE);
	map_y = (int)(ray_y / MAP_SCALE);
	if (map_y >= 0 && map_y < game->map.height
		&& map_x >= 0 && map_x < (int)ft_strlen(game->map.grid[map_y]))
	{
		if (game->map.grid[map_y][map_x] == '1')
			return (1);
		return (0);
	}
	return (1);
}

void	draw_map_cell(t_game *game, int x, int y)
{
	t_square	sq;

	sq.x = x * MAP_SCALE;
	sq.y = y * MAP_SCALE;
	sq.size = MAP_SCALE;
	if (game->map.grid[y][x] == '1')
	{
		sq.color = COLOR_WHITE;
		draw_square(game, sq);
	}
	else if (game->map.grid[y][x] == '0')
	{
		sq.color = 0x404040;
		draw_square(game, sq);
	}
}

void	draw_ray_line(t_game *game, t_line line)
{
	int	dx;
	int	dy;
	int	steps;
	int	i;

	dx = line.end_x - line.start_x;
	dy = line.end_y - line.start_y;
	if (abs(dx) > abs(dy))
		steps = abs(dx);
	else
		steps = abs(dy);
	if (steps == 0)
		return ;
	i = 0;
	while (i <= steps)
	{
		put_pixel(game,
			line.start_x + (dx * i) / steps,
			line.start_y + (dy * i) / steps,
			COLOR_BLUE);
		i++;
	}
}
