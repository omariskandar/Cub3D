/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 22:10:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/08 22:10:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static double	compute_wall_x(t_game *g, t_ray *r)
{
	double		w;

	if (r->side == 0)
		w = g->player.pos.y / MAP_SCALE + r->perp_wall_dist * r->dir.y;
	else
		w = g->player.pos.x / MAP_SCALE + r->perp_wall_dist * r->dir.x;
	return (w - floor(w));
}

static void	floor_wall_point(t_ray *r, double wall_x, double *fx, double *fy)
{
	if (r->side == 0 && r->dir.x > 0)
	{
		*fx = r->map.x;
		*fy = r->map.y + wall_x;
	}
	else if (r->side == 0 && r->dir.x < 0)
	{
		*fx = r->map.x + 1.0;
		*fy = r->map.y + wall_x;
	}
	else if (r->side == 1 && r->dir.y > 0)
	{
		*fx = r->map.x + wall_x;
		*fy = r->map.y;
	}
	else
	{
		*fx = r->map.x + wall_x;
		*fy = r->map.y + 1.0;
	}
}

static int	floor_tex_color(t_game *g, double cx, double cy)
{
	int			tx;
	int			ty;
	int			color;
	int			w;
	int			h;

	if (!g->floor_tex.img)
		return (g->map.floor_color);
	w = g->floor_tex.width;
	h = g->floor_tex.height;
	tx = ((int)(cx * w)) % w;
	ty = ((int)(cy * h)) % h;
	if (tx < 0)
		tx = 0;
	if (ty < 0)
		ty = 0;
	color = get_texture_color(&g->floor_tex, tx, ty);
	return (color);
}

static void	corpse_half_extents(t_game *g, double *hw, double *hl)
{
	double	len;
	double	r;

	len = 0.8;
	r = 0.5;
	if (g->enemy_dead_tex.img && g->enemy_dead_tex.height > 0)
		r = (double)g->enemy_dead_tex.width
			/ (double)g->enemy_dead_tex.height;
	*hl = len * 0.5;
	*hw = (len * r) * 0.5;
}

static int	is_dead_here(t_game *g, double wx, double wy)
{
	int		k;
	double		dx;
	double		dy;
	double		hw;
	double		hl;

	k = 0;
	while (k < g->spr_count)
	{
		if (g->spr_alive && !g->spr_alive[k])
		{
			corpse_half_extents(g, &hw, &hl);
			dx = wx - ((double)g->spr_x[k] + 0.5);
			dy = wy - ((double)g->spr_y[k] + 0.5);
			if (fabs(dx) <= hw && fabs(dy) <= hl)
				return (1);
		}
		k++;
	}
	return (0);
}

static int	corpse_sample_color(t_game *g, double wx, double wy)
{
	int		k;
	double		dx;
	double		dy;
	double		hw;
	double		hl;
	double		u;
	double		v;
	int			tx;
	int			ty;
	int			key;

	if (!g->enemy_dead_tex.img)
		return (-1);
	k = 0;
	while (k < g->spr_count)
	{
		if (g->spr_alive && !g->spr_alive[k])
		{
			corpse_half_extents(g, &hw, &hl);
			dx = wx - ((double)g->spr_x[k] + 0.5);
			dy = wy - ((double)g->spr_y[k] + 0.5);
			if (fabs(dx) <= hw && fabs(dy) <= hl)
			{
				u = (dx + hw) / (2.0 * hw);
				v = (dy + hl) / (2.0 * hl);
				if (u < 0.0)
					u = 0.0;
				if (u > 1.0)
					u = 1.0;
				if (v < 0.0)
					v = 0.0;
				if (v > 1.0)
					v = 1.0;
				tx = (int)(u * g->enemy_dead_tex.width);
				ty = (int)((1.0 - v) * g->enemy_dead_tex.height);
				key = get_texture_color(&g->enemy_dead_tex, 0, 0);
				if (tx < 0)
					tx = 0;
				if (ty < 0)
					ty = 0;
				if (tx >= g->enemy_dead_tex.width)
					tx = g->enemy_dead_tex.width - 1;
				if (ty >= g->enemy_dead_tex.height)
					ty = g->enemy_dead_tex.height - 1;
				if (get_texture_color(&g->enemy_dead_tex, tx, ty) != key)
					return (get_texture_color(&g->enemy_dead_tex, tx, ty));
			}
		}
		k++;
	}
	return (-1);
}

int			corpse_overlay_color(t_game *g, double wx, double wy, int base)
{
	int		cc;

	if (!g->spr_alive || g->spr_count <= 0)
		return (base);
	if (!is_dead_here(g, wx, wy))
		return (base);
	cc = corpse_sample_color(g, wx, wy);
	if (cc == -1)
		return (base);
	return (cc);
}

int			sample_floor_color_at(t_game *g, t_ray *r, int y)
{
	double		den;
	double		w;
	double		fx;
	double		fy;
	int			base;

	den = (double)(2 * (y - g->pitch) - g->mlx.current_height);
	if (den == 0.0)
		den = 1e-6;
	if (r->perp_wall_dist < 1e-6)
		w = 1.0;
	else
		w = ((double)g->mlx.current_height / den) / r->perp_wall_dist;
	floor_wall_point(r, compute_wall_x(g, r), &fx, &fy);
	fx = w * fx + (1.0 - w) * (g->player.pos.x / MAP_SCALE);
	fy = w * fy + (1.0 - w) * (g->player.pos.y / MAP_SCALE);
	base = floor_tex_color(g, fx, fy);
	base = corpse_overlay_color(g, fx, fy, base);
	base = medkit_overlay_color(g, fx, fy, base);
	base = ammo_overlay_color(g, fx, fy, base);
	return (base);
}

void			draw_floor_tex_pixel(t_game *g, t_ray *r, int x, int y)
{
	int			color;

	color = sample_floor_color_at(g, r, y);
	put_pixel(g, x, y, color);
}
