/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calculation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/01 15:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	calculate_wall_distance(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map.x - game->player.pos.x / MAP_SCALE
				+ (1 - ray->step.x) / 2) / ray->dir.x;
	else
		ray->perp_wall_dist = (ray->map.y - game->player.pos.y / MAP_SCALE
				+ (1 - ray->step.y) / 2) / ray->dir.y;
}

void	calculate_perp_wall_dist(t_game *game, t_ray *ray)
{
	double	dx;
	double	dy;

	if (ray->side == 0)
	{
		dx = ray->dir.x;
		if (dx == 0)
			dx = 1e-6;
		ray->perp_wall_dist = (ray->map.x - game->player.pos.x / MAP_SCALE)
			/ dx + (1 - ray->step.x) / 2 / dx;
	}
	else
	{
		dy = ray->dir.y;
		if (dy == 0)
			dy = 1e-6;
		ray->perp_wall_dist = (ray->map.y - game->player.pos.y / MAP_SCALE)
			/ dy + (1 - ray->step.y) / 2 / dy;
	}
	if (ray->perp_wall_dist < 1e-6)
		ray->perp_wall_dist = 1e-6;
}

void	calculate_line_height_and_draw_range(t_game *game, t_ray *ray)
{
	if (ray->perp_wall_dist < 1e-6)
		ray->perp_wall_dist = 1e-6;
	ray->line_height = (int)(game->mlx.current_height / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + game->mlx.current_height / 2
		+ game->pitch;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + game->mlx.current_height / 2
		+ game->pitch;
	if (ray->draw_end >= game->mlx.current_height)
		ray->draw_end = game->mlx.current_height - 1;
}

void	calculate_wall_texture_coords(t_game *game,
			t_ray *ray, t_texture *texture)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = game->player.pos.y / MAP_SCALE + ray->perp_wall_dist
			* ray->dir.y;
	else
		wall_x = game->player.pos.x / MAP_SCALE + ray->perp_wall_dist
			* ray->dir.x;
	wall_x -= floor(wall_x);
	ray->tex_x = (int)(wall_x * (double)texture->width);
	if ((ray->side == 0 && ray->dir.x > 0) || (ray->side == 1
			&& ray->dir.y < 0))
		ray->tex_x = texture->width - ray->tex_x - 1;
}
