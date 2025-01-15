/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshaheen <rshaheen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 16:17:02 by rshaheen          #+#    #+#             */
/*   Updated: 2023/10/26 17:10:19 by rshaheen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int a)
{
	int	i;

	i = 0;
	if (a == 0)
		return (1);
	while (a > 0)
	{
		a /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		sign;
	int		len;
	char	*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	sign = 0;
	if (n < 0)
	{
		sign = 1;
		n = -n;
	}
	len = ft_len(n);
	str = (char *)malloc(sizeof(char) * (len + sign + 1));
	if (!str)
		return (NULL);
	str[len + sign] = '\0';
	while (len-- > 0)
	{
		str[len + sign] = '0' + n % 10;
		n /= 10;
	}
	if (sign)
		str[0] = '-';
	return (str);
}
