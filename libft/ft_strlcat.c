/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshaheen <rshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:07:06 by rshaheen          #+#    #+#             */
/*   Updated: 2023/10/23 17:37:55 by rshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	length(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	total_len;
	size_t	dst_len;

	total_len = 0;
	i = 0;
	if ((!dst || !src) && !size)
		return (0);
	while (dst[i] && i < size)
		i++;
	dst_len = i;
	if (dst_len < size)
		total_len = dst_len + length(src);
	else
		return (size + length(src));
	while (*src != '\0' && (i + 1) < size)
	{
		dst[i] = src[0];
		i++;
		src++;
	}
	dst[i] = '\0';
	return (total_len);
}
