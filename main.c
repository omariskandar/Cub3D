/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 00:08:59 by oiskanda          #+#    #+#             */
/*   Updated: 2025/08/01 02:04:58 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (exit_error("Usage: ./cub3d <map.cub>"));
	if (contains_cub(argv[1]) != 0)
		return (exit_error("Error: Invalid file extension"));
	if (init_game(&game) != 0)
		return (exit_error("Error: Failed to initialize game"));
	if (parse_map_file(argv[1], &game) != 0)
		return (exit_error("Error: Failed to parse map file"));
	if (validate_map(&game) != 0)
		return (1);
	if (set_player_position(&game) != 0)
		return (1);
	if (validate_textures(&game) != 0)
		return (1);
	if (load_textures(&game) != 0)
		return (exit_error("Error: Failed to load textures"));
	if (init_doors_anim(&game) != 0)
		return (exit_error("Error: Failed to init doors"));
	register_event_handlers(&game);
	mlx_loop_hook(game.mlx.mlx_ptr, game_loop, &game);
	mlx_loop(game.mlx.mlx_ptr);
	return (0);
}
