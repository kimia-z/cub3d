/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_color.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/21 19:31:07 by rshaheen      #+#    #+#                 */
/*   Updated: 2025/03/25 10:38:59 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

size_t	count_arr_elements(char **arr)
{
	size_t	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

//32-bit integer is used for game
//Decimal = number system
//hexadecimal = number system

//32-bit number is represented using 32 binary digits (bits), 
//where each bit can be either 0 or 1. can be signed or unsigned.
//32-bit binary number: 11010110101110101011010111110001(32 digits)
//Hexadecimal version is used for easier reading and compactness
//The binary number above would be represented as 0xDAB5F1F1 in hexadecimal.

//get_rgb COMBINES the individual RGB (Red, Green, Blue) values 
//and the alpha (opacity) value into a single 32-bit integer.
//Left shifting a number n by m bits (n << m) means multiplying n by 2^m.
//because every number needs to be specifically positioned in a 32-bit number
// | (bitwise OR) operator combines all the shifted values into 1 32-bit number.

int	get_rgb(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int32_t	get_colors(char **color_num)
{
	int		i;
	int		number;
	int		arg[3];
	int32_t	rgb;
	int		j;

	i = 0;
	while (color_num[i])
	{
		j = 0;
		while (color_num[i][j])
		{
			if (!ft_isdigit(color_num[i][j]) && (color_num[i][j] != ' ')
			&& (color_num[i][j] != '\t'))
				return (error_msg("Invalid characters in RGB values\n"), -2);
			j++;
		}
		number = ft_atoi(color_num[i]);
		if (number < 0 || number > 255)
			return (error_msg("RGB values must be 0-255."), -2);
		arg[i] = number;
		i++;
	}
	rgb = get_rgb(arg[0], arg[1], arg[2], 255);
	return (rgb);
}

//parse_color receives one color line at a time from the map
//strip the identifier (F/C), and white space and newlines
//split rgb values at ','; must be 3 

int	parse_color(char *color_line)
{
	char	**splitted_color_num;
	char	*trimmed_line;
	int32_t	rgb;

	rgb = 0;
	if (!color_line)
		return (error_msg("missing color string"), -1);
	trimmed_line = ft_strtrim(color_line, "FC\n");
	if (!trimmed_line)
		return (error_msg("memory allocation for trim color failed\n"), -2);
	splitted_color_num = ft_split(trimmed_line, ',');
	if (!splitted_color_num)
		return (free(trimmed_line), error_msg("color line misconfig\n"), -2);
	free (trimmed_line);
	if (count_arr_elements(splitted_color_num) != 3)
	{
		error_msg("Number of color element wrong\n");
		return (free_array(splitted_color_num), -2);
	}
	rgb = get_colors(splitted_color_num);
	if (rgb == -2)
		return (free_array(splitted_color_num), -2);
	free_array(splitted_color_num);
	return (rgb);
}
