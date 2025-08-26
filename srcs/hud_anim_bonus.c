/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_anim_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 14:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/10 14:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_texture	*current_weapon_texture(t_game *g)
{
	double		t;

	t = now_seconds() - g->weapon_anim_started_at;
	if (g->weapon_anim_phase == 0)
		return (&g->weapon_tex);
	if (t < 0.05 && g->weapon1_tex.img)
		return (&g->weapon1_tex);
	if (t < 0.10 && g->weapon2_tex.img)
		return (&g->weapon2_tex);
	if (t < 0.15 && g->weapon1_tex.img)
		return (&g->weapon1_tex);
	g->weapon_anim_phase = 0;
	return (&g->weapon_tex);
}

void	update_weapon_anim(t_game *game)
{
	if (game->weapon_anim_phase != 0
		&& now_seconds() - game->weapon_anim_started_at > 0.15)
		game->weapon_anim_phase = 0;
} 