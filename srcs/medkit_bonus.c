/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medkit_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:25:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/12 14:25:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	count_medkits(t_game *g)
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
			if (g->map.grid[i][j] == 'M')
				c++;
			j++;
		}
		i++;
	}
	return (c);
}

int			init_medkits(t_game *g)
{
	int	k;
	int	i;
	int	j;

	g->med_count = count_medkits(g);
	if (g->med_count <= 0)
		return (0);
	g->med_x = malloc(sizeof(int) * g->med_count);
	g->med_y = malloc(sizeof(int) * g->med_count);
	g->med_alive = malloc(sizeof(int) * g->med_count);
	if (!g->med_x || !g->med_y || !g->med_alive)
		return (1);
	k = 0;
	i = 0;
	while (g->map.grid[i])
	{
		j = 0;
		while (g->map.grid[i][j])
		{
			if (g->map.grid[i][j] == 'M')
			{
				g->med_x[k] = j;
				g->med_y[k] = i;
				g->med_alive[k] = 1;
				k++;
			}
			j++;
		}
		i++;
	}
	return (0);
}

void			free_medkits(t_game *g)
{
	if (g->med_x)
		free(g->med_x);
	if (g->med_y)
		free(g->med_y);
	if (g->med_alive)
		free(g->med_alive);
	g->med_x = NULL;
	g->med_y = NULL;
	g->med_alive = NULL;
	g->med_count = 0;
}

void			update_medkits(t_game *g)
{
	int		k;
	double	px;
	double	py;
	double	dx;
	double	dy;
	double	d;

	if (g->med_count <= 0 || !g->med_alive)
		return ;
	px = g->player.pos.x / MAP_SCALE;
	py = g->player.pos.y / MAP_SCALE;
	k = 0;
	while (k < g->med_count)
	{
		if (g->med_alive[k])
		{
			dx = (double)g->med_x[k] + 0.5 - px;
			dy = (double)g->med_y[k] + 0.5 - py;
			d = sqrt(dx * dx + dy * dy);
			if (d < 0.6)
			{
				g->med_alive[k] = 0;
				heal_player(g, 40);
			}
		}
		k++;
	}
}

static int	inside_medkit_cell(t_game *g, double wx, double wy, int k,
				double *u, double *v)
{
	double	hw;
	double	hl;
	double	dx;
	double	dy;

	hw = 0.25;
	hl = 0.25;
	dx = wx - ((double)g->med_x[k] + 0.5);
	dy = wy - ((double)g->med_y[k] + 0.5);
	if (fabs(dx) > hw || fabs(dy) > hl)
		return (0);
	*u = (dx + hw) / (2.0 * hw);
	*v = (dy + hl) / (2.0 * hl);
	return (1);
}

int			medkit_overlay_color(t_game *g, double wx, double wy, int base)
{
	int		k;
	double	u;
	double	v;
	int		tx;
	int		ty;
	int		key;

	if (!g->medkit_tex.img || g->med_count <= 0 || !g->med_alive)
		return (base);
	k = 0;
	while (k < g->med_count)
	{
		if (g->med_alive[k]
			&& inside_medkit_cell(g, wx, wy, k, &u, &v))
		{
			key = get_texture_color(&g->medkit_tex, 0, 0);
			tx = (int)(u * g->medkit_tex.width);
			ty = (int)((1.0 - v) * g->medkit_tex.height);
			if (tx < 0)
				tx = 0;
			if (ty < 0)
				ty = 0;
			if (tx >= g->medkit_tex.width)
				tx = g->medkit_tex.width - 1;
			if (ty >= g->medkit_tex.height)
				ty = g->medkit_tex.height - 1;
			if (get_texture_color(&g->medkit_tex, tx, ty) != key)
				return (get_texture_color(&g->medkit_tex, tx, ty));
		}
		k++;
	}
	return (base);
} 