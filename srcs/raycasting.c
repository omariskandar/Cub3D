/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 12:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/01 12:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void				draw_floor_pixel(t_game *game, int x, int y)
{
	put_pixel(game, x, y, game->map.floor_color);
}

static int			in_bounds_cell(t_game *g, int mx, int my)
{
	if (my < 0 || my >= g->map.height)
		return (0);
	if (mx < 0 || mx >= (int)ft_strlen(g->map.grid[my]))
		return (0);
	return (1);
}

void				draw_textured_wall(t_game *game, t_ray *ray, int x)
{
	t_texture		*texture;
	char			cell;
	int				mx;
	int				my;

	texture = get_wall_texture(game, ray);
	mx = (int)ray->map.x;
	my = (int)ray->map.y;
	if (in_bounds_cell(game, mx, my))
	{
		cell = game->map.grid[my][mx];
		if (cell == 'D')
			texture = &game->door_tex;
	}
	calculate_wall_texture_coords(game, ray, texture);
	draw_wall_slice(game, ray, x, texture);
	if (game->zbuffer)
		game->zbuffer[x] = ray->perp_wall_dist;
}

void				cast_ray(t_game *game, int x)
{
	t_ray			ray;

	init_ray(game, &ray, x);
	calculate_step_and_side_dist(game, &ray);
	perform_dda(game, &ray);
	calculate_perp_wall_dist(game, &ray);
	calculate_line_height_and_draw_range(game, &ray);
	draw_textured_wall(game, &ray, x);
}

void				render_3d_view(t_game *game)
{
	int				x;

	x = 0;
	while (x < game->mlx.current_width)
	{
		cast_ray(game, x);
		x++;
	}
}
