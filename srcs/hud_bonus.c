/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/10 12:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	put_pixel_if_visible(t_game *g, int x, int y, int color)
{
	if (x >= 0 && x < g->mlx.current_width && y >= 0
		&& y < g->mlx.current_height)
		put_pixel(g, x, y, color);
}

static void	draw_weapon_row(t_game *g, int start_x, int start_y, int src_y)
{
	int		src_x;
	int		dst_x;
	int		color;
	int		key;

	key = get_texture_color(&g->weapon_tex, 0, 0);
	src_x = 0;
	while (src_x < g->weapon_tex.width)
	{
		dst_x = start_x + src_x;
		color = get_texture_color(&g->weapon_tex, src_x, src_y);
		if (color != key)
			put_pixel_if_visible(g, dst_x, start_y + src_y, color);
		src_x++;
	}
}

void	draw_weapon_hud(t_game *game)
{
	int		start_x;
	int		start_y;
	int		src_y;
	int		off;
	t_texture	saved;
	t_texture	*cur;

	if (!game->weapon_tex.img)
		return ;
	saved = game->weapon_tex;
	cur = &saved;
	if (game->weapon_anim_phase != 0)
		cur = current_weapon_texture(game);
	off = cur->width / 10;
	start_x = (game->mlx.current_width - cur->width) / 2 + off + 15;
	start_y = game->mlx.current_height - cur->height;
	src_y = 0;
	while (src_y < cur->height)
	{
		game->weapon_tex = *cur;
		draw_weapon_row(game, start_x, start_y, src_y);
		src_y++;
	}
	game->weapon_tex = saved;
}

static int	nearby_door_cell(t_game *g)
{
	int		mx;
	int		my;
	int		dx;
	int		dy;

	mx = (int)(g->player.pos.x / MAP_SCALE);
	my = (int)(g->player.pos.y / MAP_SCALE);
	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			if (my + dy >= 0 && my + dy < g->map.height && mx + dx >= 0
				&& mx + dx < (int)ft_strlen(g->map.grid[my + dy])
				&& g->map.grid[my + dy][mx + dx] == 'D')
				return (1);
			dx++;
		}
		dy++;
	}
	return (0);
}

void	draw_press_e_hint(t_game *game)
{
	int		x;
	int		y;

	if (!nearby_door_cell(game))
		return ;
	x = (game->mlx.current_width / 2) - 140;
	y = game->mlx.current_height - 40;
	mlx_string_put(game->mlx.mlx_ptr, game->mlx.win_ptr, x, y,
		COLOR_WHITE, "Press E to open the Door");
}

static void	itoa_dec(int n, char *buf, int sz)
{
	int		i;
	int		tmp;
	int		neg;

	if (sz <= 1)
		return ;
	neg = (n < 0);
	if (neg)
		n = -n;
	i = 0;
	if (n == 0)
		buf[i++] = '0';
	while (n > 0 && i < sz - 1)
	{
		buf[i++] = '0' + (n % 10);
		n /= 10;
	}
	if (neg && i < sz - 1)
		buf[i++] = '-';
	buf[i] = '\0';
	/* reverse in place */
	i--;
	tmp = 0;
	while (tmp < i)
	{
		char c = buf[tmp];
		buf[tmp] = buf[i];
		buf[i] = c;
		tmp++;
		i--;
	}
}

static void	draw_icon_key(t_game *g, t_texture *t, int dx, int dy,
			int tw, int th)
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

static void	draw_ammo_panel_bg(t_game *g, int x, int y, int w, int h)
{
	int	i;
	int	j;
	int	color;

	if (w <= 0 || h <= 0)
		return ;
	color = 0x202020;
	j = 0;
	while (j < h)
	{
		i = 0;
		while (i < w)
		{
			put_pixel_if_visible(g, x + i, y + j, color);
			i++;
		}
		j++;
	}
}

void			draw_ammo_icon_hud(t_game *g)
{
	int		icon_w;
	int		icon_h;
	int		x;
	int		y;
	int		panel_w;
	int		panel_h;
	int		panel_x;
	int		panel_y;

	if (!g->ammo_tex.img)
		return ;
	icon_w = 28;
	icon_h = 28;
	x = 12;
	y = 8;
	panel_w = icon_w + 6 + 60 + 12;
	panel_h = icon_h + 8;
	panel_x = x - 6;
	panel_y = y - 4;
	draw_ammo_panel_bg(g, panel_x, panel_y, panel_w, panel_h);
	draw_icon_key(g, &g->ammo_tex, x, y, icon_w, icon_h);
}

static void	draw_digit_strip(t_game *g, int digit, int dx, int dy,
			int tw, int th)
{
	int		tex_w;
	int		tex_h;
	int		cols;
	int		rows;
	int		cell_w;
	int		cell_h;
	int		col;
	int		row;
	int		margin_x;
	int		margin_y;
	int		x;
	int		y;
	int		sx;
	int		sy;
	int		c;
	int		key;

	if (!g->numbers_tex.img)
		return ;
	tex_w = g->numbers_tex.width;
	tex_h = g->numbers_tex.height;
	if (tex_w <= 0 || tex_h <= 0)
		return ;
	/* numbers sprite sheet is 2 rows x 5 columns: [1..5] on row 0, [6..9,0] on row 1 */
	cols = 5;
	rows = 2;
	cell_w = tex_w / cols;
	cell_h = tex_h / rows;
	if (cell_w <= 0 || cell_h <= 0)
		return ;
	if (digit < 0)
		digit = 0;
	if (digit > 9)
		digit = 9;
	if (digit == 0)
	{
		row = 1;
		col = 4;
	}
	else if (digit <= 5)
	{
		row = 0;
		col = digit - 1;
	}
	else
	{
		row = 1;
		col = digit - 6;
	}
	/* inner margins to avoid bleeding */
	margin_x = (cell_w >= 16) ? 1 : 0;
	margin_y = (cell_h >= 16) ? 1 : 0;
	key = get_texture_color(&g->numbers_tex, 0, 0);
	y = 0;
	while (y < th)
	{
		int src_y_span = cell_h - 2 * margin_y;
		if (src_y_span <= 0)
			src_y_span = cell_h;
		/* map to the selected cell's Y */
		sy = row * cell_h + margin_y + (y * src_y_span) / th;
		if (sy < 0)
			sy = 0;
		if (sy >= tex_h)
			sy = tex_h - 1;
		x = 0;
		while (x < tw)
		{
			int src_x_span = cell_w - 2 * margin_x;
			if (src_x_span <= 0)
				src_x_span = cell_w;
			/* map to the selected cell's X */
			sx = col * cell_w + margin_x + (x * src_x_span) / tw;
			if (sx < 0)
				sx = 0;
			if (sx >= tex_w)
				sx = tex_w - 1;
			c = get_texture_color(&g->numbers_tex, sx, sy);
			if (c != key)
				put_pixel(g, dx + x, dy + y, c);
			x++;
		}
		y++;
	}
}

static void	draw_number_strip(t_game *g, int value, int dx, int dy,
			int tw, int th)
{
	char	buf[16];
	int	len;
	int	i;
	int	x;

	ft_memset(buf, 0, sizeof(buf));
	itoa_dec(value, buf, (int)sizeof(buf));
	len = ft_strlen(buf);
	i = 0;
	x = dx;
	while (i < len)
	{
		if (buf[i] >= '0' && buf[i] <= '9')
			draw_digit_strip(g, buf[i] - '0', x, dy, tw, th);
		x += tw + 2;
		i++;
	}
}

void			draw_ammo_hud(t_game *g)
{
	char		num[16];
	int		x;
	int		y;
	int		dx;
	int		dy;

	if (!g->mlx.win_ptr)
		return ;
	ft_memset(num, 0, sizeof(num));
	itoa_dec(g->ammo, num, (int)sizeof(num));
	/* Top-left corner, to the right of the icon */
	x = 12 + 28 + 6;
	y = 10;
	if (g->numbers_tex.img && g->numbers_tex.width >= 10)
	{
		/* draw using sprite sheet digits */
		draw_number_strip(g, g->ammo, x, y, 18, 24);
		return ;
	}
	/* Outline to make it bigger and readable (drawn over dark panel) */
	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			if (dx != 0 || dy != 0)
				mlx_string_put(g->mlx.mlx_ptr, g->mlx.win_ptr,
				x + dx, y + dy + 6, 0x000000, num);
			dx++;
		}
		dy++;
	}
	/* Main white text on top */
	mlx_string_put(g->mlx.mlx_ptr, g->mlx.win_ptr, x, y + 6, 0xFFFFFF, num);
}
