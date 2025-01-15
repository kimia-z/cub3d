/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshaheen <rshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:30:06 by rshaheen          #+#    #+#             */
/*   Updated: 2023/10/26 17:41:13 by rshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*dest_a;
	char	*src_a;
	size_t	i;

	dest_a = (char *)dest;
	src_a = (char *)src;
	if (src_a < dest_a)
	{
		i = n;
		while (i > 0)
		{
			i--;
			dest_a[i] = src_a[i];
		}
	}
	else if (src_a > dest_a)
	{
		i = 0;
		while (i < n)
		{
			dest_a[i] = src_a[i];
			i++;
		}
	}
	return (dest);
}
