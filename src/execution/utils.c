/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kziari <kziari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:13:36 by kziari            #+#    #+#             */
/*   Updated: 2025/03/03 14:22:59 by kziari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

mlx_texture_t	*get_texture(t_game *game, int side)
{
	mlx_texture_t	*texture;

	texture = NULL;
	if (side == no)
		texture = game->texture->no;
	else if (side == so)
		texture = game->texture->so;
	else if (side == we)
		texture = game->texture->we;
	else if (side == ea)
		texture = game->texture->ea;
	return (texture);
}
