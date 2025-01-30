/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/15 12:19:30 by rshaheen      #+#    #+#                 */
/*   Updated: 2025/01/29 12:23:41 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <stdbool.h>

void	print_my_struct(t_game *data)
{
	printf("ceiling_color: %s\n", data->ceiling_color);
	printf("floor_color: %s\n", data->floor_color);
	printf("east texture: %s\n", data->ea);
	printf("north texture: %s\n", data->no);
	printf("south texture: %s\n", data->so);
	printf("west texture: %s\n", data->we);
	printf("pre_start_line_num: %d\n", data->map->pre_start_line_num);
	printf("map_height: %d\n", data->map->height);
	printf("Floor color as decimal: %u\n", data->valid_texture->floor);
	printf("Floor color as hexadecimal: %#X\n", data->valid_texture->floor);
	printf("Ceiling color as decimal: %u\n", data->valid_texture->ceiling);
	printf("Ceiling color as hexadecimal: %#X\n", data->valid_texture->ceiling);
	printf("map width: %d\n", data->map->width);
}

void	print_my_map(t_map *map)
{
	for (int i = 0; i < map->height; i++)
		printf("map2d[%d]: %s\n", i, map->map2d[i]);
	printf("map_height: %d\n", map->height);
	printf("width: %d\n", map->width);
	printf("player's x: %d\n", map->player_x);
	printf("player's y: %d\n", map->player_y);
	printf("player's direction: %c\n", map->player_facing_to);
}

int	map_validation(int argc, char **argv, t_game	*data)
{
	if (argc < 2)
	{
		printf("Please input one gaming map\n");
		return (1);
	}
	if (argc > 2)
	{
		printf("Please input one file at a time\n");
		return (1);
	}
	if (check_file_extension(argv[1]) == false)
		return (1);
	init_config(&data);
	if (parse_file(argv[1], &data) == -1)
		return (error_msg("returned from parse_file\n"), 1);
	if (parse_texture_n_color(&data) == false)
		return (error_msg("parse texture false\n"), clean_all(&data), 1);
	print_my_struct(&data);
	if (validate_game_config(argv[1], &data) == false)
		return (clean_all(&data), 1);
	print_my_map(data->map);
}

// int	main(int argc, char **argv)
// {
// 	t_game	data;

// 	if (argc < 2)
// 	{
// 		printf("Please input one gaming map\n");
// 		return (1);
// 	}
// 	if (argc > 2)
// 	{
// 		printf("Please input one file at a time\n");
// 		return (1);
// 	}
// 	if (check_file_extension(argv[1]) == false)
// 		return (1);
// 	init_config(&data);
// 	if (parse_file(argv[1], &data) == -1)
// 		return (error_msg("returned from parse_file\n"), 1);
// 	if (parse_texture_n_color(&data) == false)
// 		return (error_msg("parse texture false\n"), clean_all(&data), 1);
// 	print_my_struct(&data);
// 	if (validate_game_config(argv[1], &data) == false)
// 		return (clean_all(&data), 1);
// 	print_my_map(data.map);
// }

int	main(int argc, char **argv)
{
	t_game	data;

	map_validation(argc, argv, &data);
	execution(data);
	return (0);
}