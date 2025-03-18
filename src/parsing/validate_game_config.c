/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_game_config.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 18:51:09 by rshaheen      #+#    #+#                 */
/*   Updated: 2025/03/18 16:29:19 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

//is_struct_full is checking if all variables in the t_game struct r set
//meaning (non-zero or non-NULL).

int	is_struct_full(t_game *game)
{
	if (game->ceiling_color == 0)
		return (error_msg("missing ceiling color\n"), false);
	if (game->floor_color == 0)
		return (error_msg("missing floor color\n"), false);
	if (game->ea == NULL)
		return (error_msg("missing east texture\n"), false);
	if (game->we == NULL)
		return (error_msg("missing west texture\n"), false);
	if (game->so == NULL)
		return (error_msg("missing south texture\n"), false);
	if (game->no == NULL)
		return (error_msg("missing north texture\n"), false);
	return (true);
}
//new allocation necessary for temp_map, otherwise it will be a pointer to the
//original one and changes in the copy will cause change in original

t_map	*copy_map(t_map *map)
{
	t_map	*temp_map;
	int		i;

	i = -1;
	temp_map = malloc(sizeof(t_map));
	if (!temp_map)
		return (error_msg("allocation for copy_map failed\n"), NULL);
	temp_map->height = map->height;
	temp_map->width = map->width;
	temp_map->player_x = map->player_x;
	temp_map->player_y = map->player_y;
	temp_map->player_facing_to = map->player_facing_to;
	temp_map->map2d = malloc(sizeof(char *) * (map->height + 1));
	if (!temp_map->map2d)
		return (free(temp_map), NULL);
	while (++i < map->height)
	{
		temp_map->map2d[i] = ft_strdup(map->map2d[i]);
		if (!temp_map->map2d[i])
		{
			free_array(temp_map->map2d);
			return (free(temp_map), NULL);
		}
	}
	return (temp_map->map2d[map->height] = NULL, temp_map);
}

//x and y are pointing to one cell
//x and y begins with player's position and keeps iterating later
//check if first row has 0, meaning broken wall
//check if last row has 0,meaning broken wall
//if row is  NULL or row's length == 0, return
//stop recursion if cell is '1' or '2'
//Mark the cell as visited with 2

int	flood_fill(t_map *map, int r, int y, int x)
{
	if (map->map2d[0] && ft_strchr(map->map2d[0], '0'))
		return (error_msg("broken wall at top"), EXIT_FAILURE);
	if (map->map2d[map->height - 1]
		&& ft_strchr(map->map2d[map->height - 1], '0'))
		return (error_msg("broken wall at bottom"), EXIT_FAILURE);
	if (!map->map2d[y] || ft_strlen(map->map2d[y]) == 0)
		return (error_msg("empty row encountered"), EXIT_FAILURE);
	if ((y >= map->height || y < 0)
		|| (x >= (int)ft_strlen(map->map2d[y]) || x < 0))
		return (error_msg("out of bounds or broken wall\n"), EXIT_FAILURE);
	if (map->map2d[y][x] && (map->map2d[y][x] == '1' \
		|| map->map2d[y][x] == '2' || map->map2d[y][x] == ' '))
		return (0);
	if (map->map2d[y][x] != '1' && map->map2d[y][x] != '2'
		&& map->map2d[y][x] != ' ' && map->map2d[y][x] != '0')
		return (error_msg("unexpected value encountered\n"), 1);
	map->map2d[y][x] = '2';
	if (flood_fill(map, r, y, x + 1) == EXIT_FAILURE
		|| flood_fill(map, r, y, x - 1) == EXIT_FAILURE
		|| flood_fill(map, r, y + 1, x) == EXIT_FAILURE
		|| flood_fill(map, r, y - 1, x) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (r);
}

bool	validate_game_config(char *map_file, t_game *game)
{
	t_map	*temp_map;

	if (is_struct_full(game) == false)
		return (error_msg("missing config info\n"), false);
	if (validate_n_store_map2d(map_file, game) == false)
		return (false);
	if (parse_player(game) == false)
		return (error_msg("invalid player\n"), false);
	temp_map = copy_map(game->map);
	temp_map->map2d[temp_map->player_y][temp_map->player_x] = '0';
	if (flood_fill(temp_map, 0, temp_map->player_y, temp_map->player_x))
	{
		free_array(temp_map->map2d);
		free(temp_map);
		return (false);
	}
	game->map->map2d[game->map->player_y][game->map->player_x] = '0';
	free_array(temp_map->map2d);
	free(temp_map);
	return (true);
}
