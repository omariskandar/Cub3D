/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/01 15:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		get_texture_color(t_texture *texture, int x, int y)
{
	char		*dst;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	dst = texture->addr + (y * texture->line_length + x
			* (texture->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

int		load_texture(t_game *game, t_texture *texture, char *path)
{
	if (!path)
		return (1);
	texture->img = mlx_xpm_file_to_image(game->mlx.mlx_ptr, path,
			&texture->width, &texture->height);
	if (!texture->img)
		return (1);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
				&texture->line_length, &texture->endian);
	return (0);
}

static void	load_health_textures(t_game *game)
{
	load_texture(game, &game->hp_bar_bg,
			"./textures/health/health_bar_background.xpm");
	load_texture(game, &game->hp_bar_fill,
			"./textures/health/health_bar_fill.xpm");
	load_texture(game, &game->hp_icon,
			"./textures/health/HP.xpm");
	load_texture(game, &game->medkit_tex,
			"./textures/health/medkit.xpm");
}

static void	load_enemy_textures(t_game *game)
{
	load_texture(game, &game->enemy_tex,
			"./textures/enemy/enemy-standing.xpm");
	load_texture(game, &game->enemy_shoot_tex,
			"./textures/enemy/shooting.xpm");
	load_texture(game, &game->enemy_dead_tex,
			"./textures/enemy/dead.xpm");
}

static void	load_ui_textures(t_game *game)
{
	load_health_textures(game);
	load_texture(game, &game->game_over_tex,
			"./textures/health/game_over.xpm");
	load_texture(game, &game->ammo_tex,
			"./textures/weapon/amo.xpm");
	load_texture(game, &game->numbers_tex,
			"./textures/screen/numbers.xpm");
}

int		load_textures(t_game *game)
{
	if (!game->map.north_texture || !game->map.south_texture
		|| !game->map.west_texture || !game->map.east_texture)
		return (1);
	if (load_texture(game, &game->textures[0], game->map.north_texture))
		return (1);
	if (load_texture(game, &game->textures[1], game->map.south_texture))
		return (1);
	if (load_texture(game, &game->textures[2], game->map.west_texture))
		return (1);
	if (load_texture(game, &game->textures[3], game->map.east_texture))
		return (1);
	if (load_texture(game, &game->door_tex, "./textures/door/door-army.xpm"))
		return (1);
	if (load_texture(game, &game->floor_tex, "./textures/floor/floor_dirt.xpm"))
		return (1);
	if (load_texture(game, &game->weapon_tex,
			"./textures/weapon/weapon.xpm"))
		return (1);
	if (load_texture(game, &game->weapon1_tex,
			"./textures/weapon/weapon-1.xpm"))
		return (1);
	if (load_texture(game, &game->weapon2_tex,
			"./textures/weapon/weapon-2.xpm"))
		return (1);
	if (load_texture(game, &game->dot_tex, "./textures/weapon/dot.xpm"))
		return (1);
	load_enemy_textures(game);
	load_ui_textures(game);
	return (0);
}
