
#include "../../cub3d.h"
#include <stdbool.h>

bool	check_file_extension(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (str && ft_strncmp(&str[len - 4], ".cub", 4) != 0)
	{
		write(2, "Error: wrong file extension. Please use file.cub\n", 49);
		return (false);
	}
	return (true);
}

