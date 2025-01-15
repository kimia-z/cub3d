/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/17 11:59:08 by rshaheen      #+#    #+#                 */
/*   Updated: 2024/04/26 18:47:32 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*memal(size_t n)
{
	char	*str;

	str = (char *)malloc((sizeof(char)) * (n + 1));
	if (!str)
		return (NULL);
	return (str);
}

int	len(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	char	*temp;
	int		len_s1;
	int		len_s2;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = len(s1);
	len_s2 = len(s2);
	new_str = memal(len_s1 + len_s2);
	if (!new_str)
		return (NULL);
	temp = new_str;
	while (*s1)
		*temp++ = *s1++;
	while (*s2)
		*temp++ = *s2++;
	*temp = '\0';
	return (new_str);
}
