/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_enemies_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/12 14:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		draw_minimap_enemies(t_game *g)
{
	int		cx;
	int		cy;
	int		k;
	int		ex;
	int		ey;
	int		sx;
	int		sy;
	int		r;
	int		rs;
	int		dx;
	int		dy;

	if (g->spr_count <= 0 || !g->spr_x || !g->spr_y)
		return ;
	cx = g->mlx.current_width - MINIMAP_RADIUS - MINIMAP_MARGIN;
	cy = g->mlx.current_height - MINIMAP_RADIUS - MINIMAP_MARGIN;
	r = 3;
	rs = r * r;
	k = 0;
	while (k < g->spr_count)
	{
		if (!g->spr_alive || g->spr_alive[k])
		{
			ex = g->spr_x[k] * MAP_SCALE + MAP_SCALE / 2;
			ey = g->spr_y[k] * MAP_SCALE + MAP_SCALE / 2;
			sx = cx + ((int)g->player.pos.x - ex) / 4;
			sy = cy + ((int)g->player.pos.y - ey) / 4;
			dy = -r;
			while (dy <= r)
			{
				dx = -r;
				while (dx <= r)
				{
					if (dx * dx + dy * dy <= rs
						&& is_in_minimap_circle(sx - cx + dx,
						sy - cy + dy, MINIMAP_RADIUS - 2))
						put_pixel(g, sx + dx, sy + dy, COLOR_RED);
					dx++;
				}
				dy++;
			}
		}
		k++;
	}
}

static void	draw_minimap_medkits(t_game *g)
{
	int		cx;
	int		cy;
	int		r;
	int		k;
	int		sx;
	int		sy;
	int		dx;
	int		dy;
	int		rs;
	int		ex;
	int		ey;

	if (!g->med_x || !g->med_y || g->med_count <= 0)
		return ;
	cx = g->mlx.current_width - MINIMAP_RADIUS - MINIMAP_MARGIN;
	cy = g->mlx.current_height - MINIMAP_RADIUS - MINIMAP_MARGIN;
	r = 2;
	rs = r * r;
	k = 0;
	while (k < g->med_count)
	{
		if (!g->med_alive || g->med_alive[k])
		{
			ex = g->med_x[k] * MAP_SCALE + MAP_SCALE / 2;
			ey = g->med_y[k] * MAP_SCALE + MAP_SCALE / 2;
			sx = cx + ((int)g->player.pos.x - ex) / 4;
			sy = cy + ((int)g->player.pos.y - ey) / 4;
			dy = -r;
			while (dy <= r)
			{
				dx = -r;
				while (dx <= r)
				{
					if (dx * dx + dy * dy <= rs
						&& is_in_minimap_circle(sx - cx + dx,
						sy - cy + dy, MINIMAP_RADIUS - 2))
						put_pixel(g, sx + dx, sy + dy, COLOR_GREEN);
					dx++;
				}
				dy++;
			}
		}
		k++;
	}
}

void			draw_minimap_items(t_game *g)
{
	draw_minimap_medkits(g);
} 