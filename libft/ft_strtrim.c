/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshaheen <rshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:15:37 by rshaheen          #+#    #+#             */
/*   Updated: 2023/10/23 17:37:55 by rshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_in_set(char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

size_t	trim_len(const char *s1, const char *set)
{
	size_t	len_s1;
	size_t	start;
	size_t	end;

	len_s1 = ft_strlen(s1);
	start = 0;
	end = len_s1;
	while (s1[start] != '\0' && is_in_set(s1[start], set) == 1)
		start++;
	while (end > start && is_in_set(s1[end - 1], set) == 1)
		end--;
	return (end - start);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	trimmed_len;
	char	*trimmed_str;
	size_t	start;
	size_t	end;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	trimmed_len = trim_len(s1, set);
	trimmed_str = (char *)malloc(trimmed_len + 1);
	if (!trimmed_str)
		return (NULL);
	while (s1[start] != '\0' && is_in_set(s1[start], set) == 1)
		start++;
	while (end > start && is_in_set(s1[end - 1], set) == 1)
		end--;
	i = 0;
	while (start < end)
	{
		trimmed_str[i++] = s1[start++];
	}
	trimmed_str[i] = '\0';
	return (trimmed_str);
}
