/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/15 12:19:30 by rshaheen      #+#    #+#                 */
/*   Updated: 2025/01/20 19:08:27 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdio.h>
#include <stdbool.h>

void	print_my_struct(t_game_config *data)
{
	printf("ceiling_color: %s\n", data->ceiling_color);
	printf("floor_color: %s\n", data->floor_color);
	printf("east texture: %s\n", data->ea);
	printf("north texture: %s\n", data->no);
	printf("south texture: %s\n", data->so);
	printf("%s\n", data->we);
	printf("%s\n", data->start);
}



int	main(int argc, char **argv)
{

	t_game_config	*data;

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
	init_config(data);
	print_my_struct(data);
	parse_file(argv[1], data);
	print_my_struct(data);
	//if (parse_file(argv[1], data) == false)
		//clean file and exit here
}

