/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/15 12:19:30 by rshaheen      #+#    #+#                 */
/*   Updated: 2025/01/15 12:38:53 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	argv = NULL;
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
}
