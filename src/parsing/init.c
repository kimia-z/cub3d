/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 15:06:52 by rshaheen      #+#    #+#                 */
/*   Updated: 2025/01/29 12:25:07 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_config(t_game *game)
{
	game->no = NULL;
	game->so = NULL;
	game->we = NULL;
	game->ea = NULL;
	game->floor_color = NULL;
	game->ceiling_color = NULL;
	game->valid_texture = NULL;
	game->map = NULL;
}
