/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 11:35:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/01 11:35:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	close_game(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}

int	handle_key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_game(game);
	if (game->is_dead && keycode == KEY_SPACE)
		restart_game(game);
	if (game->is_dead)
		return (0);
	if (keycode == KEY_W)
		game->keys.w = 1;
	if (keycode == KEY_A)
		game->keys.a = 1;
	if (keycode == KEY_S)
		game->keys.s = 1;
	if (keycode == KEY_D)
		game->keys.d = 1;
	if (keycode == KEY_LEFT)
		game->keys.left = 1;
	if (keycode == KEY_RIGHT)
		game->keys.right = 1;
	if (keycode == KEY_SHIFT)
		game->keys.shift = 1;
	if (keycode == KEY_F)
		toggle_fullscreen(game);
	if (keycode == KEY_E)
		try_toggle_door(game);
	if (keycode == KEY_UP)
		game->keys.up = 1;
	if (keycode == KEY_DOWN)
		game->keys.down = 1;
	return (0);
}

int	handle_key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys.w = 0;
	if (keycode == KEY_A)
		game->keys.a = 0;
	if (keycode == KEY_S)
		game->keys.s = 0;
	if (keycode == KEY_D)
		game->keys.d = 0;
	if (keycode == KEY_LEFT)
		game->keys.left = 0;
	if (keycode == KEY_RIGHT)
		game->keys.right = 0;
	if (keycode == KEY_SHIFT)
		game->keys.shift = 0;
	if (keycode == KEY_UP)
		game->keys.up = 0;
	if (keycode == KEY_DOWN)
		game->keys.down = 0;
	return (0);
}

void	toggle_fullscreen(t_game *game)
{
	int		new_width;
	int		new_height;

	if (game->fullscreen)
	{
		new_width = WINDOW_WIDTH;
		new_height = WINDOW_HEIGHT;
	}
	else
	{
		new_width = FULLSCREEN_WIDTH;
		new_height = FULLSCREEN_HEIGHT;
	}
	destroy_window_and_image(game);
	create_new_window_and_image(game, new_width, new_height);
	register_event_handlers(game);
	game->fullscreen = !game->fullscreen;
}

int	game_loop(t_game *game)
{
	process_movement(game);
	process_rotation(game);
	process_pitch(game);
	update_doors(game);
	if (game->spr_count == 0)
		init_sprites(game);
	if (game->med_count == 0)
		init_medkits(game);
	if (game->ammo_count == 0)
		init_ammo_pickups(game);
	update_enemies(game);
	update_weapon_anim(game);
	update_medkits(game);
	update_ammo_pickups(game);
	if (!game->zbuffer)
		game->zbuffer = malloc(sizeof(double) * game->mlx.current_width);
	if (game->max_health == 0)
		init_health(game);
	clear_screen(game, COLOR_BLACK);
	render_3d_view(game);
	render_sprites(game);
	draw_minimap(game);
	draw_health_hud(game);
	draw_weapon_hud(game);
	draw_crosshair_dot(game);
	draw_death_overlay(game);
	draw_death_image(game);
	mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.win_ptr,
		game->mlx.img_ptr, 0, 0);
	draw_ammo_icon_hud(game);
	draw_ammo_hud(game);
	draw_press_e_hint(game);
	draw_death_message(game);
	handle_death_and_respawn(game);
	return (0);
}
