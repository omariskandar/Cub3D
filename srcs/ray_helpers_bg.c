/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_helpers_bg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 10:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/08 10:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	shade_if_side_bg(int color, int side)
{
	if (side == 1)
		return ((color >> 1) & 8355711);
	return (color);
}

static void	advance_to_next_wall_bg(t_game *g, t_ray *r)
{
	int		in_bounds;

	in_bounds = 1;
	while (in_bounds)
	{
		if (r->side_dist.x < r->side_dist.y)
		{
			r->side_dist.x += r->delta_dist.x;
			r->map.x += r->step.x;
			r->side = 0;
		}
		else
		{
			r->side_dist.y += r->delta_dist.y;
			r->map.y += r->step.y;
			r->side = 1;
		}
		if ((int)r->map.y < 0 || (int)r->map.y >= g->map.height
			|| (int)r->map.x < 0 || (int)r->map.x >= (int)ft_strlen(
				g->map.grid[(int)r->map.y]))
			in_bounds = 0;
		else if (g->map.grid[(int)r->map.y][(int)r->map.x] == '1')
			break ;
	}
}

static int	bg_color_from_ray_bg(t_game *g, t_ray *r, int y)
{
	t_texture	*tx;
	double		step;
	double		pos;
	double		start_unclipped;
	int			tex_y;
	int			col;
	int			vy;

	calculate_perp_wall_dist(g, r);
	calculate_line_height_and_draw_range(g, r);
	vy = y - g->pitch;
	if (vy < r->draw_start)
		return (g->map.ceiling_color);
	if (vy > r->draw_end)
		return (sample_floor_color_at(g, r, y));
	tx = get_wall_texture(g, r);
	calculate_wall_texture_coords(g, r, tx);
	step = (double)tx->height / (double)r->line_height;
	start_unclipped = (double)g->mlx.current_height * 0.5
		- (double)r->line_height * 0.5;
	pos = ((double)vy + 0.5 - start_unclipped) * step;
	if (pos < 0.0)
		pos = 0.0;
	tex_y = (int)pos;
	if (tex_y >= tx->height)
		tex_y = tx->height - 1;
	col = get_texture_color(tx, r->tex_x, tex_y);
	col = shade_if_side_bg(col, r->side);
	return (col);
}

int			bg_color_from_ray(t_game *g, t_ray *r, int y)
{
	return (bg_color_from_ray_bg(g, r, y));
}

void			advance_to_next_wall(t_game *g, t_ray *r)
{
	advance_to_next_wall_bg(g, r);
}
