/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/15 11:54:45 by rshaheen      #+#    #+#                 */
/*   Updated: 2025/01/20 15:06:02 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include <stdbool.h>

typedef struct s_game_config
{
	//char	**mapa;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*floor_color;
	char	*ceiling_color;
	int		start;
	//t_tex	*valid_tex;
	//t_map	*map;
}	t_game_config;

bool	check_file_extension(char *str);

void	error_msg(char *message);


#endif