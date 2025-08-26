/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pitch_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 12:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/11 12:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	clamp_pitch(t_game *g)
{
	if (g->pitch < PITCH_MIN)
		g->pitch = PITCH_MIN;
	if (g->pitch > PITCH_MAX)
		g->pitch = PITCH_MAX;
}

void		process_pitch(t_game *game)
{
	if (game->keys.up)
		game->pitch -= PITCH_STEP;
	if (game->keys.down)
		game->pitch += PITCH_STEP;
	clamp_pitch(game);
} 