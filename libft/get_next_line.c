/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 17:01:21 by rshaheen      #+#    #+#                 */
/*   Updated: 2025/03/25 08:09:16 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char **pointer)
{
	free(*pointer);
	*pointer = NULL;
	return (NULL);
}

char	*read_concate(int fd, char *buffer, char *storage)
{
	int		read_result;
	char	*char_temp;

	read_result = 1;
	while (read_result != 0)
	{
		read_result = read(fd, buffer, BUFFER_SIZE);
		if (read_result < 0)
			return (NULL);
		else if (read_result == 0)
			break ;
		buffer[read_result] = '\0';
		if (!storage)
			storage = ft_strdup("");
		if (storage == NULL)
			ft_free(&storage);
		char_temp = storage;
		storage = ft_strjoin(char_temp, buffer);
		if (storage == NULL)
			ft_free(&storage);
		ft_free(&char_temp);
		if (ft_strchr (buffer, '\n'))
			break ;
	}
	return (storage);
}

char	*remaining_after_n(char *line)
{
	size_t	count;
	char	*remaining;

	count = 0;
	while (line[count] != '\n' && line[count] != '\0')
		count++;
	if (line[count] == '\0')
		return (NULL);
	remaining = ft_substr(line, count + 1, ft_strlen(line) - count);
	if (remaining == NULL)
		ft_free(&remaining);
	if (remaining != NULL && remaining[0] == '\0')
		ft_free(&remaining);
	line[count + 1] = '\0';
	return (remaining);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*storage;

	if (fd < 0 || BUFFER_SIZE <= 0 || read (fd, NULL, 0) == -1)
	{
		if (storage)
			ft_free(&storage);
		return (NULL);
	}
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	line = read_concate(fd, buffer, storage);
	ft_free(&buffer);
	if (line == NULL)
		return (NULL);
	storage = remaining_after_n(line);
	return (line);
}

// int	main(void)
// {
// 	char	*line;
// 	int		count;
// 	int		fd1;
// 	int		fd2;
// 	int		fd3;
// 	//fd1 = open("example.txt", O_RDONLY);
// 	fd2 = open("example1.txt", O_RDONLY);
// 	//fd3 = open("example2.txt", O_RDONLY);
// 	count = 1;
// 	while (count < 3)
// 	{
// 		// line = get_next_line(fd1);
// 		// printf("line [%d]: %s", count, line);
// 		// free(line);

// 		line = get_next_line(fd2);
// 		printf("line [%d]: %s", count, line);
// 		free(line);

// 		// line = get_next_line(fd3);
// 		// printf("line [%d]: %s", count, line);
// 		// free(line);
// 		count++;
// 	}
// 	//close(fd1);
// 	close(fd2);
// 	//close(fd3);
// 	return (0);
// }