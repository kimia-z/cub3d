/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshaheen <rshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:36:10 by rshaheen          #+#    #+#             */
/*   Updated: 2023/10/26 19:03:51 by rshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_substr(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

size_t	len_substr(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

static void	free_array(size_t i, char **array)
{
	while (i > 0)
	{
		i--;
		free(array[i]);
	}
	free(array);
}

static char	**extract_str(char const *s, size_t subs_num, char c, char **substr)
{
	size_t	i;
	size_t	sub_i;
	size_t	len;

	i = 0;
	while (i < subs_num && *s)
	{
		while (*s == c)
			s++;
		len = len_substr(s, c);
		substr[i] = (char *)malloc(sizeof(char ) * (len + 1));
		if (!substr[i])
		{
			(free_array(i, substr));
			return (NULL);
		}
		sub_i = 0;
		while (sub_i < len)
			substr[i][sub_i++] = *s++;
		substr[i][sub_i] = '\0';
		i++;
	}
	substr[i] = NULL;
	return (substr);
}

char	**ft_split(char const *s, char c)
{
	char	**new;
	size_t	subs_num;

	if (!s)
		return (NULL);
	subs_num = count_substr(s, c);
	new = (char **)malloc(sizeof(char *) * (subs_num + 1));
	if (!new)
	{
		return (NULL);
	}
	new = extract_str(s, subs_num, c, new);
	return (new);
}
