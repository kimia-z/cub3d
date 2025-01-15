/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_convert.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rshaheen <rshaheen@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/15 13:47:20 by rshaheen      #+#    #+#                 */
/*   Updated: 2023/12/06 12:26:11 by rshaheen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_convert_helper(unsigned long long n, char *base, int len)
{
	char	*str;

	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (n > 0)
	{
		len--;
		if (ft_strncmp(base, HEX_UPP_BASE, 16) == 0)
			str[len] = HEX_UPP_BASE[n % ft_strlen(base)];
		else
			str[len] = HEX_LOW_BASE[n % ft_strlen(base)];
		n /= ft_strlen(base);
	}
	return (str);
}

char	*ft_convert(unsigned long long n, char *base)
{
	int					len;
	unsigned long long	temp;

	if (n == 0)
		return (strdup("0"));
	len = 0;
	temp = n;
	while (temp > 0)
	{
		temp /= ft_strlen(base);
		len++;
	}
	return (ft_convert_helper(n, base, len));
}
