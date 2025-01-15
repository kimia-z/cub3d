/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshaheen <rshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:55:17 by rshaheen          #+#    #+#             */
/*   Updated: 2023/10/23 17:37:55 by rshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char const *s)
{
	char	*temp;
	char	*dup_str;

	temp = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!temp)
		return (NULL);
	dup_str = temp;
	while (*s)
	{
		*temp++ = *s++;
	}
	*temp = '\0';
	return (dup_str);
}
