/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshaheen <rshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:10:31 by rshaheen          #+#    #+#             */
/*   Updated: 2023/10/26 17:18:55 by rshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*x;
	size_t				i;

	i = 0;
	x = (const unsigned char *)s;
	while (i < n)
	{
		if (x[i] == (unsigned char)c)
			return ((void *)&x[i]);
		i++;
	}
	return (NULL);
}
