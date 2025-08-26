/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/01 15:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	destroy_window_and_image(t_game *game)
{
	if (game->zbuffer)
		free(game->zbuffer);
	game->zbuffer = NULL;
	if (game->mlx.img_ptr)
		mlx_destroy_image(game->mlx.mlx_ptr, game->mlx.img_ptr);
	if (game->mlx.win_ptr)
		mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
}

void	create_new_window_and_image(t_game *game, int new_width, int new_height)
{
	game->mlx.current_width = new_width;
	game->mlx.current_height = new_height;
	game->mlx.win_ptr = mlx_new_window(game->mlx.mlx_ptr,
			new_width, new_height, "Cub3D");
	game->mlx.img_ptr = mlx_new_image(game->mlx.mlx_ptr,
			new_width, new_height);
	game->mlx.img_addr = mlx_get_data_addr(game->mlx.img_ptr,
				&game->mlx.bits_per_pixel,
				&game->mlx.line_length, &game->mlx.endian);
	game->zbuffer = malloc(sizeof(double) * new_width);
}

void	register_event_handlers(t_game *game)
{
	mlx_hook(game->mlx.win_ptr, 2, 1L << 0, handle_key_press, game);
	mlx_hook(game->mlx.win_ptr, 3, 1L << 1, handle_key_release, game);
	mlx_mouse_hook(game->mlx.win_ptr, handle_mouse_press, game);
	mlx_hook(game->mlx.win_ptr, 6, 1L << 6, handle_mouse_move, game);
	mlx_hook(game->mlx.win_ptr, 17, 1L << 17, close_game, game);
	mlx_mouse_hide(game->mlx.mlx_ptr, game->mlx.win_ptr);
}
