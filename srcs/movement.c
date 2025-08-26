/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 13:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/01 13:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	apply_forward_backward(t_game *game, double *move_x,
			double *move_y, double speed)
{
	if (game->keys.w)
	{
		*move_x += game->player.dir.x * speed;
		*move_y += game->player.dir.y * speed;
	}
	if (game->keys.s)
	{
		*move_x -= game->player.dir.x * speed;
		*move_y -= game->player.dir.y * speed;
	}
}

void	apply_left_right(t_game *game, double *move_x,
			double *move_y, double speed)
{
	if (game->keys.a)
	{
		*move_x += game->player.dir.y * speed;
		*move_y -= game->player.dir.x * speed;
	}
	if (game->keys.d)
	{
		*move_x -= game->player.dir.y * speed;
		*move_y += game->player.dir.x * speed;
	}
}

void	calculate_movement(t_game *game, double *move_x, double *move_y)
{
	double	current_speed;

	*move_x = 0;
	*move_y = 0;
	if (game->keys.shift)
		current_speed = 8.0;
	else
		current_speed = game->player.move_speed;
	apply_forward_backward(game, move_x, move_y, current_speed);
	apply_left_right(game, move_x, move_y, current_speed);
}

void	process_movement(t_game *game)
{
	double	new_x;
	double	new_y;
	double	move_x;
	double	move_y;

	new_x = game->player.pos.x;
	new_y = game->player.pos.y;
	calculate_movement(game, &move_x, &move_y);
	new_x += move_x;
	new_y += move_y;
	if (!check_collision(game, new_x, game->player.pos.y))
		game->player.pos.x = new_x;
	if (!check_collision(game, game->player.pos.x, new_y))
		game->player.pos.y = new_y;
}

void	process_rotation(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rotation_speed;

	if (game->keys.left)
		rotation_speed = -game->player.rot_speed;
	else if (game->keys.right)
		rotation_speed = game->player.rot_speed;
	else
		return ;
	old_dir_x = game->player.dir.x;
	game->player.dir.x = game->player.dir.x * cos(rotation_speed)
		- game->player.dir.y * sin(rotation_speed);
	game->player.dir.y = old_dir_x * sin(rotation_speed)
		+ game->player.dir.y * cos(rotation_speed);
	old_plane_x = game->player.plane.x;
	game->player.plane.x = game->player.plane.x * cos(rotation_speed)
		- game->player.plane.y * sin(rotation_speed);
	game->player.plane.y = old_plane_x * sin(rotation_speed)
		+ game->player.plane.y * cos(rotation_speed);
}
