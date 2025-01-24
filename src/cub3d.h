/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/15 11:54:45 by rshaheen      #+#    #+#                 */
/*   Updated: 2025/01/24 16:11:50 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include <stdbool.h>

typedef struct s_map
{
	char	**map2d;
	// char	facing_to;
	int		pre_start_line_num;
	// int		p_x;
	// int		p_y;
	//int		map_weidth;
	int		height;
}	t_map;

typedef struct s_texture
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*ea;
	mlx_texture_t	*we;
	uint32_t		ceiling;
	uint32_t		floor;
}	t_texture;

typedef struct s_game_config
{
	//char	**mapa;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*floor_color;
	char		*ceiling_color;
	//int		start;
	t_texture	*valid_texture;
	t_map		*map;
}	t_game_config;

bool	check_file_extension(char *str);
void	init_config(t_game_config *data);
int		parse_file(char *file, t_game_config *data);
int		parse_color(t_game_config *data, char *color_line);
bool	parse_map_line(char *current_line, int line_num, t_game_config *data);
bool	parse_texture_n_color(t_game_config *data);
bool	validate_game_config(char *argv, t_game_config *data);
bool	validate_n_store_map2d(char *map_file, t_game_config *data);

void	error_msg(char *message);


#endif