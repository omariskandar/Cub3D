/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_bonus.c                                     :+:      :+:      :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:20:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/11 12:20:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	count_terrorists(t_game *g)
{
	int		count;
	int		i;
	int		j;

	count = 0;
	i = 0;
	while (g->map.grid[i])
	{
		j = 0;
		while (g->map.grid[i][j])
		{
			if (g->map.grid[i][j] == 'T')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

static void	fill_terrorists(t_game *g)
{
	int		k;
	int		i;
	int		j;

	k = 0;
	i = 0;
	while (g->map.grid[i])
	{
		j = 0;
		while (g->map.grid[i][j])
		{
			if (g->map.grid[i][j] == 'T')
			{
				g->spr_x[k] = j;
				g->spr_y[k] = i;
				k++;
			}
			j++;
		}
		i++;
	}
}

int			init_sprites(t_game *g)
{
	int			i;

	g->spr_count = count_terrorists(g);
	if (g->spr_count <= 0)
		return (0);
	g->spr_x = malloc(sizeof(int) * g->spr_count);
	g->spr_y = malloc(sizeof(int) * g->spr_count);
	g->spr_spotted = malloc(sizeof(int) * g->spr_count);
	g->spr_last_seen = malloc(sizeof(double) * g->spr_count);
	g->spr_next_shot = malloc(sizeof(double) * g->spr_count);
	g->spr_shoot_until = malloc(sizeof(double) * g->spr_count);
	g->spr_health = malloc(sizeof(int) * g->spr_count);
	g->spr_alive = malloc(sizeof(int) * g->spr_count);
	if (!g->spr_x || !g->spr_y || !g->spr_spotted
		|| !g->spr_last_seen || !g->spr_next_shot || !g->spr_shoot_until
		|| !g->spr_health || !g->spr_alive)
		return (1);
	fill_terrorists(g);
	i = 0;
	while (i < g->spr_count)
	{
		g->spr_spotted[i] = 0;
		g->spr_last_seen[i] = 0.0;
		g->spr_next_shot[i] = 1e9;
		g->spr_shoot_until[i] = 0.0;
		g->spr_health[i] = 100;
		g->spr_alive[i] = 1;
		i++;
	}
	return (0);
}

static int	is_blocking_cell(t_game *g, int mx, int my)
{
	char	c;

	if (my < 0 || my >= g->map.height)
		return (1);
	if (mx < 0 || mx >= (int)ft_strlen(g->map.grid[my]))
		return (1);
	c = g->map.grid[my][mx];
	if (c == '1' || c == 'D')
		return (1);
	return (0);
}

static int	los_clear(t_game *g, double sx, double sy)
{
	double	px;
	double	py;
	double	dx;
	double	dy;
	double	steps;
	double	i;

	px = g->player.pos.x / MAP_SCALE;
	py = g->player.pos.y / MAP_SCALE;
	dx = sx - px;
	dy = sy - py;
	steps = fabs(dx);
	if (fabs(dy) > steps)
		steps = fabs(dy);
	if (steps < 1.0)
		steps = 1.0;
	dx /= steps;
	dy /= steps;
	i = 0.0;
	while (i < steps)
	{
		px += dx;
		py += dy;
		if (is_blocking_cell(g, (int)px, (int)py))
			return (0);
		i += 1.0;
	}
	return (1);
}

static int	player_visible(t_game *g, double spr_x, double spr_y)
{
	double	dx;
	double	dy;
	double	dist;
	double	dot;
	double	len;

	dx = spr_x - g->player.pos.x / MAP_SCALE;
	dy = spr_y - g->player.pos.y / MAP_SCALE;
	dist = sqrt(dx * dx + dy * dy);
	if (dist > 12.0)
		return (0);
	len = sqrt(dx * dx + dy * dy);
	if (len < 1e-6)
		return (1);
	dx /= len;
	dy /= len;
	dot = g->player.dir.x * dx + g->player.dir.y * dy;
	/* FOV ~ 60 deg total -> cos(30deg) ~ 0.866 */
	if (dot < 0.866)
		return (0);
	if (!los_clear(g, spr_x, spr_y))
		return (0);
	return (1);
}

static int	project_sprite(t_game *g, int idx, int *screen_x,
			int *size, int *bottom_y, double *trans_y)
{
	double		rel_x;
	double		rel_y;
	double		inv_det;
	double		trans_x;
	int			center_y;
	int			size_wall;
	double		scale;

	rel_x = (double)g->spr_x[idx] - g->player.pos.x / MAP_SCALE + 0.5;
	rel_y = (double)g->spr_y[idx] - g->player.pos.y / MAP_SCALE + 0.5;
	inv_det = 1.0 / (g->player.plane.x * g->player.dir.y
		- g->player.dir.x * g->player.plane.y);
	trans_x = inv_det * (g->player.dir.y * rel_x - g->player.dir.x * rel_y);
	*trans_y = inv_det * (-g->player.plane.y * rel_x
		+ g->player.plane.x * rel_y);
	if (*trans_y <= 0)
		return (0);
	*screen_x = (int)((g->mlx.current_width / 2) * (1 + trans_x / *trans_y));
	center_y = g->mlx.current_height / 2 + g->pitch;
	size_wall = (int)(g->mlx.current_height / *trans_y);
	scale = g->spr_alive[idx] ? 0.85 : 0.35;
	*size = (int)(size_wall * scale);
	*bottom_y = center_y + size_wall / 2;
	return (1);
}

void			update_enemies(t_game *g)
{
	int			k;
	double		now;
	double		sx;
	double		sy;
	int			vis;

	if (g->spr_count <= 0)
		return ;
	now = now_seconds();
	k = 0;
	while (k < g->spr_count)
	{
		if (!g->spr_alive[k])
		{
			g->spr_spotted[k] = 0;
			g->spr_shoot_until[k] = 0.0;
			k++;
			continue ;
		}
		sx = (double)g->spr_x[k];
		sy = (double)g->spr_y[k];
		vis = player_visible(g, sx, sy);
		if (vis)
		{
			if (!g->spr_spotted[k])
			{
				g->spr_spotted[k] = 1;
				g->spr_next_shot[k] = now + 2.0;
			}
			if (now >= g->spr_next_shot[k])
			{
				apply_damage(g, 20);
				g->spr_shoot_until[k] = now + 0.2;
				g->spr_next_shot[k] = now + 2.0;
			}
		}
		else
		{
			g->spr_spotted[k] = 0;
			g->spr_shoot_until[k] = 0.0;
		}
		k++;
	}
}

t_texture		*enemy_texture_for(t_game *g, int i)
{
	double	now;

	now = now_seconds();
	if (g->spr_alive && !g->spr_alive[i])
		return (&g->enemy_dead_tex);
	if (g->spr_shoot_until && now < g->spr_shoot_until[i])
		return (&g->enemy_shoot_tex);
	return (&g->enemy_tex);
}

static void	draw_sprite_column(t_game *g, int start_x, int size,
				int bottom_y, int stripe, int idx)
{
	int			y;
	int			draw_start_y;
	int			draw_end_y;
	int			tex_x;
	int			tex_y;
	int			color;
	t_texture	*cur;

	if (size < 1)
		return ;
	cur = enemy_texture_for(g, idx);
	draw_end_y = bottom_y;
	draw_start_y = draw_end_y - size;
	tex_x = (int)((double)(stripe - start_x) * cur->width / size);
	y = draw_start_y;
	while (y < draw_end_y)
	{
		tex_y = (int)(((double)(y - draw_start_y) * cur->height)
			/ (draw_end_y - draw_start_y));
		color = get_texture_color(cur, tex_x, tex_y);
		if (color != get_texture_color(&g->enemy_tex, 0, 0))
			put_pixel(g, stripe, y, color);
		y++;
	}
}

static void	render_single_sprite(t_game *g, double spr_x, double spr_y, int idx)
{
	double		rel_x;
	double		rel_y;
	double		inv_det;
	double		trans_x;
	double		trans_y;
	int			screen_x;
	int			draw_start_x;
	int			draw_end_x;
	int			stripe;
	int			size;
	int			bottom_y;
	int			size_wall;
	double		scale;
	int			center_y;

	rel_x = spr_x - g->player.pos.x / MAP_SCALE + 0.5;
	rel_y = spr_y - g->player.pos.y / MAP_SCALE + 0.5;
	inv_det = 1.0 / (g->player.plane.x * g->player.dir.y
		- g->player.dir.x * g->player.plane.y);
	trans_x = inv_det * (g->player.dir.y * rel_x - g->player.dir.x * rel_y);
	trans_y = inv_det * (-g->player.plane.y * rel_x
		+ g->player.plane.x * rel_y);
	if (trans_y <= 0)
		return ;
	screen_x = (int)((g->mlx.current_width / 2) * (1 + trans_x / trans_y));
	center_y = g->mlx.current_height / 2 + g->pitch;
	size_wall = (int)(g->mlx.current_height / trans_y);
	if (!g->spr_alive[idx])
	{
		return ;
	}
	scale = 0.85;
	size = (int)(size_wall * scale);
	bottom_y = center_y + size_wall / 2;
	draw_start_x = screen_x - size / 2;
	draw_end_x = screen_x + size / 2;
	stripe = draw_start_x;
	while (stripe < draw_end_x)
	{
		if (stripe >= 0 && stripe < g->mlx.current_width
			&& (!g->zbuffer || trans_y < g->zbuffer[stripe]))
			draw_sprite_column(g, draw_start_x, size, bottom_y, stripe, idx);
		stripe++;
	}
}

void			render_sprites(t_game *g)
{
	int			k;

	if ((!g->enemy_tex.img && !g->enemy_dead_tex.img) || g->spr_count <= 0)
		return ;
	k = 0;
	while (k < g->spr_count)
	{
		render_single_sprite(g, (double)g->spr_x[k], (double)g->spr_y[k], k);
		k++;
	}
}

void			free_sprites(t_game *g)
{
	if (g->spr_x)
		free(g->spr_x);
	if (g->spr_y)
		free(g->spr_y);
	if (g->spr_spotted)
		free(g->spr_spotted);
	if (g->spr_last_seen)
		free(g->spr_last_seen);
	if (g->spr_next_shot)
		free(g->spr_next_shot);
	if (g->spr_shoot_until)
		free(g->spr_shoot_until);
	if (g->spr_health)
		free(g->spr_health);
	if (g->spr_alive)
		free(g->spr_alive);
	g->spr_x = NULL;
	g->spr_y = NULL;
	g->spr_spotted = NULL;
	g->spr_last_seen = NULL;
	g->spr_next_shot = NULL;
	g->spr_shoot_until = NULL;
	g->spr_health = NULL;
	g->spr_alive = NULL;
	g->spr_count = 0;
} 

void			attempt_player_shot(t_game *g)
{
	int		k;
	int		cx;
	int		screen_x;
	int		size;
	int		bottom_y;
	double		trans_y;

	cx = g->mlx.current_width / 2;
	k = 0;
	while (k < g->spr_count)
	{
		if (g->spr_alive[k]
			&& project_sprite(g, k, &screen_x, &size, &bottom_y, &trans_y))
		{
			int ds;
			int de;

			ds = screen_x - size / 2;
			de = screen_x + size / 2;
			if (cx >= ds && cx < de
				&& g->mlx.current_height / 2 >= (bottom_y - size)
				&& g->mlx.current_height / 2 < bottom_y)
			{
				if (!g->zbuffer || trans_y < g->zbuffer[cx])
				{
					if (player_visible(g, (double)g->spr_x[k], (double)g->spr_y[k]))
					{
						g->spr_health[k] -= 40;
						if (g->spr_health[k] <= 0)
						{
							g->spr_alive[k] = 0;
							g->spr_spotted[k] = 0;
							g->spr_shoot_until[k] = 0.0;
						}
					}
				}
			}
		}
		k++;
	}
} 