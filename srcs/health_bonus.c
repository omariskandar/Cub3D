/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 12:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/12 12:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_health(t_game *g)
{
	g->max_health = 100;
	g->health = 100;
	g->last_hit_ts = -10.0;
	g->invuln_secs = 0.6;
	g->is_dead = 0;
}

static int	is_invulnerable(t_game *g)
{
	double	dt;

	dt = now_seconds() - g->last_hit_ts;
	if (dt < g->invuln_secs)
		return (1);
	return (0);
}

void	apply_damage(t_game *g, int amount)
{
	if (amount <= 0 || g->is_dead)
		return ;
	if (is_invulnerable(g))
		return ;
	g->health -= amount;
	if (g->health < 0)
		g->health = 0;
	g->last_hit_ts = now_seconds();
	if (g->health == 0)
		g->is_dead = 1;
}

void	heal_player(t_game *g, int amount)
{
	if (amount <= 0)
		return ;
	g->health += amount;
	if (g->health > g->max_health)
		g->health = g->max_health;
}

static void	draw_texture_scaled(t_game *g, t_texture *t,
			int dx, int dy, int tw, int th)
{
	int	x;
	int	y;
	int	sx;
	int	sy;
	int	c;
	int	key;

	if (!t->img || tw <= 0 || th <= 0)
		return ;
	key = get_texture_color(t, 0, 0);
	y = 0;
	while (y < th)
	{
		sy = (y * t->height) / th;
		x = 0;
		while (x < tw)
		{
			sx = (x * t->width) / tw;
			c = get_texture_color(t, sx, sy);
			if (c != key)
				put_pixel(g, dx + x, dy + y, c);
			x++;
		}
		y++;
	}
}

static void	draw_bar_fill_scaled(t_game *g, int x, int y,
			int fw, int fh)
{
	int	xi;
	int	yi;
	int	sx;
	int	sy;
	int	c;
	int	key;

	if (!g->hp_bar_fill.img || fw <= 0 || fh <= 0)
		return ;
	key = get_texture_color(&g->hp_bar_fill, 0, 0);
	yi = 0;
	while (yi < fh)
	{
		sy = (yi * g->hp_bar_fill.height) / fh;
		xi = 0;
		while (xi < fw)
		{
			sx = (xi * g->hp_bar_fill.width) / fw;
			c = get_texture_color(&g->hp_bar_fill, sx, sy);
			if (c != key)
				put_pixel(g, x + xi, y + yi, c);
			xi++;
		}
		yi++;
	}
}

void	draw_health_hud(t_game *g)
{
	int	margin;
	int	bg_w;
	int	bg_h;
	int	bar_x;
	int	bar_y;
	int	fill_w;
	int	icon_w;
	int	icon_h;
	int	icon_x;
	int	icon_y;

	margin = 2;
	bg_w = g->hp_bar_bg.width / 2;
	bg_h = g->hp_bar_bg.height / 2;
	icon_w = g->hp_icon.width / 10;
	if (icon_w < 1)
		icon_w = 1;
	icon_h = g->hp_icon.height / 10;
	if (icon_h < 1)
		icon_h = 1;
	icon_x = margin;
	bar_x = icon_x + icon_w + 4;
	bar_y = g->mlx.current_height - bg_h - margin;
	icon_y = bar_y + (bg_h - icon_h) / 2;
	draw_texture_scaled(g, &g->hp_bar_bg, bar_x, bar_y, bg_w, bg_h);
	fill_w = 0;
	if (g->max_health > 0)
		fill_w = (g->health * bg_w) / g->max_health;
	draw_bar_fill_scaled(g, bar_x, bar_y, fill_w, bg_h);
	draw_texture_scaled(g, &g->hp_icon, icon_x, icon_y, icon_w, icon_h);
}

static int	get_screen_pixel(t_game *g, int x, int y)
{
	char	*ptr;

	ptr = g->mlx.img_addr + (y * g->mlx.line_length + x
			* (g->mlx.bits_per_pixel / 8));
	return (*(unsigned int *)ptr);
}

static int	blend_color(int dst, int src, double a)
{
	int	dr;
	int	dg;
	int	db;
	int	sr;
	int	sg;
	int	sb;
	int	r;
	int	g2;
	int	b;

	dr = (dst >> 16) & 0xFF;
	dg = (dst >> 8) & 0xFF;
	db = dst & 0xFF;
	sr = (src >> 16) & 0xFF;
	sg = (src >> 8) & 0xFF;
	sb = src & 0xFF;
	r = (int)(dr * (1.0 - a) + sr * a);
	g2 = (int)(dg * (1.0 - a) + sg * a);
	b = (int)(db * (1.0 - a) + sb * a);
	return ((r << 16) | (g2 << 8) | b);
}

void	draw_death_overlay(t_game *g)
{
	int	x;
	int	y;
	int	base;
	int	final;

	if (!g->is_dead)
		return ;
	y = 0;
	while (y < g->mlx.current_height)
	{
		x = 0;
		while (x < g->mlx.current_width)
		{
			base = get_screen_pixel(g, x, y);
			final = blend_color(base, COLOR_RED, 0.5);
			put_pixel(g, x, y, final);
			x++;
		}
		y++;
	}
}

static void	draw_texture_scaled_key(t_game *g, t_texture *t,
			int dx, int dy, int tw, int th)
{
	int	x;
	int	y;
	int	sx;
	int	sy;
	int	c;
	int	key;

	if (!t->img || tw <= 0 || th <= 0)
		return ;
	key = get_texture_color(t, 0, 0);
	y = 0;
	while (y < th)
	{
		sy = (y * t->height) / th;
		x = 0;
		while (x < tw)
		{
			sx = (x * t->width) / tw;
			c = get_texture_color(t, sx, sy);
			if (c != key)
				put_pixel(g, dx + x, dy + y, c);
			x++;
		}
		y++;
	}
}

void	draw_death_image(t_game *g)
{
	int	img_w;
	int	img_h;
	int	x;
	int	y;

	if (!g->is_dead || !g->game_over_tex.img)
		return ;
	img_w = g->mlx.current_width / 2;
	img_h = (g->game_over_tex.height * img_w) / g->game_over_tex.width;
	x = (g->mlx.current_width - img_w) / 2;
	y = (g->mlx.current_height - img_h) / 2 - 20;
	draw_texture_scaled_key(g, &g->game_over_tex, x, y, img_w, img_h);
}

void	draw_death_message(t_game *g)
{
	int	text_x;
	int	text_y;
	char	*msg;
	int	len;

	if (!g->is_dead)
		return ;
	msg = "GAME OVER! Press Space to restart";
	len = ft_strlen(msg);
	text_x = g->mlx.current_width / 2 - len * 4;
	text_y = g->mlx.current_height - 40;
	mlx_string_put(g->mlx.mlx_ptr, g->mlx.win_ptr, text_x, text_y,
		0xFFFFFF, msg);
}

void	restart_game(t_game *g)
{
	g->health = g->max_health;
	g->is_dead = 0;
	g->last_hit_ts = -10.0;
}

void	handle_death_and_respawn(t_game *g)
{
	if (!g->is_dead)
		return ;
	g->keys.w = 0;
	g->keys.a = 0;
	g->keys.s = 0;
	g->keys.d = 0;
	g->keys.left = 0;
	g->keys.right = 0;
	g->keys.shift = 0;
	g->keys.up = 0;
	g->keys.down = 0;
} 