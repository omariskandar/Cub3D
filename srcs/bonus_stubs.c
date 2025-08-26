/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_stubs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/01 15:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_minimap(t_game *game)
{
	(void)game;
}

void	destroy_window_and_image(t_game *game)
{
	(void)game;
}

void	create_new_window_and_image(t_game *game,
			int new_width, int new_height)
{
	(void)game;
	(void)new_width;
	(void)new_height;
}

void	register_event_handlers(t_game *game)
{
	mlx_hook(game->mlx.win_ptr, 2, 1L << 0, handle_key_press, game);
	mlx_hook(game->mlx.win_ptr, 3, 1L << 1, handle_key_release, game);
	mlx_hook(game->mlx.win_ptr, 17, 1L << 17, close_game, game);
}

void	process_pitch(t_game *game)
{
	(void)game;
}
