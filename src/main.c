/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kziari <kziari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:19:30 by rshaheen          #+#    #+#             */
/*   Updated: 2025/02/27 15:43:32 by kziari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

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
	init_config(&game);
	if (parse_file(argv[1], &game) == -1)
		return (error_msg("returned from parse_file\n"), 1);
	if (parse_texture_n_color(&game) == false)
		return (error_msg("parse texture false\n"), clean_all(&game), 1);
	if (validate_game_config(argv[1], &game) == false)
		return (clean_all(&game), 1);
	execution(&game);
	clean_game(&game);
	clean_all(&game);
}
