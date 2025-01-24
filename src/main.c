/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/15 12:19:30 by rshaheen      #+#    #+#                 */
/*   Updated: 2025/01/24 16:21:30 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <stdbool.h>

void	print_my_struct(t_game_config *data)
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
	for (int i = 0; i < data->map->height - 1; i++) 
    	printf("map2d[%d]: %s\n", i, data->map->map2d[i]);

}




int	main(int argc, char **argv)
{
	t_game_config	data;

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
	parse_file(argv[1], &data);
	//if (parse_file(argv[1], data) == false)
		//clean file and exit here
	parse_texture_n_color(&data);
	// if (parse_texture_n_color(&data) == false)
	// 	return (cleaner_file(&input), 1);
	validate_game_config(argv[1], &data);
	//if (validate_game_config(argv[1], &input) == false)
		//return (cleaner_file(&input), 1);
	print_my_struct(&data);
}

//TODO: add the if condition when parse_file is false
//TODO:add the if condition when parse_texture_n_color is false
//TODO: add the if codition when validate_game_config is false
//TODO: test printing color and texture