/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clean.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/27 16:33:22 by rshaheen      #+#    #+#                 */
/*   Updated: 2025/01/27 16:52:48 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	cleaner_game(t_game *game)
// {
// 	if (game->wall != NULL)
// 		free(game->wall);
// 	if (game->plyr != NULL)
// 		free(game->plyr);
// 	if (game->ray != NULL)
// 		free(game->ray);
// 	if (game != NULL)
// 		free(game);
// }

void	clean_texture(t_texture *texture)
{
	if (texture->no != NULL)
		mlx_delete_texture(texture->no);
	if (texture->so != NULL)
		mlx_delete_texture(texture->so);
	if (texture->we != NULL)
		mlx_delete_texture(texture->we);
	if (texture->ea != NULL)
		mlx_delete_texture(texture->ea);
	if (texture != NULL)
		free(texture);
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	clean_map(t_game *game)
{
	if (game->map->map2d)
		free_array(game->map->map2d);
	if (game->map != NULL)
		free(game->map);
}

void	clean_all(t_game *game)
{
	if (game->no != NULL)
		free(game->no);
	if (game->so != NULL)
		free(game->so);
	if (game->ea != NULL)
		free(game->ea);
	if (game->we != NULL)
		free(game->we);
	if (game->floor_color != NULL)
		free(game->floor_color);
	if (game->ceiling_color != NULL)
		free(game->ceiling_color);
	// if (game->mapa != NULL)
	// 	free_split(game->mapa);
	if (game->valid_texture)
		clean_texture(game->valid_texture);
	if (game->map)
		clean_map(game);
}
