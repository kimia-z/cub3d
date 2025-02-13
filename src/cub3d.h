/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/15 11:54:45 by rshaheen      #+#    #+#                 */
/*   Updated: 2025/01/29 14:03:13 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include <stdbool.h>
# include <math.h>
# define WIDTH 800 //?
# define HEIGHT 600 //?
# define HITBOX 0.2
# define X 0
# define Y 1

typedef enum
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
}	move_t;

typedef enum
{
	TURN_LEFT,
	TURN_RIGHT
}	turn_t;

typedef	struct s_player
{
	double	x; // Player X position in the map
	double	y; // Player Y position in the map
	double	dir_x; // X direction vector
	double	dir_y; // Y direction vector
	double	plane_x; // X component of the camera plane (FOV)
	double	plane_y; // Y component of the camera plane (FOV)
}	t_player;

typedef	struct s_ray
{
	double	pos_x;
	double	pos_y;
	int		map_x;
	int		map_y;
	double	step_x;
	double	step_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	wall_x;
}	t_ray;


typedef struct s_map
{
	char	**map2d;
	char	player_facing_to;
	int		pre_start_line_num;
	int		player_x;//column
	int		player_y;//row
	int		width;
	int		height;
}	t_map;

typedef struct s_texture
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*ea;
	mlx_texture_t	*we;
	mlx_image_t		*img;
	int32_t			index;
	uint32_t		ceiling;
	uint32_t		floor;
}	t_texture;

typedef struct s_game
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*floor_color;
	char		*ceiling_color;
	int			height_keeper;
	mlx_t		*init_mlx;
	t_player	*player;
	t_ray		*ray;
	t_texture	*valid_texture;
	t_map		*map;

}	t_game;

bool	check_file_extension(char *str);
void	init_config(t_game *game);
int		parse_file(char *file, t_game *game);
int		parse_color(t_game *game, char *color_line);
bool	parse_map_line(char *current_line, int line_num, t_game *game);
bool	parse_texture_n_color(t_game *game);
bool	validate_game_config(char *argv, t_game *game);
bool	validate_n_store_map2d(char *map_file, t_game *game);
bool	parse_player(t_game *game);
char	is_player_dir(char c);

void	error_msg(char *message);

void	clean_all(t_game *game);
void	free_array(char **array);

//debugging
void	print_my_map(t_map *map);


/* Hook */
void	press_key(void *param);

/* Ray casting */
void	render(void *param);

/* Execution */
void	execution(t_game *game);
// void	render_images(t_game *game);

#endif