/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/01 12:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < game->mlx.current_width && y >= 0
		&& y < game->mlx.current_height)
	{
		dst = game->mlx.img_addr + (y * game->mlx.line_length
				+ x * (game->mlx.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_square(t_game *game, t_square sq)
{
	int	i;
	int	j;

	i = 0;
	while (i < sq.size)
	{
		j = 0;
		while (j < sq.size)
		{
			put_pixel(game, sq.x + j, sq.y + i, sq.color);
			j++;
		}
		i++;
	}
}

void	clear_screen(t_game *game, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->mlx.current_height)
	{
		x = 0;
		while (x < game->mlx.current_width)
		{
			put_pixel(game, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_map(t_game *game)
{
	int	y;
	int	x;

	if (!game->map.grid)
		return ;
	y = 0;
	while (y < game->map.height && (y * MAP_SCALE) < game->mlx.current_height)
	{
		x = 0;
		while (x < (int)ft_strlen(game->map.grid[y])
			&& (x * MAP_SCALE) < game->mlx.current_width)
		{
			draw_map_cell(game, x, y);
			x++;
		}
		y++;
	}
}

void	draw_direction_line(t_game *game, int player_x, int player_y)
{
	int		i;
	double	line_length;

	line_length = 20.0;
	i = 0;
	while (i <= (int)line_length)
	{
		put_pixel(game,
			player_x + (int)(game->player.dir.x * i),
			player_y + (int)(game->player.dir.y * i),
			COLOR_RED);
		i++;
	}
}
