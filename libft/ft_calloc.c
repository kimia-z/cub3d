/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshaheen <rshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 20:23:06 by rshaheen          #+#    #+#             */
/*   Updated: 2023/10/25 17:42:45 by rshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*memory;
	size_t	total_size;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	else
		total_size = nmemb * size;
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	memory = malloc(total_size);
	if (!memory)
		return (NULL);
	ft_bzero(memory, total_size);
	return (memory);
}
