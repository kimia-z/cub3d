/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/15 11:54:45 by rshaheen      #+#    #+#                 */
/*   Updated: 2025/01/15 12:07:11 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../../libft/libft.h"
# include "./MLX42/MLX42.h"
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# define WIDTH 1000 //?
# define HEIGHT 1900 //?
# define RESIZE 5 //?
/*
	Delta distances represent the distance the ray
		has to travel to move one unit in the X or Y direction
*/


typedef struct	s_data
{
	float posX; // player position
	float posY; // player position
	float dirX; // Ray direction
	float dirY; // Ray direction
	//char **map;
	//t_mlx	*mlx;
	//player starting position(px,py)
	//ray direction(dirx,diry)
	//grid coordinates of the player(mapx,mapy)
}	t_data;

void	execution(t_data *data);

#endif