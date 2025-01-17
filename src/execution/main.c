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

#include "cub3d.h"

int	main()
{
	t_data	*data = NULL;

	//initialize_map(data);
	execution(data);
	return (0);
}


/*
	Map Initialization and Window Creation
	loop (listening to hooks)
	ray cast
	render image(calculate high of wall)
	change view or position -> ray casting(calculate high of wall)
	close loop

*/