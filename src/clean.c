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

void	clean_map(t_game *data)
{
	if (data->map->map2d)
		free_array(data->map->map2d);
	if (data->map != NULL)
		free(data->map);
}

void	clean_all(t_game *data)
{
	if (data->no != NULL)
		free(data->no);
	if (data->so != NULL)
		free(data->so);
	if (data->ea != NULL)
		free(data->ea);
	if (data->we != NULL)
		free(data->we);
	if (data->floor_color != NULL)
		free(data->floor_color);
	if (data->ceiling_color != NULL)
		free(data->ceiling_color);
	// if (data->mapa != NULL)
	// 	free_split(data->mapa);
	if (data->valid_texture)
		clean_texture(data->valid_texture);
	if (data->map)
		clean_map(data);
}
