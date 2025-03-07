/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 15:06:52 by rshaheen      #+#    #+#                 */
/*   Updated: 2025/03/07 13:03:16 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_config(t_game *game)
{
	game->ea = NULL;
	game->we = NULL;
	game->no = NULL;
	game->so = NULL;
	game->ceiling_color = NULL;
	game->floor_color = NULL;
	game->texture = NULL;
	game->map = NULL;
}
