/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ammo_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:45:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/12 14:45:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	count_ammo(t_game *g)
{
	int	c;
	int	i;
	int	j;

	c = 0;
	i = 0;
	while (g->map.grid[i])
	{
		j = 0;
		while (g->map.grid[i][j])
		{
			if (g->map.grid[i][j] == 'A')
				c++;
			j++;
		}
		i++;
	}
	return (c);
}

int			init_ammo_pickups(t_game *g)
{
	int	k;
	int	i;
	int	j;

	g->ammo_count = count_ammo(g);
	if (g->ammo_count <= 0)
		return (0);
	g->ammo_x = malloc(sizeof(int) * g->ammo_count);
	g->ammo_y = malloc(sizeof(int) * g->ammo_count);
	g->ammo_alive = malloc(sizeof(int) * g->ammo_count);
	if (!g->ammo_x || !g->ammo_y || !g->ammo_alive)
		return (1);
	k = 0;
	i = 0;
	while (g->map.grid[i])
	{
		j = 0;
		while (g->map.grid[i][j])
		{
			if (g->map.grid[i][j] == 'A')
			{
				g->ammo_x[k] = j;
				g->ammo_y[k] = i;
				g->ammo_alive[k] = 1;
				k++;
			}
			j++;
		}
		i++;
	}
	return (0);
}

void			free_ammo_pickups(t_game *g)
{
	if (g->ammo_x)
		free(g->ammo_x);
	if (g->ammo_y)
		free(g->ammo_y);
	if (g->ammo_alive)
		free(g->ammo_alive);
	g->ammo_x = NULL;
	g->ammo_y = NULL;
	g->ammo_alive = NULL;
	g->ammo_count = 0;
}

void			update_ammo_pickups(t_game *g)
{
	int		k;
	double	px;
	double	py;
	double	dx;
	double	dy;
	double	d;

	if (g->ammo_count <= 0 || !g->ammo_alive)
		return ;
	px = g->player.pos.x / MAP_SCALE;
	py = g->player.pos.y / MAP_SCALE;
	k = 0;
	while (k < g->ammo_count)
	{
		if (g->ammo_alive[k])
		{
			dx = (double)g->ammo_x[k] + 0.5 - px;
			dy = (double)g->ammo_y[k] + 0.5 - py;
			d = sqrt(dx * dx + dy * dy);
			if (d < 0.6)
			{
				g->ammo_alive[k] = 0;
				g->ammo += 10;
			}
		}
		k++;
	}
}

static int	inside_ammo_cell(t_game *g, double wx, double wy, int k,
				double *u, double *v)
{
	double	hw;
	double	hl;
	double	dx;
	double	dy;

	hw = 0.25;
	hl = 0.25;
	dx = wx - ((double)g->ammo_x[k] + 0.5);
	dy = wy - ((double)g->ammo_y[k] + 0.5);
	if (fabs(dx) > hw || fabs(dy) > hl)
		return (0);
	*u = (dx + hw) / (2.0 * hw);
	*v = (dy + hl) / (2.0 * hl);
	return (1);
}

int			ammo_overlay_color(t_game *g, double wx, double wy, int base)
{
	int		k;
	double	u;
	double	v;
	int		tx;
	int		ty;
	int		key;

	if (!g->ammo_tex.img || g->ammo_count <= 0 || !g->ammo_alive)
		return (base);
	k = 0;
	while (k < g->ammo_count)
	{
		if (g->ammo_alive[k]
			&& inside_ammo_cell(g, wx, wy, k, &u, &v))
		{
			key = get_texture_color(&g->ammo_tex, 0, 0);
			tx = (int)(u * g->ammo_tex.width);
			ty = (int)((1.0 - v) * g->ammo_tex.height);
			if (tx < 0)
				tx = 0;
			if (ty < 0)
				ty = 0;
			if (tx >= g->ammo_tex.width)
				tx = g->ammo_tex.width - 1;
			if (ty >= g->ammo_tex.height)
				ty = g->ammo_tex.height - 1;
			if (get_texture_color(&g->ammo_tex, tx, ty) != key)
				return (get_texture_color(&g->ammo_tex, tx, ty));
		}
		k++;
	}
	return (base);
} 