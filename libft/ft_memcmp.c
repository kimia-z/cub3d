/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshaheen <rshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:33:03 by rshaheen          #+#    #+#             */
/*   Updated: 2023/10/26 17:24:15 by rshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*x1;
	const unsigned char	*x2;

	i = 0;
	x1 = s1;
	x2 = s2;
	while (n > 0)
	{
		if (x1[i] != x2[i])
			return (x1[i] - x2[i]);
		i++;
		n--;
	}
	return (0);
}
