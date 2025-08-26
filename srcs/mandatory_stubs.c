/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory_stubs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/01 15:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_map_cell(t_game *game, int x, int y)
{
	(void)game;
	(void)x;
	(void)y;
}

int	check_collision(t_game *game, double x, double y)
{
	(void)game;
	(void)x;
	(void)y;
	return (0);
}

void	draw_floor_tex_pixel(t_game *game, t_ray *ray, int x, int y)
{
	(void)ray;
	put_pixel(game, x, y, game->map.floor_color);
}

int	sample_floor_color_at(t_game *game, t_ray *ray, int y)
{
	(void)ray;
	(void)y;
	return (game->map.floor_color);
}

int			medkit_overlay_color(t_game *g, double wx, double wy, int base)
{
	(void)g;
	(void)wx;
	(void)wy;
	return (base);
}

int			handle_mouse_move(int x, int y, t_game *g)
{
	(void)x;
	(void)y;
	(void)g;
	return (0);
}

int			init_medkits(t_game *g)
{
	(void)g;
	return (0);
}

void			free_medkits(t_game *g)
{
	(void)g;
}

void			update_medkits(t_game *g)
{
	(void)g;
}

int			ammo_overlay_color(t_game *g, double wx, double wy, int base)
{
	(void)g;
	(void)wx;
	(void)wy;
	return (base);
}

int			init_ammo_pickups(t_game *g)
{
	(void)g;
	return (0);
}

void			free_ammo_pickups(t_game *g)
{
	(void)g;
}

void			update_ammo_pickups(t_game *g)
{
	(void)g;
}

void			draw_death_image(t_game *g)
{
	(void)g;
}

void			draw_ammo_hud(t_game *g)
{
	(void)g;
}

void			draw_ammo_icon_hud(t_game *g)
{
	(void)g;
}
