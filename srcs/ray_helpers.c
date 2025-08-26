/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/01 15:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void			draw_wall_slice_ceiling(t_game *game, int x, int y)
{
	put_pixel(game, x, y, game->map.ceiling_color);
}

static int		background_color_at(t_game *g, t_ray *hit, int y)
{
	t_ray		cpy;

	cpy = *hit;
	advance_to_next_wall(g, &cpy);
	return (bg_color_from_ray(g, &cpy, y));
}

static int		in_bounds_cell(t_game *g, int mx, int my)
{
	if (my < 0 || my >= g->map.height)
		return (0);
	if (mx < 0 || mx >= (int)ft_strlen(g->map.grid[my]))
		return (0);
	return (1);
}

static void		draw_wall_band(t_game *g, t_ray *r, int x)
{
	int			y;
	double		step;
	double		texpos;
	double		start;
	int			tex_y;
	int			col;
	t_texture	*tx;

	tx = get_wall_texture(g, r);
	if (in_bounds_cell(g, (int)r->map.x, (int)r->map.y)
		&& g->map.grid[(int)r->map.y][(int)r->map.x] == 'D')
		tx = &g->door_tex;
	step = (double)tx->height / (double)r->line_height;
	start = (double)g->mlx.current_height * 0.5
		- (double)r->line_height * 0.5 + (double)g->pitch;
	texpos = ((double)r->draw_start + 0.5 - start) * step;
	y = r->draw_start;
	while (y <= r->draw_end)
	{
		tex_y = (int)texpos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tx->height)
			tex_y = tx->height - 1;
		col = sample_wall_color(g, r, tx, tex_y);
		if (col < 0)
			col = background_color_at(g, r, y);
		else if (r->side == 1)
			col = (col >> 1) & 8355711;
		put_pixel(g, x, y, col);
		texpos += step;
		y++;
	}
}

void			draw_wall_slice(t_game *game, t_ray *ray, int x, t_texture *texture)
{
	int			y;

	(void)texture;
	y = 0;
	while (y < ray->draw_start && y < game->mlx.current_height)
	{
		draw_wall_slice_ceiling(game, x, y);
		y++;
	}
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= game->mlx.current_height)
		ray->draw_end = game->mlx.current_height - 1;
	if (ray->draw_start <= ray->draw_end)
		draw_wall_band(game, ray, x);
	y = ray->draw_end + 1;
	while (y < game->mlx.current_height)
	{
		draw_floor_tex_pixel(game, ray, x, y);
		y++;
	}
}
