/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omar-iskandarani <omar-iskandarani@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:00:00 by omar-iskand       #+#    #+#             */
/*   Updated: 2025/08/01 15:00:00 by omar-iskand      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_file_exists(char *filepath)
{
	int	fd;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

static int	validate_single_texture(char *texture_path, char *texture_name)
{
	if (!texture_path)
		return (exit_error("Error: Missing texture path"));
	if (!check_file_exists(texture_path))
		return (exit_error("Error: Texture file does not exist"));
	(void)texture_name;
	return (0);
}

int	validate_textures(t_game *game)
{
	if (validate_single_texture(game->map.north_texture, "North") != 0)
		return (1);
	if (validate_single_texture(game->map.south_texture, "South") != 0)
		return (1);
	if (validate_single_texture(game->map.west_texture, "West") != 0)
		return (1);
	if (validate_single_texture(game->map.east_texture, "East") != 0)
		return (1);
	return (0);
}
